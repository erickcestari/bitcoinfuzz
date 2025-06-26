#include <cstdint>

extern "C" bool nbitcoin_miniscript_parse(const char* input);

extern "C" bool nbitcoin_descriptor_parse(const char* input);

extern "C" bool nbitcoin_deserialize_block(const uint8_t *data, size_t len);