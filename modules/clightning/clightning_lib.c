#include "clightning_lib.h"
#include "common/bolt11.h"
#include "bitcoin/pubkey.h"
#include "common/node_id.h"
#include <stdio.h>
#include <string.h>
#include <bitcoin/chainparams.h>

bool clightning_des_invoice(const char* input) {
    char *fail = NULL;
    struct bolt11 *invoice = NULL;
    struct pubkey key;
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

    char* hash_str = malloc(65); // 32 bytes * 2 hex chars + 1 null terminator
    if (hash_str == NULL) {
        perror("Failed to allocate memory for hash string");
        tal_free(invoice);
        return false;
    }

    for (int i = 0; i < 32; ++i) {
        sprintf(hash_str + (i * 2), "%02x", invoice->payment_hash.u.u8[i]);
    }
    hash_str[64] = '\0';

    printf("PAYMENT-HASH: %s\n", hash_str);

    if (invoice->msat) {
        printf("AMOUNT: %ld\n", invoice->msat->millisatoshis);
    } else {
        printf("AMOUNT: Not specified in the invoice.\n");
    }

    printf("DESCRIPTION: %s\n", invoice->description);

    if (!pubkey_from_node_id(&key, &invoice->receiver_id)) {
        fprintf(stderr, "Failed to extract pubkey from node_id\n");
        tal_free(invoice);
        free(hash_str);
        return false;
    }

    printf("pubkey bytes: %s\n", key.pubkey.data);

    free(hash_str);
    tal_free(invoice);
    return true;

    tal_free(invoice);
    return true;
}
