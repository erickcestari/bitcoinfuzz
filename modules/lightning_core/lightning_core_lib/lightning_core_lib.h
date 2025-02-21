#pragma once
#include <cstddef>
#include <cstdint>

#ifdef __cplusplus
extern "C"
{
#endif

  char *lightning_core_des_invoice(const uint8_t *data, size_t len);

#ifdef __cplusplus
}
#endif