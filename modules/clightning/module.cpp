#define template c_template  // avoid C++ keyword conflict just during includes

extern "C" {
    #include "common/bolt11.h"
    #include "bitcoin/pubkey.h"
    #include "common/node_id.h"
    #include "common/utils.h"
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

namespace bitcoinfuzz
{
    namespace module
    {
        CLightning::CLightning(void) : BaseModule("CLightning") {}

        std::optional<std::string> CLightning::deserialize_invoice(std::string str) const
        {
            return clightning_des_invoice(str.c_str());
        }
    }
}
