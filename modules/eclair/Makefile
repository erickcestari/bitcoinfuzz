CXX = clang++
CXXFLAGS += -Wall -Wextra -std=c++20 -fPIC  -I ../../include

JAVA_HOME ?= $(shell readlink -f $(shell which javac) | sed "s:/bin/javac::")
OS_NAME := $(shell uname | tr '[:upper:]' '[:lower:]')

CXXFLAGS += -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/$(OS_NAME)

ROOT_DIR := $(realpath $(dir $(lastword $(MAKEFILE_LIST)))/../..)
ECLAIR_DIR := $(ROOT_DIR)/external/eclair
ECLAIR_ZIP_BUILD := $(shell find $(ECLAIR_DIR)/eclair-node/target -name "eclair-node_*.zip" | head -n 1)

all: module.a

lib: eclair.zip
	mkdir -p lib
	mkdir -p eclair_extracted
	unzip -o eclair.zip -d eclair_extracted
	cp -r eclair_extracted/*/lib/* lib/

eclair.zip:
	@echo "Building eclair in $(ECLAIR_DIR)..."
	cd $(ECLAIR_DIR) && ./mvnw package -pl eclair-node -am -Dmaven.test.skip=true -DskipTests

	@echo "Copying .JAR in $(LIGHTNING_DIR)..."
	cp $(ECLAIR_ZIP_BUILD) eclair.zip

module.a: lib module.o
	$(AR) rcs $@ module.o
	ranlib $@

module.o: module.cpp module.h
	$(CXX) $(CXXFLAGS) -fPIC -c module.cpp -o module.o

clean:
	rm -f *.o *.a