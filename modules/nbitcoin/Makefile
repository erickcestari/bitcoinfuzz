all: module.a

CXX = clang++
CXXFLAGS += -Wall -Wextra -fsanitize=address,fuzzer -std=c++20 -I ../../include
RUNTIME_ID := $(shell uname -s | tr '[:upper:]' '[:lower:]' | sed 's/darwin/osx/')-$(shell uname -m | sed 's/x86_64/x64/; s/aarch64/arm64/')

NBITCOIN_LIB_PATH := ./bin/Release/net9.0/$(RUNTIME_ID)/publish/NBitcoin.CppBridge.so

$(NBITCOIN_LIB_PATH):
	dotnet publish -c Release -r $(RUNTIME_ID) --self-contained
	cp $(NBITCOIN_LIB_PATH) ../../NBitcoin.CppBridge.so

module.a: module.o $(NBITCOIN_LIB_PATH)
	ar rcs temp_module.a module.o
	echo "INPUT(temp_module.a $(NBITCOIN_LIB_PATH))" > module.a

module.o: module.cpp module.h
	$(CXX) $(CXXFLAGS) -I . -fPIC -c module.cpp -o module.o

clean:
	rm -rf *.o module.a ./bin ./obj

.PHONY: $(NBITCOIN_LIB_PATH)