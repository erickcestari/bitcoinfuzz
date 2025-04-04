#include "clightning_lib.h"
#include "common/bolt11.h"
#include <stdio.h>
#include <string.h>
#include <bitcoin/chainparams.h>

bool clightning_des_invoice(const char* input) {
    char *fail = NULL;
    struct bolt11 *invoice = NULL;
    const struct chainparams *params = chainparams_for_network("bitcoin");

    invoice = bolt11_decode(
        NULL,
        input,
        NULL,
        NULL,
        params,
        &fail
    );

    if (invoice == NULL) {
        if (fail != NULL) {
            printf("Deserialization failed: %s\n", fail);
            tal_free(fail);
        }
        return false;
    }

    tal_free(invoice);
    return true;
}