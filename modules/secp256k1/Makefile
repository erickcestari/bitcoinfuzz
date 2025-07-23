all: module.a
SECP_LIB_PATH := ../../external/secp256k1/.libs/libsecp256k1.a
CXX := clang++
CXXFLAGS += -Wall -Wextra -fsanitize=address,fuzzer -std=c++20 -I ../../include ../../external/secp256k1/src

module.a: module.o $(SECP_LIB_PATH)
	bash ../../merge.sh module.a $(SECP_LIB_PATH) module.o
	ranlib module.a

$(SECP_LIB_PATH):
	cd ../../external/secp256k1 && ./autogen.sh
	cd ../../external/secp256k1 && ./configure \
	    --enable-fuzz \
	    --enable-experimental \
	    --enable-module-ecdh \
	    --enable-module-recovery \
	    --enable-module-schnorrsig \
	    --with-asm=no \
	    CC="clang -fsanitize=address,fuzzer-no-link" \
	    CXX="clang++ -fsanitize=address,fuzzer-no-link" \
	    CFLAGS="-fsanitize=address,fuzzer-no-link" \
	    CXXFLAGS="-fsanitize=address,fuzzer-no-link"
	cd ../../external/secp256k1 && make


module.o: module.cpp module.h
	$(CXX) $(CXXFLAGS) -I . -fPIC -c module.cpp -o module.o