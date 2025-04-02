CC = cc
AR = ar
INCLUDES = -I. -I./lightning -I./lightning/ccan -I./lightning/external/libwally-core/include -I./lightning/external/jsmn
CFLAGS = -std=gnu11 -Wall -Wextra -fPIC -D_DEFAULT_SOURCE -Wno-unused-parameter -Wno-multistatement-macros

LIB_NAME = liblightningcore_wrapper.a

SOURCES = lightningcore_lib.c \
          ./lightning/common/bolt11.c \
          ./lightning/ccan/ccan/tal/tal.c \
					
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