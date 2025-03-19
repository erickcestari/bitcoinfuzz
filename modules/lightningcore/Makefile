CXX = clang++
CXXFLAGS += -Wall -Wextra -std=c++20 -I. -I ../../include -I./lightningcore_wrapper

all: module.a

module.a: lightningcore module.o lightningcore_wrapper/liblightningcore_wrapper.a
	bash ../../merge.sh module.a lightningcore_wrapper/liblightningcore_wrapper.a module.o
	ranlib module.a

lightningcore:
	cd lightningcore_wrapper && go build -o liblightningcore_wrapper.a -buildmode=c-archive -tags=libfuzzer -gcflags=all=-d=libfuzzer wrapper.go

module.o: module.cpp
	$(CXX) $(CXXFLAGS) -lscript -L. -fPIC -c module.cpp -o module.o

clean:
	rm -f *.o *.a