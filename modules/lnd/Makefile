CXX = clang++
CXXFLAGS += -Wall -Wextra -std=c++20 -I. -I ../../include -I./lnd_wrapper

all: module.a

module.a: golang module.o lnd_wrapper/liblnd_wrapper.a
	bash ../../merge.sh module.a lnd_wrapper/liblnd_wrapper.a module.o
	ranlib module.a

golang:
	cd lnd_wrapper && \
	export CC=clang; \
	export CXX=clang++; \
	export CGO_CFLAGS="-fsanitize=address,fuzzer-no-link -fsanitize-coverage=trace-cmp,inline-8bit-counters,pc-table,trace-div,trace-gep,trace-loads,trace-stores"; \
	export CGO_LDFLAGS="-fsanitize=address,fuzzer-no-link"; \
	go build -o liblnd_wrapper.a -buildmode=c-archive \
		-tags=libfuzzer -gcflags=all=-d=libfuzzer \
		-a -installsuffix cgo wrapper.go

module.o: module.cpp
	$(CXX) $(CXXFLAGS) -lscript -L. -fPIC -c module.cpp -o module.o

clean:
	rm -f *.o *.a