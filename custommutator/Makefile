all: module.a

CXXFLAGS += -Wall -Wextra -std=c++20 \
            -fsanitize=fuzzer,address \
            -I . \
            -I ../../include \
            -I /opt/homebrew/include \
						-I ./utils \
						-I ../

MAKE = make
AR := ar

# Automatically find all .cpp files
BITCOIN_SRCS := $(shell find . -name "*.cpp" ! -name "bech32.cpp" ! -path "./univalue/*" ! -path "./secp256k1/*")
BITCOIN_OBJS := $(BITCOIN_SRCS:.cpp=.o)
SECP256K1_LIB = utils/secp256k1/.libs/libsecp256k1.a


# Build libsecp256k1 with sanitizer flags
$(SECP256K1_LIB):
	cd utils/secp256k1 && \
	./autogen.sh && \
	./configure \
		--enable-module-recovery \
		--enable-experimental \
		--enable-module-schnorrsig \
		--disable-shared \
		--with-pic \
		CFLAGS="-fsanitize=address,fuzzer-no-link" && \
	$(MAKE)

module.a: utils/bech32.o  mutators/customcrossover.o $(BITCOIN_OBJS) $(SECP256K1_LIB)
	$(AR) rcs $@ utils/bech32.o mutators/customcrossover.o $(BITCOIN_OBJS)
	bash ../merge.sh module.a $(SECP256K1_LIB) utils/bech32.o mutators/customcrossover.o $(BITCOIN_OBJS)
	ranlib module.a

utils/bech32.o: utils/bech32.cpp utils/bech32.h
	$(CXX) $(CXXFLAGS) -I . -fPIC -c utils/bech32.cpp -o utils/bech32.o

mutators/customcrossover.o: mutators/customcrossover.cpp mutators/customcrossover.h
	$(CXX) $(CXXFLAGS) -I . -fPIC -c mutators/customcrossover.cpp -o mutators/customcrossover.o

%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@

clean:
	rm -rf *.o **/*.o module.a tmp_obj/ *_combined.o

.PHONY: clean
