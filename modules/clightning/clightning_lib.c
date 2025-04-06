#include "clightning_lib.h"
#include "common/bolt11.h"
#include "bitcoin/pubkey.h"
#include "common/node_id.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <bitcoin/chainparams.h>

static char* hex_encode(const unsigned char* data, size_t len) {
    char* hex = malloc(len * 2 + 1);
    if (!hex) return NULL;

    for (size_t i = 0; i < len; ++i) {
        sprintf(hex + i * 2, "%02x", data[i]);
    }
    hex[len * 2] = '\0';
    return hex;
}

bool clightning_des_invoice(const char* input) {
    char *fail = NULL;
    struct bolt11 *invoice = NULL;
    struct pubkey key;
    const struct chainparams *params = chainparams_for_network("bitcoin");

    invoice = bolt11_decode(NULL, input, NULL, NULL, params, &fail);
    if (!invoice) {
        if (fail) {
            fprintf(stderr, "Deserialization failed: %s\n", fail);
            tal_free(fail);
        }
        return false;
    }

    // Encode payment_hash
    char* hash_str = hex_encode(invoice->payment_hash.u.u8, 32);
    if (!hash_str) {
        perror("Failed to allocate memory for hash string");
        tal_free(invoice);
        return false;
    }
    printf("PAYMENT-HASH: %s\n", hash_str);
    free(hash_str);

    // Amount
    if (invoice->msat) {
        printf("AMOUNT: %ld\n", invoice->msat->millisatoshis);
    } else {
        printf("AMOUNT: Not specified in the invoice.\n");
    }

    // Description
    printf("DESCRIPTION: %s\n", invoice->description);

    // Destination pubkey
    if (!pubkey_from_node_id(&key, &invoice->receiver_id)) {
        fprintf(stderr, "Failed to extract pubkey from node_id\n");
        tal_free(invoice);
        return false;
    }

    u8 compressed[33];
    size_t len = sizeof(compressed);

    pubkey_to_der(compressed, &key);

    char* destination_str = hex_encode(compressed, len);
    if (!destination_str) {
        perror("Failed to allocate memory for compressed pubkey string");
        tal_free(invoice);
        return false;
    }

    printf("RECIPIENT: %s\n", destination_str);
    free(destination_str);

    printf("EXPIRY: %ld\n", invoice->expiry);

    printf("TIMESTAMP: %ld\n", invoice->timestamp);

    printf("ROUTING HINTS: %zu\n", tal_count(invoice->routes));

    printf("MIN CLTV: %u\n", invoice->min_final_cltv_expiry);

    tal_free(invoice);
    return true;
}
