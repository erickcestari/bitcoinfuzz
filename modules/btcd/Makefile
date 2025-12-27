CXXFLAGS += -Wall -Wextra -std=c++20 -I. -I ../../include -I./btcd_wrapper
SYMBOL_PREFIX ?= btcd

all: module.a

module.a: module.o btcd_wrapper/libbtcd_wrapper.a
	bash ../../merge.sh module.a btcd_wrapper/libbtcd_wrapper.a module.o
	ranlib module.a

btcd_wrapper/libbtcd_wrapper.a:
	cd btcd_wrapper && go build -o libbtcd_wrapper_temp.a -buildmode=c-archive -tags=libfuzzer -gcflags=all=-d=libfuzzer wrapper.go
	
	@echo "Extracting symbols to rename..."
	@nm btcd_wrapper/libbtcd_wrapper_temp.a | awk '{print $$NF}' | grep -E '^(_cgo|x_cgo|crosscall|x_crosscall)' | sort -u > symbols_to_rename.txt
	@echo "Creating symbol map..."
	@while read sym; do \
		echo "$$sym $(SYMBOL_PREFIX)_$$sym"; \
	done < symbols_to_rename.txt > cgo_symbols.map
	@echo "Generated $$(wc -l < cgo_symbols.map) symbol mappings"
	@if [ ! -s cgo_symbols.map ]; then \
		echo "Error: cgo_symbols.map is empty or not created"; \
		exit 1; \
	fi
	mkdir -p tmp_obj
	cd tmp_obj && ar x ../btcd_wrapper/libbtcd_wrapper_temp.a
	@echo "Renaming symbols in object files..."
	@cd tmp_obj && for obj in *.o; do \
		objcopy --redefine-syms=../cgo_symbols.map $$obj 2>/dev/null || true; \
	done
	@echo "Creating final archive..."
	ar rcs btcd_wrapper/libbtcd_wrapper.a tmp_obj/*.o
	ranlib btcd_wrapper/libbtcd_wrapper.a
	rm -rf tmp_obj symbols_to_rename.txt cgo_symbols.map btcd_wrapper/libbtcd_wrapper_temp.a

module.o: module.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c module.cpp -o module.o

format:
	clang-format -i ./module.cpp ./module.h
	cd btcd_wrapper && go fmt

check-format:
	clang-format -Werror --fail-on-incomplete-format -n ./module.cpp ./module.h
	cd btcd_wrapper && files=$$(gofmt -l .); if [ -n "$$files" ]; then echo "Unformatted files:"; echo "$$files"; exit 1; fi

clean:
	rm -f *.o *.a cgo_symbols.map symbols_to_rename.txt btcd_wrapper/*.a
	rm -rf tmp_obj

.PHONY: all clean format check-format