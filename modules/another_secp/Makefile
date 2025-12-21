all: module.a

CXXFLAGS += -Wall -Wextra -std=c++20 \
            -fsanitize=fuzzer,address \
            -I . \
            -I ../../include \
            -I /opt/homebrew/include \
            -I ../../external/secp256k1/include

SECP256K1_LIB = ../../external/secp256k1_2/.libs/libsecp256k1.a
MAKE = make

OBJCOPY := $(shell command -v objcopy 2> /dev/null)
SYMBOL_PREFIX ?= second

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

module.a: $(SECP256K1_LIB) module.o secp256k1_symbols.map
	bash ../../merge.sh module.a $(SECP256K1_LIB) module.o

	@echo "Renaming secp256k1 symbols in Bitcoin object files..."
	@for obj in module.o ; do \
		if [ -f "$$obj" ]; then \
			echo "  Renaming symbols in $$obj..."; \
			$(OBJCOPY) --redefine-syms=secp256k1_symbols.map $$obj; \
		fi \
	done

	@echo "Verifying renamed symbols in module.o:"
	@nm module.o | grep secp256k1 | head -3

	# Create archive with renamed Bitcoin objects
	@echo "Creating archive with renamed objects..."
	$(AR) rcs $@ module.o

	mkdir -p tmp_obj
	# Extract secp256k1 objects and rename ONLY secp256k1_* symbols
	cd tmp_obj && $(AR) x ../$(SECP256K1_LIB)
	@echo "Renaming only secp256k1_* symbols (preserving ASAN/sanitizer symbols)..."
	cd tmp_obj && for obj in *.o; do \
		for sym in $$(nm $$obj | awk '{print $$3}'); do \
			$(OBJCOPY) --redefine-sym $$sym=$(SYMBOL_PREFIX)_$$sym $$obj 2>/dev/null || true; \
		done; \
		for sym in $$(nm $$obj | awk '{print $$3}'); do \
			$(OBJCOPY) --redefine-sym $$sym=$(SYMBOL_PREFIX)_$$sym $$obj 2>/dev/null || true; \
		done; \
		for sym in $$(nm $$obj | awk '{print $$3}'); do \
			$(OBJCOPY) --redefine-sym $$sym=$(SYMBOL_PREFIX)_$$sym $$obj 2>/dev/null || true; \
		done; \
	done
	$(AR) rcs $@ tmp_obj/*.o
	rm -rf tmp_obj/*

module.o: module.cpp module.h
	$(CXX) $(CXXFLAGS) -I . -fPIC -c module.cpp -o module.o

format: 
	clang-format -i ./module.cpp ./module.h

check-format:
	clang-format -Werror --fail-on-incomplete-format -n ./module.cpp ./module.h

clean:
	rm -f *.o *.a
	cd ../../external/secp256k1 && $(MAKE) clean || true

.PHONY: clean
