#define template c_template  // avoid C++ keyword conflict just during includes

extern "C" {
    #include "common/bolt11.h"
    #include "common/bolt12.h"
    #include "bitcoin/pubkey.h"
    #include "common/node_id.h"
    #include "common/utils.h"
    #include "common/setup.h"
    #include <common/decode_array.h>
    #include "common/addr.h"
    #include <common/ping.h>
    #include <bitcoin/chainparams.h>
    #include <common/derive_basepoints.h>
    #include <wire/peer_wiregen.h>
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

struct CleanTmpCtxGuard {
    CleanTmpCtxGuard() noexcept = default;
    ~CleanTmpCtxGuard() noexcept { clean_tmpctx(); }
    CleanTmpCtxGuard(const CleanTmpCtxGuard&) = delete;
    CleanTmpCtxGuard& operator=(const CleanTmpCtxGuard&) = delete;
};

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
    CleanTmpCtxGuard _cleanup;

    char* fail = nullptr;
    const struct chainparams* params = chainparams_for_network("bitcoin");

    struct bolt11 *invoice = bolt11_decode(tmpctx, input.c_str(), nullptr, nullptr, params, &fail);

    if (!invoice) {
        // Handle invoices without payment secrets by returning null
        // This is needed because LND don't require payment secrets,
        // and we need to maintain compatibility with that implementation
        if (strcmp(fail, "Missing required payment secret (s field)") == 0) {
            return std::nullopt;
        }
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

    return result.str();
}

std::string clightning_des_offer(const std::string_view input) {
    CleanTmpCtxGuard _cleanup;

    char* fail = nullptr;

    // Get the truncated length of the string (in case it contains null bytes)
    size_t c_string_len = strnlen(input.data(), input.size());

    struct tlv_offer *offer = offer_decode(tmpctx, input.data(), c_string_len, /*our_features=*/nullptr, /*must_be_chain=*/nullptr, &fail);
    if (!offer) {
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
    
    return result.str();
}

std::optional<std::string> clightning_parse_p2p_lightning_message(std::span<const uint8_t> buffer) {
    CleanTmpCtxGuard _cleanup;

    u8 *msg = tal_arr(tmpctx, u8, buffer.size());
    memcpy(msg, buffer.data(), buffer.size());
    peer_wire msg_type = static_cast<enum peer_wire>(fromwire_peektype(msg));
    std::ostringstream result;

    if (msg_type == WIRE_WARNING) {
	    struct channel_id channel;
        u8 *data;

        if (!fromwire_warning(tmpctx, msg, &channel, &data)) {
            return "";
        }

        result << "MSG_TYPE=warning;CHANNEL_ID=" << hex_encode(channel.id, 32);
        result << ";DATA=" << tal_hex(tmpctx, data);
    } else if (msg_type == WIRE_ERROR) {
	    struct channel_id channel;
        u8 *data;

        if (!fromwire_error(tmpctx, msg, &channel, &data)) {
            return "";
        }

        result << "MSG_TYPE=error;CHANNEL_ID=" << hex_encode(channel.id, 32);
        result << ";DATA=" << tal_hex(tmpctx, data);
    } else if (msg_type == WIRE_PING) {
        u16 num_pong_bytes;
	    u8 *ignored;
        u8 *pong;

        if (!check_ping_make_pong(tmpctx, msg, &pong)) {
            return "";
        }
        if (!pong) {
            return "";
        }
        fromwire_ping(tmpctx, msg, &num_pong_bytes, &ignored);

        result << "MSG_TYPE=ping;NUM_PONG_BYTES=" << num_pong_bytes;
        result << ";IGNORED=" << tal_bytelen(ignored);
    } else if (msg_type == WIRE_PONG) {
	    u8 *ignored;

        if (!fromwire_pong(tmpctx, msg, &ignored)) {
            return "";
        }

        result << "MSG_TYPE=pong;IGNORED=" << tal_bytelen(ignored);
    } else if (msg_type == WIRE_ACCEPT_CHANNEL) {
        struct basepoints theirs;
        struct pubkey their_funding_pubkey, first_per_commitment_point;
        struct channel_id channel_id;
        u16 to_self_delay, max_accepted_htlcs;
        struct tlv_accept_channel_tlvs *accept_tlvs;
        struct amount_msat max_htlc_value_in_flight, htlc_minimum;
        struct amount_sat dust_limit, channel_reserve;
        u32 minimum_depth;

        if (!fromwire_accept_channel(tmpctx, msg,
                    &channel_id,
                    &dust_limit,
                    &max_htlc_value_in_flight,
                    &channel_reserve,
                    &htlc_minimum,
                    &minimum_depth,
                    &to_self_delay,
                    &max_accepted_htlcs,
                    &their_funding_pubkey,
                    &theirs.revocation,
                    &theirs.payment,
                    &theirs.delayed_payment,
                    &theirs.htlc,
                    &first_per_commitment_point,
                    &accept_tlvs)) {
                        return "";
                    }

        result << "MSG_TYPE=accept_channel";
        result << ";TEMPORARY_CHANNEL_ID=" << fmt_channel_id(tmpctx, &channel_id);
        result << ";DUST_LIMIT_SATOSHIS=" << dust_limit.satoshis;
        result << ";MAX_HTLC_IN_FLIGHT_MSAT=" << max_htlc_value_in_flight.millisatoshis;
        result << ";CHANNEL_RESERVE_SATOSHIS=" << channel_reserve.satoshis;
        result << ";HTLC_MINIMUM_MSAT=" << htlc_minimum.millisatoshis;
        result << ";MINIMUM_DEPTH=" << minimum_depth;
        result << ";TO_SELF_DELAY=" << to_self_delay;
        result << ";MAX_ACCEPTED_HTLCS=" << max_accepted_htlcs;
        result << ";FUNDING_PUBKEY=" << fmt_pubkey(tmpctx, &their_funding_pubkey);
        result << ";REVOCATION_BASEPOINT=" << fmt_pubkey(tmpctx, &theirs.revocation);
        result << ";PAYMENT_BASEPOINT=" << fmt_pubkey(tmpctx, &theirs.payment);
        result << ";DELAYED_PAYMENT_BASEPOINT=" << fmt_pubkey(tmpctx, &theirs.delayed_payment);
        result << ";HTLC_BASEPOINT=" << fmt_pubkey(tmpctx, &theirs.htlc);
        result << ";FIRST_PER_COMMITMENT_POINT=" << fmt_pubkey(tmpctx, &first_per_commitment_point);

        if (accept_tlvs && accept_tlvs->upfront_shutdown_script) {
            result << ";UPFRONT_SHUTDOWN_SCRIPT=";
            result << tal_hex(tmpctx, accept_tlvs->upfront_shutdown_script);
        }

        if (accept_tlvs && accept_tlvs->channel_type) {
            result << ";CHANNEL_TYPE=";
            result << tal_hex(tmpctx, accept_tlvs->channel_type);
        }
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
            return clightning_des_offer(str);
        }

        std::optional<std::string> CLightning::parse_p2p_lightning_message(std::span<const uint8_t> buffer) const
        {
            return clightning_parse_p2p_lightning_message(buffer);
        }
    }
}
