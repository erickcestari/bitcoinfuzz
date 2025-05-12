#define template c_template  // avoid C++ keyword conflict just during includes

extern "C" {
    #include "common/bolt11.h"
    #include "common/bolt12.h"
    #include "bitcoin/pubkey.h"
    #include "common/node_id.h"
    #include "common/utils.h"
    #include "common/setup.h"
    #include <bitcoin/chainparams.h>
    #include <ccan/tal/tal.h>
}

#undef template

#include <string>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <memory>
#include <iostream>
#include <iostream>
#include <span>
#include "module.h"

void init(int *argc, char ***argv) {
    if (!tmpctx){
        common_setup("fuzzer"); 
    }
}

struct TalFree {
    void operator()(void* ptr) const { tal_free(ptr); }
};

std::string hex_encode(const unsigned char* data, size_t len) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = 0; i < len; ++i) {
        oss << std::setw(2) << static_cast<int>(data[i]);
    }
    return oss.str();
}

std::string clightning_des_invoice(const std::string& input) {
    char* fail = nullptr;
    const struct chainparams* params = chainparams_for_network("bitcoin");

    std::unique_ptr<bolt11, TalFree> invoice(
        bolt11_decode(nullptr, input.c_str(), nullptr, nullptr, params, &fail)
    );

    if (!invoice) {
        tal_free(fail);
        return "";
    }

    std::ostringstream result;
    result << "HASH=" << hex_encode(invoice->payment_hash.u.u8, 32) << ";";

    result << "AMOUNT=";
    if (invoice->msat) {
        result << invoice->msat->millisatoshis;
    } else {
        result << "0";
    }
    result << ";";

    result << "DESCRIPTION=";
    if (invoice->description) {
        result << invoice->description;
    }
    result << ";";

    struct pubkey key;
    assert(pubkey_from_node_id(&key, &invoice->receiver_id));

    uint8_t compressed[33];
    pubkey_to_der(compressed, &key);
    result << "RECIPIENT=" << hex_encode(compressed, 33) << ";";

    result << "EXPIRY=" << invoice->expiry << ";";
    result << "TIMESTAMP=" << invoice->timestamp << ";";
    result << "ROUTING_HINTS=" << tal_count(invoice->routes) << ";";
    result << "MIN_CLTV=" << invoice->min_final_cltv_expiry;

    return result.str();
}

std::string clightning_des_invoice_request(const std::string& input) {
    char* fail = nullptr;
    const struct chainparams* params = chainparams_for_network("bitcoin");
    const char *b12 = input.c_str();
    size_t b12len = input.size();

    struct tlv_invoice_request *invoice_request = invrequest_decode(tmpctx, b12, b12len, nullptr, params, &fail);
    if (!invoice_request) {
        clean_tmpctx();
        return "";
    }

    std::ostringstream result;
    result << "CHAINS=";
    if (invoice_request->invreq_chain) {
        result << hex_encode(invoice_request->invreq_chain->shad.sha.u.u8, 32);
    } else {
        // If no chains are specified, Clightning defaults to bitcoin
        struct bitcoin_blkid chain = chainparams_for_network("bitcoin")->genesis_blockhash;
        result << hex_encode(chain.shad.sha.u.u8, 32);
    }

    result << ";METADATA=";
    if (invoice_request->invreq_metadata) {
        result << hex_encode(invoice_request->invreq_metadata, tal_bytelen(invoice_request->invreq_metadata));
    }

    if (invoice_request->invreq_amount) {
        result << ";AMOUNT=";
        result << *invoice_request->invreq_amount;
    }

    result << ";DESCRIPTION=";
    if (invoice_request->offer_description) {
        size_t len = tal_bytelen(invoice_request->offer_description);
        result.write((const char*)invoice_request->offer_description, len);
    }

    result << ";FEATURES=";
    if (invoice_request->invreq_features) {
        result << hex_encode(invoice_request->invreq_features, tal_bytelen(invoice_request->invreq_features));
    }

    result << ";ABSOLUTE_EXPIRY=";
    if (invoice_request->offer_absolute_expiry) {
        result << *invoice_request->offer_absolute_expiry;
    }

    if (invoice_request->invreq_paths) {
        for (size_t i = 0; invoice_request->invreq_paths[i] != NULL; i++) {
            struct blinded_path_hop **blinded_path_hops = invoice_request->invreq_paths[i]->path;

            for (size_t j = 0; blinded_path_hops[j] != NULL; j++) {
                result << ";BLINDED_HOP=";
                struct pubkey pubkey = blinded_path_hops[j]->blinded_node_id;
                uint8_t compressed[33];
                pubkey_to_der(compressed, &pubkey);
                result << hex_encode(compressed, 33);
            }
        }
    }

    result << ";ISSUER=";
    if (invoice_request->offer_issuer) {
        size_t len = tal_bytelen(invoice_request->offer_issuer);
        result.write((const char*)invoice_request->offer_issuer, len);
    }

    result << ";QUANTITY=";
    if (invoice_request->invreq_quantity) {
        result << *invoice_request->invreq_quantity;
    }

    result << ";ISSUER_ID=";
    if (invoice_request->offer_issuer_id) {
        uint8_t compressed[33];
        pubkey_to_der(compressed, invoice_request->offer_issuer_id);
        result << hex_encode(compressed, 33);
    }

    result << ";NOTE=";
    if (invoice_request->invreq_payer_note) {
        size_t len = tal_bytelen(invoice_request->invreq_payer_note);
        result.write((const char*)invoice_request->invreq_payer_note, len);
    }
    
    clean_tmpctx();
    return result.str();
}

namespace bitcoinfuzz
{
    namespace module
    {
        CLightning::CLightning(void) : BaseModule("CLightning") {
            init(nullptr, nullptr);
        }

        std::optional<std::string> CLightning::deserialize_invoice(std::string str) const
        {
            return clightning_des_invoice(str.c_str());
        }

        std::optional<std::string> CLightning::deserialize_invoice_request(std::string str) const
        {
            return clightning_des_invoice_request(str.c_str());
        }
    }
}
