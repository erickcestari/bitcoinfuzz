#include "lightningcore_lib.h"
#include <lightning/common/bolt11.h>
#include <stdio.h>

extern "C" bool lightningcore_des_invoice(const char* input) {
    char *fail = NULL;
    
    struct bolt11 *invoice = bolt11_decode_nosig(
        NULL, // context - using NULL since we're not using tal
        input,
        NULL, // our_features
        NULL, // description
        NULL, // must_be_chain
        NULL, // hash
        NULL, // sig
        NULL, // have_n
        &fail
    );
    
    if (invoice == NULL) {
        if (fail != NULL) {
            printf("Deserialization failed: %s\n", fail);
        }
        return false;
    }

    tal_free(invoice);
    return true;
}