CC=gcc
CXX=g++
LIGHTNING_CORE_PATH=/home/erick/study/work-open-source/lightning-core

# Update these paths according to your lightning-core installation
INCLUDES=-I$(LIGHTNING_CORE_PATH)/include -I../..
LDFLAGS=-L$(LIGHTNING_CORE_PATH)/lib -lsecp256k1 -lblockchain -lbolt11

SRCS=module.cpp lightning_core_lib.c
OBJS=$(SRCS:.cpp=.o)
OBJS:=$(OBJS:.c=.o)

all: liblightningcore_module.a

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

liblightningcore_module.a: $(OBJS)
	ar rcs $@ $(OBJS)

clean:
	rm -f *.o *.a