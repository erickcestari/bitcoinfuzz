all: module.a

CXX = clang++
CXXFLAGS += -Wall -Wextra -fsanitize=address,fuzzer -std=c++20 -I ../../include

UNAME_S := $(shell uname -s)
RUNTIME_ID := $(shell echo $(UNAME_S)  | tr '[:upper:]' '[:lower:]' | sed 's/darwin/osx/')-$(shell uname -m | sed 's/x86_64/x64/; s/aarch64/arm64/')
ifeq ($(UNAME_S), Darwin)
  NBITCOIN_LIB_EXT := dylib
else
  NBITCOIN_LIB_EXT := so
endif

NBITCOIN_LIB_PATH := ./bin/Release/net9.0/$(RUNTIME_ID)/native/NBitcoin.CppBridge.$(NBITCOIN_LIB_EXT)

$(NBITCOIN_LIB_PATH):
	dotnet publish -c Release -r $(RUNTIME_ID) --self-contained
	@if [ "$(UNAME_S)" = "Darwin" ]; then \
		llvm-install-name-tool -id ./NBitcoin.CppBridge.$(NBITCOIN_LIB_EXT)  $(NBITCOIN_LIB_PATH); \
	fi
	cp $(NBITCOIN_LIB_PATH) ../../NBitcoin.CppBridge.$(NBITCOIN_LIB_EXT)

module.a: module.o $(NBITCOIN_LIB_PATH)
	ar rcs module.a module.o

module.o: module.cpp module.h
	$(CXX) $(CXXFLAGS) -I . -fPIC -c module.cpp -o module.o

clean:
	rm -rf *.o module.a ./bin ./obj

.PHONY: $(NBITCOIN_LIB_PATH)