#define template c_template  // avoid C++ keyword conflict just during includes

extern "C" {
    #include "common/bolt11.h"
    #include "common/bolt12.h"
    #include "bitcoin/pubkey.h"
    #include "common/node_id.h"
    #include "common/utils.h"
    #include "common/setup.h"
    #include "common/addr.h"
    #include <bitcoin/chainparams.h>
    #include <wire/peer_wiregen.h>
    #include <gossipd/sigcheck.h>
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

std::string hex_encode(const unsigned char* data, size_t len) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = 0; i < len; ++i) {
        oss << std::setw(2) << static_cast<int>(data[i]);
    }
    return oss.str();
}

std::optional<std::string> clightning_des_invoice(const std::string& input) {
    char* fail = nullptr;
    const struct chainparams* params = chainparams_for_network("bitcoin");

    struct bolt11 *invoice = bolt11_decode(tmpctx, input.c_str(), nullptr, nullptr, params, &fail);

    if (!invoice) {
        // Handle invoices without payment secrets by returning null
        // This is needed because LND don't require payment secrets,
        // and we need to maintain compatibility with that implementation
        if (strcmp(fail, "Missing required payment secret (s field)") == 0) {
            clean_tmpctx();
            return std::nullopt;
        }
        clean_tmpctx();
        return "";
    }

    std::ostringstream result;
    result << "HASH=" << hex_encode(invoice->payment_hash.u.u8, 32);

    result << ";PAYMENT_SECRET=";
    if (invoice->payment_secret) {
        result << hex_encode(invoice->payment_secret->data, 32);
    }

    result << ";AMOUNT=";
    if (invoice->msat) {
        result << invoice->msat->millisatoshis;
    } else {
        result << "0";
    }

    result << ";DESCRIPTION=";
    if (invoice->description) {
        result << invoice->description;
    }

    result << ";METADATA=";
    if (invoice->metadata) {
        result << hex_encode(invoice->metadata, tal_bytelen(invoice->metadata));
    }

    struct pubkey key;
    assert(pubkey_from_node_id(&key, &invoice->receiver_id));

    uint8_t compressed[33];
    pubkey_to_der(compressed, &key);
    result << ";RECIPIENT=" << hex_encode(compressed, 33);

    result << ";DESCRIPTION_HASH=";
    if (invoice->description_hash) {
        result << hex_encode(invoice->description_hash->u.u8, 32);
    }

    // Convert the expiry time to seconds, ensuring consistent overflow behavior
    // with other implementations like LND. The multiplication and division by 1000000000
    // may appear redundant, but it's intentionally mirroring the nanosecond conversion 
    // logic used in LND to ensure the same overflow characteristics.
    result << ";EXPIRY=" << (invoice->expiry * 1000000000) / 1000000000;

    result << ";TIMESTAMP=" << invoice->timestamp;

    result << ";FALLBACK_ADDRESS=";
    if (invoice->fallbacks) {
        // Use only the first fallback address for compatibility with LND,
        // which ignores additional fallback fields.
        // See: https://github.com/lightningnetwork/lnd/issues/9591
        std::string addr = encode_scriptpubkey_to_addr(tmpctx, params, invoice->fallbacks[0]);
        result << addr;
    }

    if (invoice->routes) {
        for (size_t i = 0; i < tal_count(invoice->routes); i++) {
            struct route_info *route = invoice->routes[i];
            result << ";PRIVATE_ROUTE=[";
            for (size_t j = 0; j < tal_count(route); j++) {
                if (j == 0) result << "(";
                else result << ",(";
                
                struct pubkey key;
                assert(pubkey_from_node_id(&key, &route[j].pubkey));
                uint8_t compressed[33];
                pubkey_to_der(compressed, &key);
                result << "NODE_ID=" << hex_encode(compressed, 33);
                result << ",SHORT_CHANNEL_ID=" << route[j].short_channel_id.u64;
                result << ",FEES=" << route[j].fee_base_msat;
                result << ",CLTV_EXPIRY_DELTA=" << route[j].cltv_expiry_delta;
                result << ",PROPORTIONAL_MILLIONTHS=" << route[j].fee_proportional_millionths;
                result << ")";
            }
            result << "]";
        }
    }

    result << ";MIN_CLTV=" << invoice->min_final_cltv_expiry;

    result << ";FEATURES=";
    if (invoice->features) {
        result << hex_encode(invoice->features, tal_bytelen(invoice->features));
    }

    clean_tmpctx();
    return result.str();
}

std::string clightning_des_offer(const std::string_view input) {
    char* fail = nullptr;

    // Get the truncated length of the string (in case it contains null bytes)
    size_t c_string_len = strnlen(input.data(), input.size());

    struct tlv_offer *offer = offer_decode(tmpctx, input.data(), c_string_len, /*our_features=*/nullptr, /*must_be_chain=*/nullptr, &fail);
    if (!offer) {
        clean_tmpctx();
        return "";
    }

    std::ostringstream result;
    result << "CHAINS=";
    if (offer->offer_chains && tal_count(offer->offer_chains) > 0) {
        for (size_t i = 0; i < tal_count(offer->offer_chains); i++) {
            if (i > 0) result << ";";
            result << hex_encode(offer->offer_chains[i].shad.sha.u.u8, 32);
        }
    } else {
        // If no chains are specified, Clightning defaults to bitcoin
        struct bitcoin_blkid chain = chainparams_for_network("bitcoin")->genesis_blockhash;
        result << hex_encode(chain.shad.sha.u.u8, 32);
    }

    result << ";METADATA=";
    if (offer->offer_metadata) {
        result << hex_encode(offer->offer_metadata, tal_bytelen(offer->offer_metadata));
    }

    if (offer->offer_amount) {
        result << ";AMOUNT=";
        result << *offer->offer_amount;
    }

    if (offer->offer_currency) {
        result << ";CURRENCY=";
        size_t len = tal_bytelen(offer->offer_currency);
        result.write((const char*)offer->offer_currency, len);
    }

    result << ";DESCRIPTION=";
    if (offer->offer_description) {
        size_t len = tal_bytelen(offer->offer_description);
        result.write((const char*)offer->offer_description, len);
    }

    result << ";FEATURES=";
    if (offer->offer_features) {
        result << hex_encode(offer->offer_features, tal_bytelen(offer->offer_features));
    }

    result << ";ABSOLUTE_EXPIRY=";
    if (offer->offer_absolute_expiry) {
        result << *offer->offer_absolute_expiry;
    }

    if (offer->offer_paths) {
        for (size_t i = 0; i < tal_count(offer->offer_paths); i++) {
            struct blinded_path_hop **blinded_path_hops = offer->offer_paths[i]->path;

            for (size_t j = 0; j < tal_count(blinded_path_hops); j++) {
                result << ";PATH_" << i << "_HOP=";
                struct pubkey pubkey = blinded_path_hops[j]->blinded_node_id;
                uint8_t compressed[33];
                pubkey_to_der(compressed, &pubkey);
                result << hex_encode(compressed, 33);
            }
        }
    }

    result << ";ISSUER=";
    if (offer->offer_issuer) {
        size_t len = tal_bytelen(offer->offer_issuer);
        result.write((const char*)offer->offer_issuer, len);
    }

    result << ";QUANTITY=";
    if (offer->offer_quantity_max) {
        result << *offer->offer_quantity_max;
    }

    result << ";ISSUER_ID=";
    if (offer->offer_issuer_id) {
        uint8_t compressed[33];
        pubkey_to_der(compressed, offer->offer_issuer_id);
        result << hex_encode(compressed, 33);
    }
    
    clean_tmpctx();
    return result.str();
}

std::optional<std::string> clightning_parse_gossip_message(std::span<const uint8_t> buffer) {
    u8 *msg = (u8 *) tal_arr(tmpctx, u8, buffer.size());
    memcpy(msg, buffer.data(), buffer.size());
    peer_wire msg_type = (enum peer_wire)fromwire_peektype(msg);

    std::string result;
    
    if (msg_type == WIRE_CHANNEL_ANNOUNCEMENT) {
        secp256k1_ecdsa_signature node_signature_1, node_signature_2;
        secp256k1_ecdsa_signature bitcoin_signature_1, bitcoin_signature_2;
        u8 *features;
        struct bitcoin_blkid chain_hash;
        struct short_channel_id scid;
        struct node_id node_id_1;
        struct node_id node_id_2;
        struct pubkey bitcoin_key_1;
        struct pubkey bitcoin_key_2;

        if (!fromwire_channel_announcement(tmpctx, msg, &node_signature_1, &node_signature_2,
                        &bitcoin_signature_1, &bitcoin_signature_2, &features, &chain_hash,
                        &scid, &node_id_1, &node_id_2, &bitcoin_key_1, &bitcoin_key_2)) {
            clean_tmpctx();
            return "";
        }

        const char* fail;
        fail = sigcheck_channel_announcement(tmpctx, &node_id_1, &node_id_2, &bitcoin_key_1, &bitcoin_key_2,
                        &node_signature_1 , &node_signature_2, &bitcoin_signature_1, &bitcoin_signature_2, msg);
        if (fail) {
            clean_tmpctx();
            return "";
        }

        clean_tmpctx();
        return "256";
    }

    if (msg_type == WIRE_NODE_ANNOUNCEMENT) {
        struct gossmap_node *node;
        u8 *nannounce;
        struct node_id id;
        secp256k1_ecdsa_signature signature;
        u32 timestamp;
        u8 *addresses, *features;
        u8 rgb_color[3], alias[32];
        struct tlv_node_ann_tlvs *na_tlvs;
        struct wireaddr *alladdrs, *addrs[3];

        if (!fromwire_node_announcement(tmpctx, msg, &signature, &features, &timestamp, &id, rgb_color, alias, &addresses, &na_tlvs)) {
            clean_tmpctx();
            return "";
        }

        const char* fail;
        fail = sigcheck_node_announcement(tmpctx, &id, &signature, msg);
        if (fail) {
            clean_tmpctx();
            return "";
        }

        clean_tmpctx();
        return "257";
    }

    if (msg_type == WIRE_QUERY_CHANNEL_RANGE) {
        struct bitcoin_blkid chain_hash;
        u32 first_blocknum, number_of_blocks;
        struct tlv_query_channel_range_tlvs *tlvs;

        if (!fromwire_query_channel_range(tmpctx, msg, &chain_hash, &first_blocknum, &number_of_blocks, &tlvs)) {
            clean_tmpctx();
            return "";
        }
        if (tal_count(tlvs) != 0) {
            clean_tmpctx();
            return std::nullopt;
        }
        clean_tmpctx();
        return "263";
    }

    if (msg_type == WIRE_GOSSIP_TIMESTAMP_FILTER) {
        struct bitcoin_blkid chain_hash;
        u32 first_timestamp, timestamp_range;

        // C-lightning ignores extra data.
        // rust-lightning returns error.
        // LND accepts non-tlv extra data.
        size_t msg_size = tal_bytelen(msg);
        if (msg_size > 42) {
            clean_tmpctx();
            return std::nullopt;
        }
        if (!fromwire_gossip_timestamp_filter(msg, &chain_hash, &first_timestamp, &timestamp_range)) {
            clean_tmpctx();
            return "";
        }
        clean_tmpctx();
        return "265";
    }
    clean_tmpctx();
    return "";
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
            return clightning_des_offer(str);
        }

        std::optional<std::string> CLightning::parse_gossip_message(std::span<const uint8_t> buffer) const
        {
            return clightning_parse_gossip_message(buffer);
        }
    }
}
