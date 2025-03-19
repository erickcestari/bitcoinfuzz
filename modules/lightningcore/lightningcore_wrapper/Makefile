CC = g++
CXX = g++
AR = ar
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -fPIC
LDFLAGS = 
INCLUDES = -I. -I./lightning -I./lightning/ccan
# Output file
LIB_NAME = liblightningcore_wrapper.a

# Source files
SOURCES = lightningcore_lib.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(LIB_NAME)

# Rule to build the static library
$(LIB_NAME): $(OBJECTS)
	$(AR) rcs $@ $^

# Rule to compile object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJECTS) $(LIB_NAME)

.PHONY: all clean