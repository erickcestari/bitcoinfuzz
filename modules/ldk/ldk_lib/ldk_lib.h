#include <cstdint>

extern "C" char* ldk_des_invoice(const char* input);

extern "C" void ldk_free_string(const char* ptr);