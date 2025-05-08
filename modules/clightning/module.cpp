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

void init(int *argc, char ***argv) { common_setup("fuzzer"); }

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

std::string clightning_des_offer(const std::string& input) {
    char* fail = nullptr;
    const struct chainparams* params = chainparams_for_network("bitcoin");
    const char *b12 = input.c_str();
    size_t b12len = input.size();
    std::unique_ptr<tlv_offer, TalFree> offer(
        offer_decode(nullptr, b12, b12len, nullptr, params, &fail)
    );

    if (!offer) {
        tal_free(fail);
        return "";
    }

    std::ostringstream result;
    if (offer->offer_chains) {
        result << "CHAINS=" << hex_encode(offer->offer_chains->shad.sha.u.u8, 32) << ";";
    }

    // result << "METADATA=" << offer->offer_metadata << ";";

    // result << "AMOUNT=";
    // if (offer->offer_amount) {
    //     result << offer->offer_amount;
    // } else {
    //     result << "0";
    // }
    // result << ";";

    // result << "CURRENCY=";
    // if (offer->offer_currency) {
    //     result << offer->offer_currency;
    // } else {
    //     result << "0";
    // }
    // result << ";";

    result << "DESCRIPTION=";
    if (offer->offer_description) {
        size_t len = tal_bytelen(offer->offer_description);
        result.write((const char*)offer->offer_description, len);
    }
    result << ";";

    // result << "FEATURES=";
    // result << offer->offer_features << ";";

    result << "ABSOLUTE_EXPIRY=";
    if (offer->offer_absolute_expiry) {
        result << offer->offer_absolute_expiry;
    }
    result << ";";

    // result << "BLINDED_PATHS=";
    
    // result << ";";

    // result << "ISSUER=";
    // if (offer->offer_issuer) {
    //     result << offer->offer_issuer;
    // }
    // result << ";";

    result << "QUANTITY=";
    if (offer->offer_quantity_max) {
        result << offer->offer_quantity_max;
    }
    result << ";";

    result << "ISSUER_ID=";
    if (offer->offer_issuer_id) {
        uint8_t compressed[33];
        pubkey_to_der(compressed, offer->offer_issuer_id);
        result << hex_encode(compressed, 33);
    }

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

        std::optional<std::string> CLightning::deserialize_offer(std::string str) const
        {
            return clightning_des_offer(str.c_str());
        }
    }
}
