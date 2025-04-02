CC = cc
AR = ar
LIGHTNING_DIR = ./lightning
CCANDIR := $(LIGHTNING_DIR)/ccan
INCLUDES = -I. -I$(LIGHTNING_DIR) -I$(LIGHTNING_DIR)/ccan -I$(LIGHTNING_DIR)/external/libwally-core/include -I$(LIGHTNING_DIR)/external/jsmn
CFLAGS = -std=gnu11 -Wall -Wextra -fPIC -D_DEFAULT_SOURCE -Wno-unused-parameter -Wno-multistatement-macros

LIB_NAME = liblightningcore_wrapper.a

SOURCES = lightningcore_lib.c \
          $(LIGHTNING_DIR)/common/bolt11.c \
          $(LIGHTNING_DIR)/ccan/ccan/tal/tal.c \
          $(LIGHTNING_DIR)/common/amount.c \
          $(LIGHTNING_DIR)/common/bech32.c \
          $(LIGHTNING_DIR)/common/bech32_util.c \
          $(LIGHTNING_DIR)/common/features.c \
          $(LIGHTNING_DIR)/common/node_id.c \
          $(LIGHTNING_DIR)/common/utils.c \
          $(LIGHTNING_DIR)/common/pseudorand.c \
          $(LIGHTNING_DIR)/common/base32.c \
          $(LIGHTNING_DIR)/common/setup.c \
          $(LIGHTNING_DIR)/bitcoin/pubkey.c \
          $(LIGHTNING_DIR)/bitcoin/chainparams.c \
          $(LIGHTNING_DIR)/bitcoin/short_channel_id.c \
          $(LIGHTNING_DIR)/bitcoin/script.c \
          $(LIGHTNING_DIR)/bitcoin/tx.c \
          $(LIGHTNING_DIR)/wire/fromwire.c \
          $(LIGHTNING_DIR)/wire/towire.c
          
OBJECTS = $(SOURCES:.c=.o)

all: $(LIB_NAME)

$(LIB_NAME): libccan.a $(OBJECTS)
	cp libccan.a $@
	$(AR) rs $@ $(OBJECTS)

# Rule to compile the object files
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

CCAN_OBJS := ccan-asort.o \
	ccan-base64.o \
	ccan-bitmap.o \
	ccan-bitops.o \
	ccan-breakpoint.o \
	ccan-closefrom.o \
	ccan-crc32c.o \
	ccan-crypto-hmac.o \
	ccan-crypto-hkdf.o \
	ccan-crypto-ripemd160.o \
	ccan-crypto-sha256.o \
	ccan-crypto-shachain.o \
	ccan-crypto-siphash24.o \
	ccan-err.o \
	ccan-fdpass.o \
	ccan-htable.o \
	ccan-ilog.o \
	ccan-io-io.o \
	ccan-intmap.o \
	ccan-io-poll.o \
	ccan-io-fdpass.o \
	ccan-isaac.o \
	ccan-isaac64.o \
	ccan-json_escape.o \
	ccan-json_out.o \
	ccan-list.o \
	ccan-mem.o \
	ccan-membuf.o \
	ccan-noerr.o \
	ccan-opt-helpers.o \
	ccan-opt-parse.o \
	ccan-opt-usage.o \
	ccan-opt.o \
	ccan-pipecmd.o \
	ccan-ptr_valid.o \
	ccan-rbuf.o \
	ccan-read_write_all.o \
	ccan-rune-coding.o \
	ccan-rune-rune.o \
	ccan-str-base32.o \
	ccan-str-hex.o \
	ccan-str.o \
	ccan-strmap.o \
	ccan-strset.o \
	ccan-take.o \
	ccan-tal-grab_file.o \
	ccan-tal-link.o \
	ccan-tal-path.o \
	ccan-tal-str.o \
	ccan-tal.o \
	ccan-time.o \
	ccan-timer.o \
	ccan-utf8.o

CCAN_HEADERS := $(CCANDIR)/config.h \
	$(CCANDIR)/ccan/alignof/alignof.h \
	$(CCANDIR)/ccan/array_size/array_size.h \
	$(CCANDIR)/ccan/asort/asort.h \
	$(CCANDIR)/ccan/base64/base64.h \
	$(CCANDIR)/ccan/bitmap/bitmap.h \
	$(CCANDIR)/ccan/bitops/bitops.h \
	$(CCANDIR)/ccan/breakpoint/breakpoint.h \
	$(CCANDIR)/ccan/build_assert/build_assert.h \
	$(CCANDIR)/ccan/cast/cast.h \
	$(CCANDIR)/ccan/cdump/cdump.h \
	$(CCANDIR)/ccan/check_type/check_type.h \
	$(CCANDIR)/ccan/closefrom/closefrom.h \
	$(CCANDIR)/ccan/compiler/compiler.h \
	$(CCANDIR)/ccan/container_of/container_of.h \
	$(CCANDIR)/ccan/cppmagic/cppmagic.h \
	$(CCANDIR)/ccan/crc32c/crc32c.h \
	$(CCANDIR)/ccan/crypto/hkdf_sha256/hkdf_sha256.h \
	$(CCANDIR)/ccan/crypto/hmac_sha256/hmac_sha256.h \
	$(CCANDIR)/ccan/crypto/ripemd160/ripemd160.h \
	$(CCANDIR)/ccan/crypto/sha256/sha256.h \
	$(CCANDIR)/ccan/crypto/shachain/shachain.h \
	$(CCANDIR)/ccan/crypto/siphash24/siphash24.h \
	$(CCANDIR)/ccan/endian/endian.h \
	$(CCANDIR)/ccan/err/err.h \
	$(CCANDIR)/ccan/fdpass/fdpass.h \
	$(CCANDIR)/ccan/graphql/graphql.h \
	$(CCANDIR)/ccan/htable/htable.h \
	$(CCANDIR)/ccan/htable/htable_type.h \
	$(CCANDIR)/ccan/ilog/ilog.h \
	$(CCANDIR)/ccan/intmap/intmap.h \
	$(CCANDIR)/ccan/io/backend.h \
	$(CCANDIR)/ccan/io/fdpass/fdpass.h \
	$(CCANDIR)/ccan/io/io.h \
	$(CCANDIR)/ccan/io/io_plan.h \
	$(CCANDIR)/ccan/isaac/isaac.h \
	$(CCANDIR)/ccan/isaac/isaac64.h \
	$(CCANDIR)/ccan/json_escape/json_escape.h \
	$(CCANDIR)/ccan/json_out/json_out.h \
	$(CCANDIR)/ccan/likely/likely.h \
	$(CCANDIR)/ccan/list/list.h \
	$(CCANDIR)/ccan/lqueue/lqueue.h \
	$(CCANDIR)/ccan/mem/mem.h \
	$(CCANDIR)/ccan/membuf/membuf.h \
	$(CCANDIR)/ccan/noerr/noerr.h \
	$(CCANDIR)/ccan/opt/opt.h \
	$(CCANDIR)/ccan/opt/private.h \
	$(CCANDIR)/ccan/order/order.h \
	$(CCANDIR)/ccan/pipecmd/pipecmd.h \
	$(CCANDIR)/ccan/ptr_valid/ptr_valid.h \
	$(CCANDIR)/ccan/ptrint/ptrint.h \
	$(CCANDIR)/ccan/rbuf/rbuf.h \
	$(CCANDIR)/ccan/read_write_all/read_write_all.h \
	$(CCANDIR)/ccan/rune/internal.h \
	$(CCANDIR)/ccan/rune/rune.h \
	$(CCANDIR)/ccan/short_types/short_types.h \
	$(CCANDIR)/ccan/str/base32/base32.h \
	$(CCANDIR)/ccan/str/hex/hex.h \
	$(CCANDIR)/ccan/str/str.h \
	$(CCANDIR)/ccan/str/str_debug.h \
	$(CCANDIR)/ccan/strmap/strmap.h \
	$(CCANDIR)/ccan/strset/strset.h \
	$(CCANDIR)/ccan/structeq/structeq.h \
	$(CCANDIR)/ccan/take/take.h \
	$(CCANDIR)/ccan/tal/grab_file/grab_file.h \
	$(CCANDIR)/ccan/tal/link/link.h \
	$(CCANDIR)/ccan/tal/path/path.h \
	$(CCANDIR)/ccan/tal/str/str.h \
	$(CCANDIR)/ccan/tal/tal.h \
	$(CCANDIR)/ccan/tcon/tcon.h \
	$(CCANDIR)/ccan/time/time.h \
	$(CCANDIR)/ccan/timer/timer.h \
	$(CCANDIR)/ccan/typesafe_cb/typesafe_cb.h \
	$(CCANDIR)/ccan/utf8/utf8.h

# We make a static library, this way linker can discard unused parts.
libccan.a: $(CCAN_OBJS)
	$(AR) r $@ $(CCAN_OBJS)

# Define VERBOSE function if it's not already defined
ifndef VERBOSE
define VERBOSE
@echo $(1) $(2)
$(2)
endef
endif

# Everything depends on the CCAN headers, and Makefile
$(CCAN_OBJS): $(CCAN_HEADERS) $(LIGHTNING_DIR)/ccan_compat.h

clean:
	rm -f $(OBJECTS) $(LIB_NAME) $(CCAN_OBJS) libccan.a

.PHONY: all clean

# These specific rules need to be kept for each object file
ccan-breakpoint.o: $(CCANDIR)/ccan/breakpoint/breakpoint.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-base64.o: $(CCANDIR)/ccan/base64/base64.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-tal.o: $(CCANDIR)/ccan/tal/tal.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-tal-str.o: $(CCANDIR)/ccan/tal/str/str.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-tal-link.o: $(CCANDIR)/ccan/tal/link/link.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-tal-path.o: $(CCANDIR)/ccan/tal/path/path.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-tal-grab_file.o: $(CCANDIR)/ccan/tal/grab_file/grab_file.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-take.o: $(CCANDIR)/ccan/take/take.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-list.o: $(CCANDIR)/ccan/list/list.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-asort.o: $(CCANDIR)/ccan/asort/asort.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-ptr_valid.o: $(CCANDIR)/ccan/ptr_valid/ptr_valid.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-read_write_all.o: $(CCANDIR)/ccan/read_write_all/read_write_all.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-str.o: $(CCANDIR)/ccan/str/str.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-opt.o: $(CCANDIR)/ccan/opt/opt.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-opt-helpers.o: $(CCANDIR)/ccan/opt/helpers.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-opt-parse.o: $(CCANDIR)/ccan/opt/parse.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-opt-usage.o: $(CCANDIR)/ccan/opt/usage.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-err.o: $(CCANDIR)/ccan/err/err.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-noerr.o: $(CCANDIR)/ccan/noerr/noerr.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-str-hex.o: $(CCANDIR)/ccan/str/hex/hex.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-crc32c.o: $(CCANDIR)/ccan/crc32c/crc32c.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-crypto-hmac.o: $(CCANDIR)/ccan/crypto/hmac_sha256/hmac_sha256.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-crypto-hkdf.o: $(CCANDIR)/ccan/crypto/hkdf_sha256/hkdf_sha256.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-crypto-shachain.o: $(CCANDIR)/ccan/crypto/shachain/shachain.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -DSHACHAIN_BITS=48 -c -o $@ $<)
ccan-crypto-sha256.o: $(CCANDIR)/ccan/crypto/sha256/sha256.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-crypto-ripemd160.o: $(CCANDIR)/ccan/crypto/ripemd160/ripemd160.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-strmap.o: $(CCANDIR)/ccan/strmap/strmap.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-strset.o: $(CCANDIR)/ccan/strset/strset.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-crypto-siphash24.o: $(CCANDIR)/ccan/crypto/siphash24/siphash24.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-htable.o: $(CCANDIR)/ccan/htable/htable.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-ilog.o: $(CCANDIR)/ccan/ilog/ilog.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-intmap.o: $(CCANDIR)/ccan/intmap/intmap.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-isaac.o: $(CCANDIR)/ccan/isaac/isaac.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-isaac64.o: $(CCANDIR)/ccan/isaac/isaac64.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-time.o: $(CCANDIR)/ccan/time/time.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-timer.o: $(CCANDIR)/ccan/timer/timer.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-io-io.o: $(CCANDIR)/ccan/io/io.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-io-poll.o: $(CCANDIR)/ccan/io/poll.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-io-fdpass.o: $(CCANDIR)/ccan/io/fdpass/fdpass.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-pipecmd.o: $(CCANDIR)/ccan/pipecmd/pipecmd.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-mem.o: $(CCANDIR)/ccan/mem/mem.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-fdpass.o: $(CCANDIR)/ccan/fdpass/fdpass.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-bitops.o: $(CCANDIR)/ccan/bitops/bitops.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-rbuf.o: $(CCANDIR)/ccan/rbuf/rbuf.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-str-base32.o: $(CCANDIR)/ccan/str/base32/base32.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-utf8.o: $(CCANDIR)/ccan/utf8/utf8.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-bitmap.o: $(CCANDIR)/ccan/bitmap/bitmap.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-membuf.o: $(CCANDIR)/ccan/membuf/membuf.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-json_escape.o: $(CCANDIR)/ccan/json_escape/json_escape.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-json_out.o: $(CCANDIR)/ccan/json_out/json_out.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-closefrom.o: $(CCANDIR)/ccan/closefrom/closefrom.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-rune-rune.o: $(CCANDIR)/ccan/rune/rune.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)
ccan-rune-coding.o: $(CCANDIR)/ccan/rune/coding.c
	$(call VERBOSE, "cc $<", $(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<)