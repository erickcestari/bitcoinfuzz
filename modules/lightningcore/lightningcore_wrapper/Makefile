CC = cc
AR = ar
INCLUDES = -I. -I./lightning -I./lightning/ccan
CFLAGS = -std=c11 -Wall -Wextra -fPIC -D_DEFAULT_SOURCE

LIB_NAME = liblightningcore_wrapper.a

SOURCES = lightningcore_lib.c
OBJECTS = $(SOURCES:.c=.o)

all: $(LIB_NAME)

$(LIB_NAME): $(OBJECTS)
	$(AR) rcs $@ $(OBJECTS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJECTS) $(LIB_NAME)

.PHONY: all clean