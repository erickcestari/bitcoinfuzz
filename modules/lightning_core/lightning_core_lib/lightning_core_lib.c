// lightning_core_lib.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lightning_core_lib.h"
#include <lightning/bolt11.h>

char *lightning_core_des_invoice(const uint8_t *data, size_t len)
{
  printf("Entering lightning_core_des_invoice\n");

  if (!data || len == 0)
  {
    printf("Invalid input: data is null or length is zero\n");
    return NULL;
  }

  // Convert binary data to null-terminated string
  char *invoice_str = malloc(len + 1);
  if (!invoice_str)
  {
    printf("Memory allocation failed\n");
    return NULL;
  }
  memcpy(invoice_str, data, len);
  invoice_str[len] = '\0';

  // Try to parse the invoice using lightning-core's bolt11_decode
  char *fail;
  struct bolt11 *b11 = bolt11_decode(invoice_str, &fail);
  free(invoice_str);

  if (!b11)
  {
    printf("Failed to parse invoice: %s\n", fail);
    if (fail)
      free(fail);
    return NULL;
  }

  // Convert bolt11 struct to string representation
  const char *description = b11->description ? b11->description : "No description";
  size_t result_len = strlen(description) + 100; // Extra space for additional info
  char *result = malloc(result_len);
  if (!result)
  {
    printf("Memory allocation failed for result\n");
    bolt11_free(b11);
    return NULL;
  }

  snprintf(result, result_len, "Amount: %llu msat, Description: %s",
           (unsigned long long)b11->msat, description);

  bolt11_free(b11);
  return result;
}