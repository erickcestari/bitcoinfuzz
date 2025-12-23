all: module.a

CXXFLAGS += -Wall -Wextra -std=c++20 \
            -fsanitize=fuzzer,address \
            -I . \
            -I ../../include \
            -I /opt/homebrew/include \
            -I ../../external/secp256k1/include

SECP256K1_LIB = ../../external/secp256k1/.libs/libsecp256k1.a
MAKE = make

OBJCOPY := $(shell command -v objcopy 2> /dev/null)
SYMBOL_PREFIX ?= orig

# Build libsecp256k1 with sanitizer flags
$(SECP256K1_LIB):
	cd ../../external/secp256k1 && \
	./autogen.sh && \
	./configure \
		--enable-module-recovery \
		--enable-experimental \
		--enable-module-schnorrsig \
		--disable-shared \
		--with-pic \
		CFLAGS="-fsanitize=address,fuzzer-no-link" && \
	$(MAKE)

secp256k1_symbols.map:

	@echo "Generating symbol map for ALL secp256k1 symbols..."
	@nm $(SECP256K1_LIB) | awk '/ [TDBR] / && /secp256k1/ {print $$3}' | sort -u | while read sym; do \
		echo "$$sym $(SYMBOL_PREFIX)_$$sym"; \
	done > $@
	@echo "Generated $$(wc -l < $@) symbol mappings"

secp256k1_merged.o: $(SECP256K1_LIB)
	@echo "Extracting and merging secp256k1 library objects..."
	mkdir -p tmp_obj
	cd tmp_obj && $(AR) x ../$(SECP256K1_LIB)
	# Use partial linking to merge all objects
	ld -r -o secp256k1_merged_tmp.o tmp_obj/*.o
	rm -rf tmp_obj
	# Remove COMDAT group sections to avoid conflicts with other secp256k1 copies
	$(OBJCOPY) --remove-section=.group secp256k1_merged_tmp.o $@
	rm -f secp256k1_merged_tmp.o

module.a: $(SECP256K1_LIB) module.o secp256k1_symbols.map secp256k1_merged.o
	@echo "Renaming secp256k1 symbols in module.o..."
	$(OBJCOPY) --redefine-syms=secp256k1_symbols.map module.o

	@echo "Verifying renamed symbols in module.o:"
	@nm module.o | grep secp256k1 | head -5 || echo "No secp256k1 symbols found (good if all renamed)"

	@echo "Renaming symbols in merged secp256k1 object..."
	$(OBJCOPY) --redefine-syms=secp256k1_symbols.map secp256k1_merged.o

	# Create archive with renamed objects
	@echo "Creating archive with renamed objects..."
	$(AR) rcs $@ module.o secp256k1_merged.o

module.o: module.cpp module.h
	$(CXX) $(CXXFLAGS) -I . -fPIC -c module.cpp -o module.o

format: 
	clang-format -i ./module.cpp ./module.h

check-format:
	clang-format -Werror --fail-on-incomplete-format -n ./module.cpp ./module.h

clean:
	rm -f *.o *.a secp256k1_symbols.map secp256k1_merged.o
	rm -rf tmp_obj
	cd ../../external/secp256k1 && $(MAKE) clean || true

.PHONY: clean
