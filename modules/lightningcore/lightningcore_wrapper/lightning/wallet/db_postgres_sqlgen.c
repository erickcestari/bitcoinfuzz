#ifndef LIGHTNINGD_WALLET_GEN_DB_POSTGRES
#define LIGHTNINGD_WALLET_GEN_DB_POSTGRES

#include <config.h>
#include <ccan/array_size/array_size.h>
#include <db/common.h>
#include <db/utils.h>

#if HAVE_POSTGRES
static const struct sqlname_map col_table0[] = {
    { "version", 0 },
};

static const struct sqlname_map col_table1[] = {
    { "intval", 0 },
};

static const struct sqlname_map col_table4[] = {
    { "intval", 0 },
};

static const struct sqlname_map col_table249[] = {
    { NULL, -1 },
    { "type", 0 },
    { "prev_out_index", 3 },
    { "channel_id", 4 },
    { "commitment_point", 6 },
    { "prev_out_tx", 2 },
    { NULL, -1 },
    { "peer_id", 5 },
    { "keyindex", 1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table251[] = {
    { "id", 0 },
    { "funding_tx_outnum", 2 },
    { NULL, -1 },
    { NULL, -1 },
    { "funding_tx_id", 1 },
};

static const struct sqlname_map col_table253[] = {
    { NULL, -1 },
    { "channels.id", 0 },
    { "peers.node_id", 1 },
};

static const struct sqlname_map col_table257[] = {
    { "inflight.funding_tx_id", 6 },
    { NULL, -1 },
    { NULL, -1 },
    { "inflight.last_tx", 3 },
    { NULL, -1 },
    { NULL, -1 },
    { "p.node_id", 1 },
    { "c.fundingkey_remote", 2 },
    { NULL, -1 },
    { NULL, -1 },
    { "inflight.last_sig", 4 },
    { "c.id", 0 },
    { "inflight.funding_satoshi", 5 },
};

static const struct sqlname_map col_table259[] = {
    { "c.last_sig", 5 },
    { "p.node_id", 1 },
    { NULL, -1 },
    { "c.id", 0 },
    { "c.last_tx", 2 },
    { "c.funding_satoshi", 3 },
    { "c.fundingkey_remote", 4 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table261[] = {
    { "short_channel_id", 0 },
};

static const struct sqlname_map col_table264[] = {
    { "id", 0 },
    { "failchannel", 1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table267[] = {
    { NULL, -1 },
    { NULL, -1 },
    { "local_static_remotekey_start", 1 },
    { "option_anchor_outputs", 2 },
    { "alias_remote", 4 },
    { "minimum_depth", 5 },
    { NULL, -1 },
    { NULL, -1 },
    { "id", 0 },
    { "channel_flags", 3 },
    { NULL, -1 },
};

static const struct sqlname_map col_table269[] = {
    { "MAX(id)", 0 },
};

static const struct sqlname_map col_table272[] = {
    { "MAX(id)", 0 },
};

static const struct sqlname_map col_table276[] = {
    { "MAX(rowid)", 0 },
};

static const struct sqlname_map col_table277[] = {
    { "id", 0 },
    { "state", 1 },
    { "last_tx", 2 },
    { NULL, -1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table278[] = {
    { "id", 1 },
    { "bolt11", 0 },
    { NULL, -1 },
};

static const struct sqlname_map col_table280[] = {
    { "id", 1 },
    { "bolt11", 0 },
    { NULL, -1 },
};

static const struct sqlname_map col_table282[] = {
    { "id", 0 },
};

static const struct sqlname_map col_table285[] = {
    { "id", 0 },
};

static const struct sqlname_map col_table287[] = {
    { "MIN(expiry_time)", 0 },
};

static const struct sqlname_map col_table289[] = {
    { "id", 0 },
};

static const struct sqlname_map col_table290[] = {
    { "id", 0 },
};

static const struct sqlname_map col_table292[] = {
    { "invoice_id", 0 },
};

static const struct sqlname_map col_table293[] = {
    { "id", 0 },
};

static const struct sqlname_map col_table296[] = {
    { "id", 0 },
};

static const struct sqlname_map col_table297[] = {
    { "id", 0 },
};

static const struct sqlname_map col_table298[] = {
    { "state", 0 },
};

static const struct sqlname_map col_table299[] = {
    { "local_offer_id", 0 },
};

static const struct sqlname_map col_table301[] = {
    { "id", 0 },
};

static const struct sqlname_map col_table302[] = {
    { "msatoshi", 4 },
    { "pay_index", 6 },
    { "paid_outnum", 10 },
    { "updated_index", 16 },
    { "features", 13 },
    { NULL, -1 },
    { "expiry_time", 5 },
    { "msatoshi_received", 7 },
    { "description", 12 },
    { NULL, -1 },
    { "bolt11", 11 },
    { "local_offer_id", 14 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "label", 3 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "payment_hash", 2 },
    { NULL, -1 },
    { "paid_txid", 9 },
    { "state", 0 },
    { "id", 15 },
    { "payment_key", 1 },
    { "paid_timestamp", 8 },
};

static const struct sqlname_map col_table303[] = {
    { "outnum", 1 },
    { "txid", 0 },
    { NULL, -1 },
};

static const struct sqlname_map col_table304[] = {
    { "*", 0 },
};

static const struct sqlname_map col_table308[] = {
    { "prev_out_index", 1 },
    { "peer_id", 7 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "csv_lock", 14 },
    { NULL, -1 },
    { NULL, -1 },
    { "type", 3 },
    { "option_anchor_outputs", 9 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "channel_id", 6 },
    { NULL, -1 },
    { "scriptpubkey", 12 },
    { "reserved_til", 13 },
    { "is_in_coinbase", 15 },
    { NULL, -1 },
    { NULL, -1 },
    { "commitment_point", 8 },
    { NULL, -1 },
    { "status", 4 },
    { "prev_out_tx", 0 },
    { NULL, -1 },
    { "confirmation_height", 10 },
    { NULL, -1 },
    { "keyindex", 5 },
    { "value", 2 },
    { NULL, -1 },
    { "spend_height", 11 },
};

static const struct sqlname_map col_table309[] = {
    { "prev_out_index", 1 },
    { "peer_id", 7 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "csv_lock", 14 },
    { NULL, -1 },
    { NULL, -1 },
    { "type", 3 },
    { "option_anchor_outputs", 9 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "channel_id", 6 },
    { NULL, -1 },
    { "scriptpubkey", 12 },
    { "reserved_til", 13 },
    { "is_in_coinbase", 15 },
    { NULL, -1 },
    { NULL, -1 },
    { "commitment_point", 8 },
    { NULL, -1 },
    { "status", 4 },
    { "prev_out_tx", 0 },
    { NULL, -1 },
    { "confirmation_height", 10 },
    { NULL, -1 },
    { "keyindex", 5 },
    { "value", 2 },
    { NULL, -1 },
    { "spend_height", 11 },
};

static const struct sqlname_map col_table310[] = {
    { "prev_out_index", 1 },
    { "peer_id", 7 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "csv_lock", 14 },
    { NULL, -1 },
    { NULL, -1 },
    { "type", 3 },
    { "option_anchor_outputs", 9 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "channel_id", 6 },
    { NULL, -1 },
    { "scriptpubkey", 12 },
    { "reserved_til", 13 },
    { "is_in_coinbase", 15 },
    { NULL, -1 },
    { NULL, -1 },
    { "commitment_point", 8 },
    { NULL, -1 },
    { "status", 4 },
    { "prev_out_tx", 0 },
    { NULL, -1 },
    { "confirmation_height", 10 },
    { NULL, -1 },
    { "keyindex", 5 },
    { "value", 2 },
    { NULL, -1 },
    { "spend_height", 11 },
};

static const struct sqlname_map col_table311[] = {
    { "prev_out_index", 1 },
    { "peer_id", 7 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "csv_lock", 14 },
    { NULL, -1 },
    { NULL, -1 },
    { "type", 3 },
    { "option_anchor_outputs", 9 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "channel_id", 6 },
    { NULL, -1 },
    { "scriptpubkey", 12 },
    { "reserved_til", 13 },
    { "is_in_coinbase", 15 },
    { NULL, -1 },
    { NULL, -1 },
    { "commitment_point", 8 },
    { NULL, -1 },
    { "status", 4 },
    { "prev_out_tx", 0 },
    { NULL, -1 },
    { "confirmation_height", 10 },
    { NULL, -1 },
    { "keyindex", 5 },
    { "value", 2 },
    { NULL, -1 },
    { "spend_height", 11 },
};

static const struct sqlname_map col_table313[] = {
    { "prev_out_index", 1 },
    { "peer_id", 7 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "csv_lock", 14 },
    { NULL, -1 },
    { NULL, -1 },
    { "type", 3 },
    { "option_anchor_outputs", 9 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "channel_id", 6 },
    { NULL, -1 },
    { "scriptpubkey", 12 },
    { "reserved_til", 13 },
    { "is_in_coinbase", 15 },
    { NULL, -1 },
    { NULL, -1 },
    { "commitment_point", 8 },
    { NULL, -1 },
    { "status", 4 },
    { "prev_out_tx", 0 },
    { NULL, -1 },
    { "confirmation_height", 10 },
    { NULL, -1 },
    { "keyindex", 5 },
    { "value", 2 },
    { NULL, -1 },
    { "spend_height", 11 },
};

static const struct sqlname_map col_table314[] = {
    { "prev_out_index", 1 },
    { "peer_id", 7 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "csv_lock", 14 },
    { NULL, -1 },
    { NULL, -1 },
    { "type", 3 },
    { "option_anchor_outputs", 9 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "channel_id", 6 },
    { NULL, -1 },
    { "scriptpubkey", 12 },
    { "reserved_til", 13 },
    { "is_in_coinbase", 15 },
    { NULL, -1 },
    { NULL, -1 },
    { "commitment_point", 8 },
    { NULL, -1 },
    { "status", 4 },
    { "prev_out_tx", 0 },
    { NULL, -1 },
    { "confirmation_height", 10 },
    { NULL, -1 },
    { "keyindex", 5 },
    { "value", 2 },
    { NULL, -1 },
    { "spend_height", 11 },
};

static const struct sqlname_map col_table316[] = {
    { "addrtype", 0 },
};

static const struct sqlname_map col_table322[] = {
    { NULL, -1 },
    { "min_index", 0 },
    { "num_valid", 1 },
};

static const struct sqlname_map col_table323[] = {
    { "idx", 0 },
    { NULL, -1 },
    { "hash", 1 },
    { "pos", 2 },
    { NULL, -1 },
};

static const struct sqlname_map col_table324[] = {
    { "id", 0 },
    { "node_id", 1 },
    { "address", 2 },
    { "last_known_address", 4 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "feature_bits", 3 },
    { NULL, -1 },
};

static const struct sqlname_map col_table325[] = {
    { "signature", 0 },
};

static const struct sqlname_map col_table326[] = {
    { "remote_ann_bitcoin_sig", 1 },
    { NULL, -1 },
    { "remote_ann_node_sig", 0 },
};

static const struct sqlname_map col_table328[] = {
    { "hstate", 0 },
    { NULL, -1 },
    { "feerate_per_kw", 1 },
};

static const struct sqlname_map col_table329[] = {
    { "hstate", 0 },
    { "blockheight", 1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table334[] = {
    { "funding_tx_id", 0 },
    { "lease_commit_sig", 10 },
    { "lease_chan_max_msat", 11 },
    { "lease_blockheight_start", 13 },
    { "lease_expiry", 9 },
    { "remote_funding", 19 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "force_sign_first", 18 },
    { "last_tx", 6 },
    { NULL, -1 },
    { "i_am_initiator", 17 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "lease_satoshi", 15 },
    { NULL, -1 },
    { "funding_psbt", 5 },
    { "funding_tx_remote_sigs_received", 8 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "funding_feerate", 2 },
    { "our_funding_satoshi", 4 },
    { "last_sig", 7 },
    { "lease_chan_max_ppt", 12 },
    { "lease_fee", 14 },
    { NULL, -1 },
    { "funding_tx_outnum", 1 },
    { "splice_amnt", 16 },
    { NULL, -1 },
    { NULL, -1 },
    { "funding_satoshi", 3 },
    { NULL, -1 },
};

static const struct sqlname_map col_table335[] = {
    { "max_accepted_htlcs", 5 },
    { "dust_limit_satoshis", 0 },
    { NULL, -1 },
    { "to_self_delay", 4 },
    { "htlc_minimum_msat", 3 },
    { "max_dust_htlc_exposure_msat", 6 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "max_htlc_value_in_flight_msat", 1 },
    { NULL, -1 },
    { "channel_reserve_satoshis", 2 },
};

static const struct sqlname_map col_table336[] = {
    { NULL, -1 },
    { NULL, -1 },
    { "timestamp", 0 },
    { NULL, -1 },
    { "old_state", 1 },
    { "new_state", 2 },
    { "message", 4 },
    { "cause", 3 },
    { NULL, -1 },
};

static const struct sqlname_map col_table337[] = {
    { NULL, -1 },
    { "state_change_reason", 20 },
    { "lease_commit_sig", 21 },
    { "msatoshi_to_us_max", 17 },
    { NULL, -1 },
    { "next_index_local", 8 },
    { NULL, -1 },
    { "last_tx", 18 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "full_channel_id", 1 },
    { "p.node_id", 0 },
    { "alias_local", 3 },
    { "closer", 6 },
    { "channel_flags", 7 },
    { "next_index_remote", 9 },
    { "msatoshi_local", 15 },
    { "last_stable_connection", 22 },
    { NULL, -1 },
    { NULL, -1 },
    { "funding_tx_outnum", 12 },
    { NULL, -1 },
    { "channel_type", 19 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "next_htlc_id", 10 },
    { "push_msatoshi", 14 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "funding_satoshi", 13 },
    { NULL, -1 },
    { "funder", 5 },
    { "scid", 2 },
    { NULL, -1 },
    { "funding_tx_id", 11 },
    { "msatoshi_to_us_min", 16 },
    { "alias_remote", 4 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table338[] = {
    { "id", 0 },
};

static const struct sqlname_map col_table339[] = {
    { NULL, -1 },
    { "max_possible_feerate", 39 },
    { "require_confirm_inputs_remote", 10 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "remote_htlc_maximum_msat", 73 },
    { "funding_satoshi", 17 },
    { "out_msatoshi_fulfilled", 82 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "feerate_base", 44 },
    { "closer", 51 },
    { "funding_pubkey_local", 57 },
    { "lease_commit_sig", 61 },
    { "next_index_local", 12 },
    { "out_msatoshi_offered", 81 },
    { NULL, -1 },
    { "remote_htlc_minimum_msat", 72 },
    { "shachain_remote_id", 29 },
    { "in_payments_offered", 75 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "htlc_maximum_msat", 65 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "in_msatoshi_offered", 77 },
    { "payment_basepoint_local", 54 },
    { NULL, -1 },
    { NULL, -1 },
    { "shutdown_scriptpubkey_remote", 30 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "ignore_fee_limits", 68 },
    { NULL, -1 },
    { "alias_local", 66 },
    { "next_index_remote", 13 },
    { "last_stable_connection", 74 },
    { "last_sent_commit_state", 32 },
    { "close_attempt_height", 83 },
    { NULL, -1 },
    { NULL, -1 },
    { "last_tx", 34 },
    { "lease_chan_max_msat", 62 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "shutdown_keyidx_local", 31 },
    { "in_msatoshi_fulfilled", 78 },
    { "channel_config_local", 4 },
    { NULL, -1 },
    { NULL, -1 },
    { "channel_config_remote", 5 },
    { "funder", 7 },
    { "funding_tx_outnum", 16 },
    { "msatoshi_local", 21 },
    { "remote_upfront_shutdown_script", 46 },
    { "state_change_reason", 52 },
    { "our_funding_satoshi", 18 },
    { "msatoshi_to_us_min", 40 },
    { "feerate_ppm", 45 },
    { "require_confirm_inputs_local", 9 },
    { "first_blocknum", 37 },
    { "lease_chan_max_ppt", 63 },
    { "htlc_minimum_msat", 64 },
    { "out_payments_fulfilled", 80 },
    { NULL, -1 },
    { "push_msatoshi", 20 },
    { "last_was_revoke", 36 },
    { NULL, -1 },
    { "local_static_remotekey_start", 47 },
    { "shutdown_wrong_outnum", 59 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "alias_remote", 67 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "scid", 2 },
    { "funding_locked_remote", 19 },
    { "delayed_payment_basepoint_remote", 26 },
    { "shutdown_wrong_txid", 58 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "payment_basepoint_remote", 24 },
    { "revocation_basepoint_remote", 23 },
    { "last_sent_commit_id", 33 },
    { NULL, -1 },
    { NULL, -1 },
    { "channel_type", 49 },
    { "revocation_basepoint_local", 53 },
    { "delayed_payment_basepoint_local", 56 },
    { NULL, -1 },
    { "fundingkey_remote", 22 },
    { "htlc_basepoint_local", 55 },
    { NULL, -1 },
    { "minimum_depth", 11 },
    { "shutdown_scriptpubkey_local", 50 },
    { "in_payments_fulfilled", 76 },
    { NULL, -1 },
    { "remote_feerate_ppm", 70 },
    { "last_sig", 35 },
    { "future_per_commitment_point", 42 },
    { NULL, -1 },
    { NULL, -1 },
    { "remote_static_remotekey_start", 48 },
    { NULL, -1 },
    { NULL, -1 },
    { "channel_flags", 8 },
    { NULL, -1 },
    { "id", 0 },
    { "remote_feerate_base", 69 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "state", 6 },
    { NULL, -1 },
    { NULL, -1 },
    { "lease_expiry", 60 },
    { NULL, -1 },
    { "msatoshi_to_us_max", 41 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "peer_id", 1 },
    { "htlc_basepoint_remote", 25 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "remote_cltv_expiry_delta", 71 },
    { NULL, -1 },
    { "old_per_commit_remote", 28 },
    { NULL, -1 },
    { NULL, -1 },
    { "min_possible_feerate", 38 },
    { "full_channel_id", 3 },
    { "last_sent_commit", 43 },
    { "out_payments_offered", 79 },
    { NULL, -1 },
    { NULL, -1 },
    { "per_commit_remote", 27 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "next_htlc_id", 14 },
    { "funding_tx_id", 15 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table344[] = {
    { "MAX(height)", 0 },
};

static const struct sqlname_map col_table358[] = {
    { "id", 0 },
};

static const struct sqlname_map col_table362[] = {
    { "*", 0 },
};

static const struct sqlname_map col_table371[] = {
    { "*", 0 },
};

static const struct sqlname_map col_table378[] = {
    { "id", 0 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "payment_hash", 5 },
    { "channel_htlc_id", 1 },
    { "msatoshi", 2 },
    { "hstate", 4 },
    { "received_time", 11 },
    { "malformed_onion", 9 },
    { "shared_secret", 10 },
    { "failuremsg", 8 },
    { "cltv_expiry", 3 },
    { "fail_immediate", 13 },
    { "we_filled", 12 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "payment_key", 6 },
    { "routing_onion", 7 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table379[] = {
    { "id", 0 },
    { "groupid", 12 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "origin_htlc", 9 },
    { "payment_hash", 5 },
    { "channel_htlc_id", 1 },
    { "msatoshi", 2 },
    { "hstate", 4 },
    { "fees_msat", 13 },
    { NULL, -1 },
    { NULL, -1 },
    { "failuremsg", 8 },
    { "cltv_expiry", 3 },
    { "partid", 10 },
    { "localfailmsg", 11 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "payment_key", 6 },
    { "routing_onion", 7 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table380[] = {
    { "channel_htlc_id", 3 },
    { NULL, -1 },
    { NULL, -1 },
    { "channel_id", 0 },
    { NULL, -1 },
    { NULL, -1 },
    { "direction", 1 },
    { "cltv_expiry", 2 },
    { "payment_hash", 4 },
};

static const struct sqlname_map col_table382[] = {
    { "MAX(groupid)", 0 },
};

static const struct sqlname_map col_table385[] = {
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "id", 0 },
    { "timestamp", 6 },
    { "path_secrets", 8 },
    { NULL, -1 },
    { "local_invreq_id", 18 },
    { "msatoshi", 4 },
    { NULL, -1 },
    { "destination", 3 },
    { "paydescription", 14 },
    { "groupid", 19 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_channels", 10 },
    { "total_msat", 16 },
    { "completed_at", 20 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_nodes", 9 },
    { "payment_preimage", 7 },
    { "failonionreply", 15 },
    { NULL, -1 },
    { "msatoshi_sent", 11 },
    { NULL, -1 },
    { "bolt11", 13 },
    { "payment_hash", 5 },
    { "updated_index", 1 },
    { "status", 2 },
    { "partid", 17 },
    { NULL, -1 },
    { NULL, -1 },
    { "description", 12 },
};

static const struct sqlname_map col_table389[] = {
    { NULL, -1 },
    { "failonionreply", 0 },
    { "failnode", 4 },
    { "failupdate", 6 },
    { NULL, -1 },
    { "failscid", 5 },
    { "faildirection", 8 },
    { NULL, -1 },
    { NULL, -1 },
    { "failindex", 2 },
    { "faildetail", 7 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "failcode", 3 },
    { NULL, -1 },
    { "faildestperm", 1 },
};

static const struct sqlname_map col_table391[] = {
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "id", 0 },
    { "timestamp", 6 },
    { "path_secrets", 8 },
    { NULL, -1 },
    { "local_invreq_id", 18 },
    { "msatoshi", 4 },
    { NULL, -1 },
    { "destination", 3 },
    { "paydescription", 14 },
    { "groupid", 19 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_channels", 10 },
    { "total_msat", 16 },
    { "completed_at", 20 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_nodes", 9 },
    { "payment_preimage", 7 },
    { "failonionreply", 15 },
    { NULL, -1 },
    { "msatoshi_sent", 11 },
    { NULL, -1 },
    { "bolt11", 13 },
    { "payment_hash", 5 },
    { "updated_index", 1 },
    { "status", 2 },
    { "partid", 17 },
    { NULL, -1 },
    { NULL, -1 },
    { "description", 12 },
};

static const struct sqlname_map col_table392[] = {
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "id", 0 },
    { "timestamp", 6 },
    { "path_secrets", 8 },
    { NULL, -1 },
    { "local_invreq_id", 18 },
    { "msatoshi", 4 },
    { NULL, -1 },
    { "destination", 3 },
    { "paydescription", 14 },
    { "groupid", 19 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_channels", 10 },
    { "total_msat", 16 },
    { "completed_at", 20 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_nodes", 9 },
    { "payment_preimage", 7 },
    { "failonionreply", 15 },
    { NULL, -1 },
    { "msatoshi_sent", 11 },
    { NULL, -1 },
    { "bolt11", 13 },
    { "payment_hash", 5 },
    { "updated_index", 1 },
    { "status", 2 },
    { "partid", 17 },
    { NULL, -1 },
    { NULL, -1 },
    { "description", 12 },
};

static const struct sqlname_map col_table393[] = {
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "id", 0 },
    { "timestamp", 6 },
    { "path_secrets", 8 },
    { NULL, -1 },
    { "local_invreq_id", 18 },
    { "msatoshi", 4 },
    { NULL, -1 },
    { "destination", 3 },
    { "paydescription", 14 },
    { "groupid", 19 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_channels", 10 },
    { "total_msat", 16 },
    { "completed_at", 20 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_nodes", 9 },
    { "payment_preimage", 7 },
    { "failonionreply", 15 },
    { NULL, -1 },
    { "msatoshi_sent", 11 },
    { NULL, -1 },
    { "bolt11", 13 },
    { "payment_hash", 5 },
    { "updated_index", 1 },
    { "status", 2 },
    { "partid", 17 },
    { NULL, -1 },
    { NULL, -1 },
    { "description", 12 },
};

static const struct sqlname_map col_table394[] = {
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "id", 0 },
    { "timestamp", 6 },
    { "path_secrets", 8 },
    { NULL, -1 },
    { "local_invreq_id", 18 },
    { "msatoshi", 4 },
    { NULL, -1 },
    { "destination", 3 },
    { "paydescription", 14 },
    { "groupid", 19 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_channels", 10 },
    { "total_msat", 16 },
    { "completed_at", 20 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_nodes", 9 },
    { "payment_preimage", 7 },
    { "failonionreply", 15 },
    { NULL, -1 },
    { "msatoshi_sent", 11 },
    { NULL, -1 },
    { "bolt11", 13 },
    { "payment_hash", 5 },
    { "updated_index", 1 },
    { "status", 2 },
    { "partid", 17 },
    { NULL, -1 },
    { NULL, -1 },
    { "description", 12 },
};

static const struct sqlname_map col_table395[] = {
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "id", 0 },
    { "timestamp", 6 },
    { "path_secrets", 8 },
    { NULL, -1 },
    { "local_invreq_id", 18 },
    { "msatoshi", 4 },
    { NULL, -1 },
    { "destination", 3 },
    { "paydescription", 14 },
    { "groupid", 19 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_channels", 10 },
    { "total_msat", 16 },
    { "completed_at", 20 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_nodes", 9 },
    { "payment_preimage", 7 },
    { "failonionreply", 15 },
    { NULL, -1 },
    { "msatoshi_sent", 11 },
    { NULL, -1 },
    { "bolt11", 13 },
    { "payment_hash", 5 },
    { "updated_index", 1 },
    { "status", 2 },
    { "partid", 17 },
    { NULL, -1 },
    { NULL, -1 },
    { "description", 12 },
};

static const struct sqlname_map col_table396[] = {
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "id", 0 },
    { "timestamp", 6 },
    { "path_secrets", 8 },
    { NULL, -1 },
    { "local_invreq_id", 18 },
    { "msatoshi", 4 },
    { NULL, -1 },
    { "destination", 3 },
    { "paydescription", 14 },
    { "groupid", 19 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_channels", 10 },
    { "total_msat", 16 },
    { "completed_at", 20 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_nodes", 9 },
    { "payment_preimage", 7 },
    { "failonionreply", 15 },
    { NULL, -1 },
    { "msatoshi_sent", 11 },
    { NULL, -1 },
    { "bolt11", 13 },
    { "payment_hash", 5 },
    { "updated_index", 1 },
    { "status", 2 },
    { "partid", 17 },
    { NULL, -1 },
    { NULL, -1 },
    { "description", 12 },
};

static const struct sqlname_map col_table397[] = {
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "id", 0 },
    { "timestamp", 6 },
    { "path_secrets", 8 },
    { NULL, -1 },
    { "local_invreq_id", 18 },
    { "msatoshi", 4 },
    { NULL, -1 },
    { "destination", 3 },
    { "paydescription", 14 },
    { "groupid", 19 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_channels", 10 },
    { "total_msat", 16 },
    { "completed_at", 20 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "route_nodes", 9 },
    { "payment_preimage", 7 },
    { "failonionreply", 15 },
    { NULL, -1 },
    { "msatoshi_sent", 11 },
    { NULL, -1 },
    { "bolt11", 13 },
    { "payment_hash", 5 },
    { "updated_index", 1 },
    { "status", 2 },
    { "partid", 17 },
    { NULL, -1 },
    { NULL, -1 },
    { "description", 12 },
};

static const struct sqlname_map col_table401[] = {
    { "blobval", 0 },
};

static const struct sqlname_map col_table403[] = {
    { "blobval", 0 },
};

static const struct sqlname_map col_table405[] = {
    { "outnum", 1 },
    { "txid", 0 },
    { NULL, -1 },
};

static const struct sqlname_map col_table409[] = {
    { "*", 0 },
};

static const struct sqlname_map col_table414[] = {
    { "height", 0 },
};

static const struct sqlname_map col_table415[] = {
    { "spendheight", 1 },
    { "satoshis", 3 },
    { "scriptpubkey", 2 },
    { NULL, -1 },
    { "txid", 0 },
    { NULL, -1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table416[] = {
    { "outnum", 2 },
    { NULL, -1 },
    { NULL, -1 },
    { "blockheight", 0 },
    { "txindex", 1 },
};

static const struct sqlname_map col_table417[] = {
    { "spendheight", 0 },
};

static const struct sqlname_map col_table418[] = {
    { "outnum", 2 },
    { NULL, -1 },
    { NULL, -1 },
    { "blockheight", 0 },
    { "txindex", 1 },
};

static const struct sqlname_map col_table419[] = {
    { "blockheight", 0 },
};

static const struct sqlname_map col_table423[] = {
    { "rawtx", 0 },
};

static const struct sqlname_map col_table424[] = {
    { "blockheight", 0 },
    { "txindex", 1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table425[] = {
    { "id", 0 },
};

static const struct sqlname_map col_table427[] = {
    { "t.rawtx", 1 },
    { NULL, -1 },
    { "t.blockheight", 0 },
};

static const struct sqlname_map col_table430[] = {
    { "CAST(COALESCE(SUM(in_msatoshi - out_msatoshi), 0) AS BIGINT)", 0 },
};

static const struct sqlname_map col_table431[] = {
    { "state", 0 },
    { "rowid", 11 },
    { "resolved_time", 8 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "in_htlc_id", 5 },
    { NULL, -1 },
    { NULL, -1 },
    { "failcode", 9 },
    { NULL, -1 },
    { "out_msatoshi", 2 },
    { NULL, -1 },
    { "out_channel_scid", 4 },
    { "updated_index", 12 },
    { NULL, -1 },
    { "in_msatoshi", 1 },
    { "out_htlc_id", 6 },
    { "forward_style", 10 },
    { NULL, -1 },
    { "in_channel_scid", 3 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "received_time", 7 },
};

static const struct sqlname_map col_table432[] = {
    { "state", 0 },
    { "rowid", 11 },
    { "resolved_time", 8 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "in_htlc_id", 5 },
    { NULL, -1 },
    { NULL, -1 },
    { "failcode", 9 },
    { NULL, -1 },
    { "out_msatoshi", 2 },
    { NULL, -1 },
    { "out_channel_scid", 4 },
    { "updated_index", 12 },
    { NULL, -1 },
    { "in_msatoshi", 1 },
    { "out_htlc_id", 6 },
    { "forward_style", 10 },
    { NULL, -1 },
    { "in_channel_scid", 3 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "received_time", 7 },
};

static const struct sqlname_map col_table433[] = {
    { "state", 0 },
    { "rowid", 11 },
    { "resolved_time", 8 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "in_htlc_id", 5 },
    { NULL, -1 },
    { NULL, -1 },
    { "failcode", 9 },
    { NULL, -1 },
    { "out_msatoshi", 2 },
    { NULL, -1 },
    { "out_channel_scid", 4 },
    { "updated_index", 12 },
    { NULL, -1 },
    { "in_msatoshi", 1 },
    { "out_htlc_id", 6 },
    { "forward_style", 10 },
    { NULL, -1 },
    { "in_channel_scid", 3 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "received_time", 7 },
};

static const struct sqlname_map col_table434[] = {
    { "CAST(COALESCE(SUM(in_msatoshi - out_msatoshi), 0) AS BIGINT)", 0 },
};

static const struct sqlname_map col_table435[] = {
    { "CAST(COALESCE(SUM(in_msatoshi - out_msatoshi), 0) AS BIGINT)", 0 },
};

static const struct sqlname_map col_table438[] = {
    { "t.rawtx", 1 },
    { NULL, -1 },
    { "t.txindex", 3 },
    { NULL, -1 },
    { "t.blockheight", 2 },
    { NULL, -1 },
    { "t.id", 0 },
};

static const struct sqlname_map col_table440[] = {
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "commitnum", 0 },
    { "txid", 1 },
    { "amount", 3 },
    { "outnum", 2 },
};

static const struct sqlname_map col_table442[] = {
    { "1", 0 },
};

static const struct sqlname_map col_table444[] = {
    { NULL, -1 },
    { "bolt12", 0 },
    { "status", 2 },
    { NULL, -1 },
    { "label", 1 },
};

static const struct sqlname_map col_table445[] = {
    { "offer_id", 0 },
};

static const struct sqlname_map col_table448[] = {
    { "status", 0 },
};

static const struct sqlname_map col_table449[] = {
    { "1", 0 },
};

static const struct sqlname_map col_table451[] = {
    { NULL, -1 },
    { "bolt12", 0 },
    { "status", 2 },
    { NULL, -1 },
    { "label", 1 },
};

static const struct sqlname_map col_table452[] = {
    { "invreq_id", 0 },
};

static const struct sqlname_map col_table454[] = {
    { "status", 0 },
};

static const struct sqlname_map col_table458[] = {
    { "data", 0 },
    { "generation", 1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table459[] = {
    { "key", 0 },
    { "data", 1 },
    { NULL, -1 },
    { "generation", 2 },
    { NULL, -1 },
};

static const struct sqlname_map col_table460[] = {
    { "key", 0 },
    { "data", 1 },
    { NULL, -1 },
    { "generation", 2 },
    { NULL, -1 },
};

static const struct sqlname_map col_table461[] = {
    { NULL, -1 },
    { NULL, -1 },
    { "h.channel_htlc_id", 0 },
    { "h.direction", 2 },
    { "h.hstate", 5 },
    { "h.msatoshi", 3 },
    { "h.payment_hash", 4 },
    { NULL, -1 },
    { NULL, -1 },
    { "h.cltv_expiry", 1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table462[] = {
    { NULL, -1 },
    { "h.payment_hash", 6 },
    { NULL, -1 },
    { NULL, -1 },
    { NULL, -1 },
    { "channels.alias_local", 1 },
    { NULL, -1 },
    { "h.msatoshi", 5 },
    { NULL, -1 },
    { "h.cltv_expiry", 3 },
    { "h.channel_htlc_id", 2 },
    { "h.hstate", 7 },
    { "channels.scid", 0 },
    { NULL, -1 },
    { "h.direction", 4 },
};

static const struct sqlname_map col_table463[] = {
    { "(COALESCE(MAX(id), -1) + 1)", 0 },
};

static const struct sqlname_map col_table464[] = {
    { "end_index", 1 },
    { NULL, -1 },
    { "start_index", 0 },
};

static const struct sqlname_map col_table465[] = {
    { NULL, -1 },
    { "last_used_nsec", 1 },
    { "rune", 0 },
};

static const struct sqlname_map col_table466[] = {
    { "rune", 0 },
};

static const struct sqlname_map col_table467[] = {
    { NULL, -1 },
    { "last_used_nsec", 1 },
    { "rune", 0 },
};

static const struct sqlname_map col_table475[] = {
    { NULL, -1 },
    { "commitment_anchor_outnum", 1 },
    { "commitment_fee", 2 },
    { NULL, -1 },
    { NULL, -1 },
    { "commitment_weight", 3 },
    { "commitment_txid", 0 },
};

static const struct sqlname_map col_table476[] = {
    { NULL, -1 },
    { "addrtype", 1 },
    { "keyidx", 0 },
};

static const struct sqlname_map col_table477[] = {
    { "name", 0 },
};

static const struct sqlname_map col_table484[] = {
    { "id", 0 },
    { NULL, -1 },
    { "field1a", 1 },
};

static const struct sqlname_map col_table485[] = {
    { "id", 0 },
    { "field2", 1 },
    { NULL, -1 },
};

static const struct sqlname_map col_table486[] = {
    { "field1", 0 },
};

static const struct sqlname_map col_table487[] = {
    { "field1", 0 },
};

static const struct sqlname_map col_table488[] = {
    { "COUNT(1)", 0 },
};


const struct db_query db_postgres_queries[] = {

    {
         .name = "SELECT * FROM channels WHERE id = ?",
         .query = "SELECT * FROM channels WHERE id = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table362,
         .num_colnames = ARRAY_SIZE(col_table362),
    },
    {
    },
    {
         .name = "UPDATE channels   SET  in_payments_offered = 0,  in_payments_fulfilled = 0     ,  in_msatoshi_offered = 0,  in_msatoshi_fulfilled = 0     , out_payments_offered = 0, out_payments_fulfilled = 0     , out_msatoshi_offered = 0, out_msatoshi_fulfilled = 0     ;",
         .query = "UPDATE channels   SET  in_payments_offered = 0,  in_payments_fulfilled = 0     ,  in_msatoshi_offered = 0,  in_msatoshi_fulfilled = 0     , out_payments_offered = 0, out_payments_fulfilled = 0     , out_msatoshi_offered = 0, out_msatoshi_fulfilled = 0     ;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD remote_cltv_expiry_delta INTEGER DEFAULT NULL;",
         .query = "ALTER TABLE channels ADD remote_cltv_expiry_delta INTEGER DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT blockheight FROM transactions WHERE id=?",
         .query = "SELECT blockheight FROM transactions WHERE id=$1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table419,
         .num_colnames = ARRAY_SIZE(col_table419),
    },
    {
         .name = "INSERT INTO channels (id) VALUES (1);",
         .query = "INSERT INTO channels (id) VALUES (1);",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD feerate_base INTEGER;",
         .query = "ALTER TABLE channels ADD feerate_base INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT remote_ann_node_sig, remote_ann_bitcoin_sig FROM channels WHERE id = ?",
         .query = "SELECT remote_ann_node_sig, remote_ann_bitcoin_sig FROM channels WHERE id = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table326,
         .num_colnames = ARRAY_SIZE(col_table326),
    },
    {
    },
    {
    },
    {
         .name = "SELECT intval FROM vars WHERE name = 'data_version'",
         .query = "SELECT intval FROM vars WHERE name = 'data_version'",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table1,
         .num_colnames = ARRAY_SIZE(col_table1),
    },
    {
         .name = "/*PSQL*/INSERT INTO vars (name, intval) VALUES ('payment_id_reset', setval(pg_get_serial_sequence('payments', 'id'), COALESCE((SELECT MAX(id)+1 FROM payments), 1)))",
         .query = "/*PSQL*/INSERT INTO vars (name, intval) VALUES ('payment_id_reset', setval(pg_get_serial_sequence('payments', 'id'), COALESCE((SELECT MAX(id)+1 FROM payments), 1)))",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD paid_txid BLOB DEFAULT NULL",
         .query = "ALTER TABLE invoices ADD paid_txid BYTEA DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT height FROM blocks WHERE height = ?",
         .query = "SELECT height FROM blocks WHERE height = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table414,
         .num_colnames = ARRAY_SIZE(col_table414),
    },
    {
    },
    {
         .name = "INSERT INTO channels (  peer_id, first_blocknum, id, revocation_basepoint_local, payment_basepoint_local, htlc_basepoint_local, delayed_payment_basepoint_local, funding_pubkey_local, require_confirm_inputs_remote, require_confirm_inputs_local) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO channels (  peer_id, first_blocknum, id, revocation_basepoint_local, payment_basepoint_local, htlc_basepoint_local, delayed_payment_basepoint_local, funding_pubkey_local, require_confirm_inputs_remote, require_confirm_inputs_local) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10);",
         .placeholders = 10,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET payment_preimage=? WHERE payment_hash=? AND partid=? AND groupid=?",
         .query = "UPDATE payments SET payment_preimage=$1 WHERE payment_hash=$2 AND partid=$3 AND groupid=$4",
         .placeholders = 4,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "DELETE FROM htlc_sigs WHERE channelid=? AND (inflight_tx_id is NULL OR ( inflight_tx_id!=? AND  inflight_tx_outnum!=?))",
         .query = "DELETE FROM htlc_sigs WHERE channelid=$1 AND (inflight_tx_id is NULL OR ( inflight_tx_id!=$2 AND  inflight_tx_outnum!=$3))",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD COLUMN local_invreq_id BLOB DEFAULT NULL REFERENCES invoicerequests(invreq_id);",
         .query = "ALTER TABLE payments ADD COLUMN local_invreq_id BYTEA DEFAULT NULL REFERENCES invoicerequests(invreq_id);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT txid, spendheight, scriptpubkey, satoshis FROM utxoset WHERE blockheight = ? AND txindex = ? AND outnum = ? AND spendheight IS NULL",
         .query = "SELECT txid, spendheight, scriptpubkey, satoshis FROM utxoset WHERE blockheight = $1 AND txindex = $2 AND outnum = $3 AND spendheight IS NULL",
         .placeholders = 3,
         .readonly = true,
         .colnames = col_table415,
         .num_colnames = ARRAY_SIZE(col_table415),
    },
    {
    },
    {
         .name = "CREATE TABLE version (version INTEGER)",
         .query = "CREATE TABLE version (version INTEGER)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET our_funding_satoshi = funding_satoshi WHERE funder = 0;",
         .query = "UPDATE channels SET our_funding_satoshi = funding_satoshi WHERE funder = 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "INSERT INTO outputs (  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, is_in_coinbase) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO outputs (  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, is_in_coinbase) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14);",
         .placeholders = 14,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD revocation_basepoint_local BLOB",
         .query = "ALTER TABLE channels ADD revocation_basepoint_local BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "INSERT INTO channel_htlcs ( channel_id, channel_htlc_id,  direction, msatoshi, cltv_expiry, payment_hash,  payment_key, hstate, shared_secret, routing_onion, received_time, min_commit_num,  fail_immediate) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO channel_htlcs ( channel_id, channel_htlc_id,  direction, msatoshi, cltv_expiry, payment_hash,  payment_key, hstate, shared_secret, routing_onion, received_time, min_commit_num,  fail_immediate) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13);",
         .placeholders = 13,
         .readonly = false,
    },
    {
         .name = "SELECT id, funding_tx_id, funding_tx_outnum FROM channels;",
         .query = "SELECT id, funding_tx_id, funding_tx_outnum FROM channels;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table251,
         .num_colnames = ARRAY_SIZE(col_table251),
    },
    {
         .name = "UPDATE invoices   SET paid_timestamp = CURRENT_TIMESTAMP() WHERE state = 1;",
         .query = "UPDATE invoices   SET paid_timestamp = EXTRACT(epoch FROM now()) WHERE state = 1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE outputs SET status=? WHERE status=? AND prev_out_tx=? AND prev_out_index=?",
         .query = "UPDATE outputs SET status=$1 WHERE status=$2 AND prev_out_tx=$3 AND prev_out_index=$4",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "INSERT INTO vars (name, intval) VALUES ('data_version', 0);",
         .query = "INSERT INTO vars (name, intval) VALUES ('data_version', 0);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD funding_pubkey_local BLOB",
         .query = "ALTER TABLE channels ADD funding_pubkey_local BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT hstate, feerate_per_kw FROM channel_feerates WHERE channel_id = ?",
         .query = "SELECT hstate, feerate_per_kw FROM channel_feerates WHERE channel_id = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table328,
         .num_colnames = ARRAY_SIZE(col_table328),
    },
    {
         .name = "ALTER TABLE invoices ADD COLUMN features BLOB DEFAULT '';",
         .query = "ALTER TABLE invoices ADD COLUMN features BYTEA DEFAULT '';",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT channels.scid, channels.alias_local, h.channel_htlc_id, h.cltv_expiry, h.direction, h.msatoshi, h.payment_hash, h.hstate FROM channel_htlcs h JOIN channels ON channels.id = h.channel_id ORDER BY h.id ASC",
         .query = "SELECT channels.scid, channels.alias_local, h.channel_htlc_id, h.cltv_expiry, h.direction, h.msatoshi, h.payment_hash, h.hstate FROM channel_htlcs h JOIN channels ON channels.id = h.channel_id ORDER BY h.id ASC",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table462,
         .num_colnames = ARRAY_SIZE(col_table462),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT keyidx, addrtype FROM addresses WHERE keyidx >= ? ORDER BY keyidx LIMIT ?;",
         .query = "SELECT keyidx, addrtype FROM addresses WHERE keyidx >= $1 ORDER BY keyidx LIMIT $2;",
         .placeholders = 2,
         .readonly = true,
         .colnames = col_table476,
         .num_colnames = ARRAY_SIZE(col_table476),
    },
    {
         .name = "INSERT INTO payments (id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11)SELECT id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11 FROM temp_payments;",
         .query = "INSERT INTO payments (id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11)SELECT id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11 FROM temp_payments;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "CREATE TABLE transaction_annotations (  txid BLOB, idx INTEGER, location INTEGER, type INTEGER, channel BIGINT REFERENCES channels(id), UNIQUE(txid, idx));",
         .query = "CREATE TABLE transaction_annotations (  txid BYTEA, idx INTEGER, location INTEGER, type INTEGER, channel BIGINT REFERENCES channels(id), UNIQUE(txid, idx));",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT txid, outnum FROM utxoset WHERE spendheight is NULL",
         .query = "SELECT txid, outnum FROM utxoset WHERE spendheight is NULL",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table303,
         .num_colnames = ARRAY_SIZE(col_table303),
    },
    {
         .name = "SELECT 1  FROM invoicerequests WHERE invreq_id = ?;",
         .query = "SELECT 1  FROM invoicerequests WHERE invreq_id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table449,
         .num_colnames = ARRAY_SIZE(col_table449),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO db_upgrades VALUES (?, ?);",
         .query = "INSERT INTO db_upgrades VALUES ($1, $2);",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "CREATE TABLE invoicerequests (  invreq_id BLOB, bolt12 TEXT, label TEXT, status INTEGER, PRIMARY KEY (invreq_id));",
         .query = "CREATE TABLE invoicerequests (  invreq_id BYTEA, bolt12 TEXT, label TEXT, status INTEGER, PRIMARY KEY (invreq_id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD msatoshi_to_us_max BIGINT;",
         .query = "ALTER TABLE channels ADD msatoshi_to_us_max BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "SELECT id  FROM invoices WHERE payment_hash = ?   AND state = ?;",
         .query = "SELECT id  FROM invoices WHERE payment_hash = $1   AND state = $2;",
         .placeholders = 2,
         .readonly = true,
         .colnames = col_table293,
         .num_colnames = ARRAY_SIZE(col_table293),
    },
    {
         .name = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE  description = ?;",
         .query = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE  description = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table394,
         .num_colnames = ARRAY_SIZE(col_table394),
    },
    {
    },
    {
         .name = "INSERT INTO vars (name, blobval) VALUES ('node_id', ?);",
         .query = "INSERT INTO vars (name, blobval) VALUES ('node_id', $1);",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT id, node_id, address, feature_bits, last_known_address FROM peers WHERE id=?;",
         .query = "SELECT id, node_id, address, feature_bits, last_known_address FROM peers WHERE id=$1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table324,
         .num_colnames = ARRAY_SIZE(col_table324),
    },
    {
    },
    {
         .name = "UPDATE version SET version=?;",
         .query = "UPDATE version SET version=$1;",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "UPDATE invoices SET msatoshi_received=0 WHERE state=1;",
         .query = "UPDATE invoices SET msatoshi_received=0 WHERE state=1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD lease_fee BIGINT DEFAULT 0",
         .query = "ALTER TABLE channel_funding_inflights ADD lease_fee BIGINT DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD require_confirm_inputs_local INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD require_confirm_inputs_local INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO invoices            ( id, payment_hash, payment_key, state            , msatoshi, label, expiry_time            , pay_index, msatoshi_received            , paid_timestamp, bolt11, description, features, local_offer_id)     VALUES ( ?, ?, ?, ?            , ?, ?, ?            , NULL, NULL            , NULL, ?, ?, ?, ?);",
         .query = "INSERT INTO invoices            ( id, payment_hash, payment_key, state            , msatoshi, label, expiry_time            , pay_index, msatoshi_received            , paid_timestamp, bolt11, description, features, local_offer_id)     VALUES ( $1, $2, $3, $4            , $5, $6, $7            , NULL, NULL            , NULL, $8, $9, $10, $11);",
         .placeholders = 11,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE peers ADD last_known_address BLOB DEFAULT NULL;",
         .query = "ALTER TABLE peers ADD last_known_address BYTEA DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "UPDATE outputs SET status=? WHERE prev_out_tx=? AND prev_out_index=?",
         .query = "UPDATE outputs SET status=$1 WHERE prev_out_tx=$2 AND prev_out_index=$3",
         .placeholders = 3,
         .readonly = false,
    },
    {
    },
    {
         .name = "UPDATE payments SET completed_at = timestamp WHERE status != 0;",
         .query = "UPDATE payments SET completed_at = timestamp WHERE status != 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO htlc_sigs (channelid, signature) VALUES (?, ?)",
         .query = "INSERT INTO htlc_sigs (channelid, signature) VALUES ($1, $2)",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channel_feerates (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  hstate INTEGER,  feerate_per_kw INTEGER,  UNIQUE (channel_id, hstate));",
         .query = "CREATE TABLE channel_feerates (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  hstate INTEGER,  feerate_per_kw INTEGER,  UNIQUE (channel_id, hstate));",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE channels SET remote_ann_node_sig=?, remote_ann_bitcoin_sig=? WHERE id = ?",
         .query = "UPDATE channels SET remote_ann_node_sig=$1, remote_ann_bitcoin_sig=$2 WHERE id = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "CREATE TABLE payments ( id BIGSERIAL, timestamp INTEGER, status INTEGER, payment_hash BLOB, destination BLOB, msatoshi BIGINT, payment_preimage BLOB, path_secrets BLOB, route_nodes BLOB, route_channels BLOB, failonionreply BLOB, faildestperm INTEGER, failindex INTEGER, failcode INTEGER, failnode BLOB, failchannel TEXT, failupdate BLOB, msatoshi_sent BIGINT, faildetail TEXT, description TEXT, faildirection INTEGER, bolt11 TEXT, total_msat BIGINT, partid BIGINT, PRIMARY KEY (id), UNIQUE (payment_hash, partid))",
         .query = "CREATE TABLE payments ( id BIGSERIAL, timestamp INTEGER, status INTEGER, payment_hash BYTEA, destination BYTEA, msatoshi BIGINT, payment_preimage BYTEA, path_secrets BYTEA, route_nodes BYTEA, route_channels BYTEA, failonionreply BYTEA, faildestperm INTEGER, failindex INTEGER, failcode INTEGER, failnode BYTEA, failchannel TEXT, failupdate BYTEA, msatoshi_sent BIGINT, faildetail TEXT, description TEXT, faildirection INTEGER, bolt11 TEXT, total_msat BIGINT, partid BIGINT, PRIMARY KEY (id), UNIQUE (payment_hash, partid))",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD require_confirm_inputs_remote INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD require_confirm_inputs_remote INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT  id, channel_htlc_id, msatoshi, cltv_expiry, hstate, payment_hash, payment_key, routing_onion, failuremsg, origin_htlc, partid, localfailmsg, groupid, fees_msat FROM channel_htlcs WHERE direction = ? AND channel_id = ? AND hstate NOT IN (?, ?)",
         .query = "SELECT  id, channel_htlc_id, msatoshi, cltv_expiry, hstate, payment_hash, payment_key, routing_onion, failuremsg, origin_htlc, partid, localfailmsg, groupid, fees_msat FROM channel_htlcs WHERE direction = $1 AND channel_id = $2 AND hstate NOT IN ($3, $4)",
         .placeholders = 4,
         .readonly = true,
         .colnames = col_table379,
         .num_colnames = ARRAY_SIZE(col_table379),
    },
    {
         .name = "SELECT rune FROM runes",
         .query = "SELECT rune FROM runes",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table466,
         .num_colnames = ARRAY_SIZE(col_table466),
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD feerate_ppm INTEGER;",
         .query = "ALTER TABLE channels ADD feerate_ppm INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "CREATE INDEX channel_htlcs_speedup_unresolved_idx    ON channel_htlcs(channel_id, direction) WHERE hstate NOT IN (9, 19);",
         .query = "CREATE INDEX channel_htlcs_speedup_unresolved_idx    ON channel_htlcs(channel_id, direction) WHERE hstate NOT IN (9, 19);",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "CREATE TABLE channels (  id BIGSERIAL,  peer_id BIGINT REFERENCES peers(id) ON DELETE CASCADE,  short_channel_id TEXT,  channel_config_local BIGINT,  channel_config_remote BIGINT,  state INTEGER,  funder INTEGER,  channel_flags INTEGER,  minimum_depth INTEGER,  next_index_local BIGINT,  next_index_remote BIGINT,  next_htlc_id BIGINT,  funding_tx_id BLOB,  funding_tx_outnum INTEGER,  funding_satoshi BIGINT,  funding_locked_remote INTEGER,  push_msatoshi BIGINT,  msatoshi_local BIGINT,  fundingkey_remote BLOB,  revocation_basepoint_remote BLOB,  payment_basepoint_remote BLOB,  htlc_basepoint_remote BLOB,  delayed_payment_basepoint_remote BLOB,  per_commit_remote BLOB,  old_per_commit_remote BLOB,  local_feerate_per_kw INTEGER,  remote_feerate_per_kw INTEGER,  shachain_remote_id BIGINT,  shutdown_scriptpubkey_remote BLOB,  shutdown_keyidx_local BIGINT,  last_sent_commit_state BIGINT,  last_sent_commit_id INTEGER,  last_tx BLOB,  last_sig BLOB,  closing_fee_received INTEGER,  closing_sig_received BLOB,  PRIMARY KEY (id));",
         .query = "CREATE TABLE channels (  id BIGSERIAL,  peer_id BIGINT REFERENCES peers(id) ON DELETE CASCADE,  short_channel_id TEXT,  channel_config_local BIGINT,  channel_config_remote BIGINT,  state INTEGER,  funder INTEGER,  channel_flags INTEGER,  minimum_depth INTEGER,  next_index_local BIGINT,  next_index_remote BIGINT,  next_htlc_id BIGINT,  funding_tx_id BYTEA,  funding_tx_outnum INTEGER,  funding_satoshi BIGINT,  funding_locked_remote INTEGER,  push_msatoshi BIGINT,  msatoshi_local BIGINT,  fundingkey_remote BYTEA,  revocation_basepoint_remote BYTEA,  payment_basepoint_remote BYTEA,  htlc_basepoint_remote BYTEA,  delayed_payment_basepoint_remote BYTEA,  per_commit_remote BYTEA,  old_per_commit_remote BYTEA,  local_feerate_per_kw INTEGER,  remote_feerate_per_kw INTEGER,  shachain_remote_id BIGINT,  shutdown_scriptpubkey_remote BYTEA,  shutdown_keyidx_local BIGINT,  last_sent_commit_state BIGINT,  last_sent_commit_id INTEGER,  last_tx BYTEA,  last_sig BYTEA,  closing_fee_received INTEGER,  closing_sig_received BYTEA,  PRIMARY KEY (id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "INSERT INTO forwards (  rowid, in_htlc_id, out_htlc_id, in_channel_scid, out_channel_scid, in_msatoshi, out_msatoshi, state, received_time, resolved_time, failcode, forward_style) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO forwards (  rowid, in_htlc_id, out_htlc_id, in_channel_scid, out_channel_scid, in_msatoshi, out_msatoshi, state, received_time, resolved_time, failcode, forward_style) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12);",
         .placeholders = 12,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD COLUMN commitment_point BLOB;",
         .query = "ALTER TABLE outputs ADD COLUMN commitment_point BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD shutdown_wrong_txid BLOB DEFAULT NULL",
         .query = "ALTER TABLE channels ADD shutdown_wrong_txid BYTEA DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX payments_update_idx ON payments (updated_index)",
         .query = "CREATE INDEX payments_update_idx ON payments (updated_index)",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD remote_ann_bitcoin_sig BLOB;",
         .query = "ALTER TABLE channels ADD remote_ann_bitcoin_sig BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD close_attempt_height INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD close_attempt_height INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD failupdate BLOB;",
         .query = "ALTER TABLE payments ADD failupdate BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD expiry_time BIGINT;",
         .query = "ALTER TABLE invoices ADD expiry_time BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX forwards_updated_idx ON forwards (updated_index)",
         .query = "CREATE INDEX forwards_updated_idx ON forwards (updated_index)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT into shachains (min_index, num_valid) VALUES (?, ?);",
         .query = "INSERT into shachains (min_index, num_valid) VALUES ($1, $2);",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_funding_inflights (  channel_id, funding_tx_id, funding_tx_outnum, funding_feerate, funding_satoshi, our_funding_satoshi, funding_psbt, funding_tx_remote_sigs_received, last_tx, last_sig, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt, lease_expiry, lease_blockheight_start, lease_fee, lease_satoshi, splice_amnt, i_am_initiator, force_sign_first, remote_funding) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO channel_funding_inflights (  channel_id, funding_tx_id, funding_tx_outnum, funding_feerate, funding_satoshi, our_funding_satoshi, funding_psbt, funding_tx_remote_sigs_received, last_tx, last_sig, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt, lease_expiry, lease_blockheight_start, lease_fee, lease_satoshi, splice_amnt, i_am_initiator, force_sign_first, remote_funding) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16, $17, $18, $19, $20, $21);",
         .placeholders = 21,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET status=?, completed_at=?, updated_index=? WHERE payment_hash=? AND partid=? AND groupid=?",
         .query = "UPDATE payments SET status=$1, completed_at=$2, updated_index=$3 WHERE payment_hash=$4 AND partid=$5 AND groupid=$6",
         .placeholders = 6,
         .readonly = false,
    },
    {
         .name = "UPDATE outputs SET status=?, reserved_til=? WHERE prev_out_tx=? AND prev_out_index=?",
         .query = "UPDATE outputs SET status=$1, reserved_til=$2 WHERE prev_out_tx=$3 AND prev_out_index=$4",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE  status = ? AND  updated_index >= ? ORDER BY updated_index LIMIT ?;",
         .query = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE  status = $1 AND  updated_index >= $2 ORDER BY updated_index LIMIT $3;",
         .placeholders = 3,
         .readonly = true,
         .colnames = col_table395,
         .num_colnames = ARRAY_SIZE(col_table395),
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD lease_chan_max_msat INTEGER DEFAULT NULL",
         .query = "ALTER TABLE channels ADD lease_chan_max_msat INTEGER DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT  commitment_txid , commitment_anchor_outnum , commitment_fee , commitment_weight FROM local_anchors WHERE channel_id = ?;",
         .query = "SELECT  commitment_txid , commitment_anchor_outnum , commitment_fee , commitment_weight FROM local_anchors WHERE channel_id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table475,
         .num_colnames = ARRAY_SIZE(col_table475),
    },
    {
         .name = "SELECT idx, hash, pos FROM shachain_known WHERE shachain_id=?",
         .query = "SELECT idx, hash, pos FROM shachain_known WHERE shachain_id=$1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table323,
         .num_colnames = ARRAY_SIZE(col_table323),
    },
    {
    },
    {
    },
    {
         .name = "UPDATE utxoset SET spendheight = ? WHERE txid = ? AND outnum = ?",
         .query = "UPDATE utxoset SET spendheight = $1 WHERE txid = $2 AND outnum = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "UPDATE invoices   SET state=?     , pay_index=?     , msatoshi_received=?     , paid_timestamp=?     , paid_txid=?     , paid_outnum=?     , updated_index=? WHERE id=?;",
         .query = "UPDATE invoices   SET state=$1     , pay_index=$2     , msatoshi_received=$3     , paid_timestamp=$4     , paid_txid=$5     , paid_outnum=$6     , updated_index=$7 WHERE id=$8;",
         .placeholders = 8,
         .readonly = false,
    },
    {
    },
    {
         .name = "UPDATE vars SET intval = intval + 1 WHERE name = 'data_version' AND intval = ?",
         .query = "UPDATE vars SET intval = intval + 1 WHERE name = 'data_version' AND intval = $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE forwarded_payments ADD forward_style INTEGER DEFAULT NULL",
         .query = "ALTER TABLE forwarded_payments ADD forward_style INTEGER DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD remote_funding BLOB DEFAULT NULL;",
         .query = "ALTER TABLE channel_funding_inflights ADD remote_funding BYTEA DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE payments   SET path_secrets = NULL     , route_nodes = NULL     , route_channels = NULL WHERE status <> 0;",
         .query = "UPDATE payments   SET path_secrets = NULL     , route_nodes = NULL     , route_channels = NULL WHERE status <> 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE invoices SET bolt11 = ? WHERE id = ?;",
         .query = "UPDATE invoices SET bolt11 = $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD out_msatoshi_offered BIGINT DEFAULT 0;",
         .query = "ALTER TABLE channels ADD out_msatoshi_offered BIGINT DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE forwards (in_channel_scid BIGINT, in_htlc_id BIGINT, out_channel_scid BIGINT, out_htlc_id BIGINT, in_msatoshi BIGINT, out_msatoshi BIGINT, state INTEGER, received_time BIGINT, resolved_time BIGINT, failcode INTEGER, forward_style INTEGER, PRIMARY KEY(in_channel_scid, in_htlc_id))",
         .query = "CREATE TABLE forwards (in_channel_scid BIGINT, in_htlc_id BIGINT, out_channel_scid BIGINT, out_htlc_id BIGINT, in_msatoshi BIGINT, out_msatoshi BIGINT, state INTEGER, received_time BIGINT, resolved_time BIGINT, failcode INTEGER, forward_style INTEGER, PRIMARY KEY(in_channel_scid, in_htlc_id))",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE invoices ADD description TEXT;",
         .query = "ALTER TABLE invoices ADD description TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO payments (  id,  status,  payment_hash,  destination,  msatoshi,  timestamp,  path_secrets,  route_nodes,  route_channels,  msatoshi_sent,  description,  bolt11,  total_msat,  partid,  local_invreq_id,  groupid,  paydescription) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO payments (  id,  status,  payment_hash,  destination,  msatoshi,  timestamp,  path_secrets,  route_nodes,  route_channels,  msatoshi_sent,  description,  bolt11,  total_msat,  partid,  local_invreq_id,  groupid,  paydescription) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14, $15, $16, $17);",
         .placeholders = 17,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT id, failchannel FROM payments",
         .query = "SELECT id, failchannel FROM payments",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table264,
         .num_colnames = ARRAY_SIZE(col_table264),
    },
    {
    },
    {
    },
    {
         .name = "SELECT  state, payment_key, payment_hash, label, msatoshi, expiry_time, pay_index, msatoshi_received, paid_timestamp, paid_txid, paid_outnum, bolt11, description, features, local_offer_id, id, updated_index FROM invoices WHERE id = ?;",
         .query = "SELECT  state, payment_key, payment_hash, label, msatoshi, expiry_time, pay_index, msatoshi_received, paid_timestamp, paid_txid, paid_outnum, bolt11, description, features, local_offer_id, id, updated_index FROM invoices WHERE id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table302,
         .num_colnames = ARRAY_SIZE(col_table302),
    },
    {
         .name = "UPDATE runes SET last_used_nsec = ? WHERE id = ?;",
         .query = "UPDATE runes SET last_used_nsec = $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD remote_htlc_minimum_msat BIGINT DEFAULT NULL;",
         .query = "ALTER TABLE channels ADD remote_htlc_minimum_msat BIGINT DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD failnode BLOB;",
         .query = "ALTER TABLE payments ADD failnode BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO htlc_sigs (channelid, inflight_tx_id, inflight_tx_outnum, signature) VALUES (?, ?, ?, ?)",
         .query = "INSERT INTO htlc_sigs (channelid, inflight_tx_id, inflight_tx_outnum, signature) VALUES ($1, $2, $3, $4)",
         .placeholders = 4,
         .readonly = false,
    },
    {
    },
    {
         .name = "ALTER TABLE peers ADD feature_bits BLOB DEFAULT NULL;",
         .query = "ALTER TABLE peers ADD feature_bits BYTEA DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE outputs ADD is_in_coinbase INTEGER DEFAULT 0;",
         .query = "ALTER TABLE outputs ADD is_in_coinbase INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT CAST(COALESCE(SUM(in_msatoshi - out_msatoshi), 0) AS BIGINT) FROM forwards WHERE state = ?;",
         .query = "SELECT CAST(COALESCE(SUM(in_msatoshi - out_msatoshi), 0) AS BIGINT) FROM forwards WHERE state = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table430,
         .num_colnames = ARRAY_SIZE(col_table430),
    },
    {
    },
    {
         .name = "INSERT INTO vars VALUES ('data_version', 0);",
         .query = "INSERT INTO vars VALUES ('data_version', 0);",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til, csv_lock, is_in_coinbase FROM outputs WHERE status = ? OR (status = ? AND reserved_til <= ?)",
         .query = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til, csv_lock, is_in_coinbase FROM outputs WHERE status = $1 OR (status = $2 AND reserved_til <= $3)",
         .placeholders = 3,
         .readonly = true,
         .colnames = col_table314,
         .num_colnames = ARRAY_SIZE(col_table314),
    },
    {
         .name = "INSERT INTO channel_blockheights  VALUES(?, ?, ?)",
         .query = "INSERT INTO channel_blockheights  VALUES($1, $2, $3)",
         .placeholders = 3,
         .readonly = false,
    },
    {
    },
    {
         .name = "SELECT status  FROM offers WHERE offer_id = ?;",
         .query = "SELECT status  FROM offers WHERE offer_id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table448,
         .num_colnames = ARRAY_SIZE(col_table448),
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD localfailmsg BLOB;",
         .query = "ALTER TABLE channel_htlcs ADD localfailmsg BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "SELECT MAX(height) FROM blocks;",
         .query = "SELECT MAX(height) FROM blocks;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table344,
         .num_colnames = ARRAY_SIZE(col_table344),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD alias_remote BIGINT DEFAULT NULL",
         .query = "ALTER TABLE channels ADD alias_remote BIGINT DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT CAST(COALESCE(SUM(in_msatoshi - out_msatoshi), 0) AS BIGINT) FROM forwards  WHERE in_channel_scid = ? AND in_htlc_id = ? AND state = ?;",
         .query = "SELECT CAST(COALESCE(SUM(in_msatoshi - out_msatoshi), 0) AS BIGINT) FROM forwards  WHERE in_channel_scid = $1 AND in_htlc_id = $2 AND state = $3;",
         .placeholders = 3,
         .readonly = true,
         .colnames = col_table434,
         .num_colnames = ARRAY_SIZE(col_table434),
    },
    {
         .name = "CREATE INDEX short_channel_id ON utxoset (blockheight, txindex, outnum)",
         .query = "CREATE INDEX short_channel_id ON utxoset (blockheight, txindex, outnum)",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT id FROM invoices WHERE updated_index >= ? ORDER BY updated_index LIMIT ?;",
         .query = "SELECT id FROM invoices WHERE updated_index >= $1 ORDER BY updated_index LIMIT $2;",
         .placeholders = 2,
         .readonly = true,
         .colnames = col_table296,
         .num_colnames = ARRAY_SIZE(col_table296),
    },
    {
         .name = "UPDATE htlc_sigs SET inflight_tx_id=NULL WHERE channelid=?",
         .query = "UPDATE htlc_sigs SET inflight_tx_id=NULL WHERE channelid=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE runes ADD last_used_nsec BIGINT DEFAULT NULL",
         .query = "ALTER TABLE runes ADD last_used_nsec BIGINT DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT field1 FROM tableb;",
         .query = "SELECT field1 FROM tableb;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table487,
         .num_colnames = ARRAY_SIZE(col_table487),
    },
    {
         .name = "ALTER TABLE payments ADD COLUMN route_nodes BLOB;",
         .query = "ALTER TABLE payments ADD COLUMN route_nodes BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD COLUMN option_static_remotekey INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD COLUMN option_static_remotekey INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT  state, in_msatoshi, out_msatoshi, in_channel_scid, out_channel_scid, in_htlc_id, out_htlc_id, received_time, resolved_time, failcode , forward_style , rowid , updated_index FROM forwards  WHERE  (1 = ? OR state = ?) AND  updated_index >= ? ORDER BY updated_index LIMIT ?;",
         .query = "SELECT  state, in_msatoshi, out_msatoshi, in_channel_scid, out_channel_scid, in_htlc_id, out_htlc_id, received_time, resolved_time, failcode , forward_style , rowid , updated_index FROM forwards  WHERE  (1 = $1 OR state = $2) AND  updated_index >= $3 ORDER BY updated_index LIMIT $4;",
         .placeholders = 4,
         .readonly = true,
         .colnames = col_table432,
         .num_colnames = ARRAY_SIZE(col_table432),
    },
    {
    },
    {
    },
    {
         .name = "SELECT id, field2 FROM tableb;",
         .query = "SELECT id, field2 FROM tableb;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table485,
         .num_colnames = ARRAY_SIZE(col_table485),
    },
    {
    },
    {
         .name = "CREATE TABLE htlc_sigs (channelid INTEGER REFERENCES channels(id) ON DELETE CASCADE, signature BLOB);",
         .query = "CREATE TABLE htlc_sigs (channelid INTEGER REFERENCES channels(id) ON DELETE CASCADE, signature BYTEA);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channel_htlcs (  id BIGSERIAL,  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  channel_htlc_id BIGINT,  direction INTEGER,  origin_htlc BIGINT,  msatoshi BIGINT,  cltv_expiry INTEGER,  payment_hash BLOB,  payment_key BLOB,  routing_onion BLOB,  failuremsg BLOB,  malformed_onion INTEGER,  hstate INTEGER,  shared_secret BLOB,  PRIMARY KEY (id),  UNIQUE (channel_id, channel_htlc_id, direction));",
         .query = "CREATE TABLE channel_htlcs (  id BIGSERIAL,  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  channel_htlc_id BIGINT,  direction INTEGER,  origin_htlc BIGINT,  msatoshi BIGINT,  cltv_expiry INTEGER,  payment_hash BYTEA,  payment_key BYTEA,  routing_onion BYTEA,  failuremsg BYTEA,  malformed_onion INTEGER,  hstate INTEGER,  shared_secret BYTEA,  PRIMARY KEY (id),  UNIQUE (channel_id, channel_htlc_id, direction));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels   SET out_payments_fulfilled = COALESCE(out_payments_fulfilled, 0) + 1     , out_msatoshi_fulfilled = COALESCE(out_msatoshi_fulfilled, 0) + ? WHERE id = ?;",
         .query = "UPDATE channels   SET out_payments_fulfilled = COALESCE(out_payments_fulfilled, 0) + 1     , out_msatoshi_fulfilled = COALESCE(out_msatoshi_fulfilled, 0) + $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD funding_tx_remote_sigs_received INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD funding_tx_remote_sigs_received INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM channel_funding_inflights  WHERE channel_id=?",
         .query = "DELETE FROM channel_funding_inflights  WHERE channel_id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
         .name = "SELECT COUNT(1) FROM channel_funding_inflights WHERE channel_id = ?;",
         .query = "SELECT COUNT(1) FROM channel_funding_inflights WHERE channel_id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table488,
         .num_colnames = ARRAY_SIZE(col_table488),
    },
    {
         .name = "UPDATE outputs SET confirmation_height = ? WHERE prev_out_tx = ?",
         .query = "UPDATE outputs SET confirmation_height = $1 WHERE prev_out_tx = $2",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "INSERT INTO blocks (height, hash, prev_hash) VALUES (?, ?, ?);",
         .query = "INSERT INTO blocks (height, hash, prev_hash) VALUES ($1, $2, $3);",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_htlcs SET payment_key=NULL, routing_onion=NULL, failuremsg=NULL, shared_secret=NULL, localfailmsg=NULL WHERE (hstate=9 OR hstate=19);",
         .query = "UPDATE channel_htlcs SET payment_key=NULL, routing_onion=NULL, failuremsg=NULL, shared_secret=NULL, localfailmsg=NULL WHERE (hstate=9 OR hstate=19);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD received_time BIGINT",
         .query = "ALTER TABLE channel_htlcs ADD received_time BIGINT",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT id  FROM invoices WHERE payment_hash = ?;",
         .query = "SELECT id  FROM invoices WHERE payment_hash = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table290,
         .num_colnames = ARRAY_SIZE(col_table290),
    },
    {
         .name = "UPDATE channels SET last_tx = ? WHERE id = ?;",
         .query = "UPDATE channels SET last_tx = $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "SELECT id, field1a FROM tablea;",
         .query = "SELECT id, field1a FROM tablea;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table484,
         .num_colnames = ARRAY_SIZE(col_table484),
    },
    {
    },
    {
         .name = "CREATE TABLE vars (name VARCHAR(32), intval);",
         .query = "CREATE TABLE vars (name VARCHAR(32), intval);",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD out_payments_fulfilled INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD out_payments_fulfilled INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD in_payments_fulfilled INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD in_payments_fulfilled INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM utxoset WHERE spendheight < ?",
         .query = "DELETE FROM utxoset WHERE spendheight < $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
         .name = "UPDATE payments   SET faildetail = 'unspecified payment failure reason' WHERE status = 2;",
         .query = "UPDATE payments   SET faildetail = 'unspecified payment failure reason' WHERE status = 2;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE runes (id BIGSERIAL, rune TEXT, PRIMARY KEY (id));",
         .query = "CREATE TABLE runes (id BIGSERIAL, rune TEXT, PRIMARY KEY (id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE vars ADD COLUMN intval INTEGER",
         .query = "ALTER TABLE vars ADD COLUMN intval INTEGER",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT timestamp, old_state, new_state, cause, message FROM channel_state_changes WHERE channel_id = ? ORDER BY timestamp ASC;",
         .query = "SELECT timestamp, old_state, new_state, cause, message FROM channel_state_changes WHERE channel_id = $1 ORDER BY timestamp ASC;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table336,
         .num_colnames = ARRAY_SIZE(col_table336),
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "DELETE FROM channeltxs WHERE channel_id=?",
         .query = "DELETE FROM channeltxs WHERE channel_id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "SELECT rune, last_used_nsec FROM runes",
         .query = "SELECT rune, last_used_nsec FROM runes",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table467,
         .num_colnames = ARRAY_SIZE(col_table467),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD lease_commit_sig BLOB DEFAULT NULL",
         .query = "ALTER TABLE channels ADD lease_commit_sig BYTEA DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "CREATE INDEX channel_state_changes_channel_id ON channel_state_changes (channel_id);",
         .query = "CREATE INDEX channel_state_changes_channel_id ON channel_state_changes (channel_id);",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO penalty_bases (  channel_id, commitnum, txid, outnum, amount) VALUES (?, ?, ?, ?, ?);",
         .query = "INSERT INTO penalty_bases (  channel_id, commitnum, txid, outnum, amount) VALUES ($1, $2, $3, $4, $5);",
         .placeholders = 5,
         .readonly = false,
    },
    {
    },
    {
         .name = "ALTER TABLE transactions ADD channel_id BIGINT;",
         .query = "ALTER TABLE transactions ADD channel_id BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT id FROM invoices WHERE id >= ? ORDER BY id LIMIT ?;",
         .query = "SELECT id FROM invoices WHERE id >= $1 ORDER BY id LIMIT $2;",
         .placeholders = 2,
         .readonly = true,
         .colnames = col_table297,
         .num_colnames = ARRAY_SIZE(col_table297),
    },
    {
         .name = "UPDATE shachains SET num_valid=?, min_index=? WHERE id=?",
         .query = "UPDATE shachains SET num_valid=$1, min_index=$2 WHERE id=$3",
         .placeholders = 3,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE id >= ? ORDER BY id LIMIT ?;",
         .query = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE id >= $1 ORDER BY id LIMIT $2;",
         .placeholders = 2,
         .readonly = true,
         .colnames = col_table392,
         .num_colnames = ARRAY_SIZE(col_table392),
    },
    {
         .name = "SELECT  id, peer_id, scid, full_channel_id, channel_config_local, channel_config_remote, state, funder, channel_flags, require_confirm_inputs_local, require_confirm_inputs_remote, minimum_depth, next_index_local, next_index_remote, next_htlc_id, funding_tx_id, funding_tx_outnum, funding_satoshi, our_funding_satoshi, funding_locked_remote, push_msatoshi, msatoshi_local, fundingkey_remote, revocation_basepoint_remote, payment_basepoint_remote, htlc_basepoint_remote, delayed_payment_basepoint_remote, per_commit_remote, old_per_commit_remote, shachain_remote_id, shutdown_scriptpubkey_remote, shutdown_keyidx_local, last_sent_commit_state, last_sent_commit_id, last_tx, last_sig, last_was_revoke, first_blocknum, min_possible_feerate, max_possible_feerate, msatoshi_to_us_min, msatoshi_to_us_max, future_per_commitment_point, last_sent_commit, feerate_base, feerate_ppm, remote_upfront_shutdown_script, local_static_remotekey_start, remote_static_remotekey_start, channel_type, shutdown_scriptpubkey_local, closer, state_change_reason, revocation_basepoint_local, payment_basepoint_local, htlc_basepoint_local, delayed_payment_basepoint_local, funding_pubkey_local, shutdown_wrong_txid, shutdown_wrong_outnum, lease_expiry, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt, htlc_minimum_msat, htlc_maximum_msat, alias_local, alias_remote, ignore_fee_limits, remote_feerate_base, remote_feerate_ppm, remote_cltv_expiry_delta, remote_htlc_minimum_msat, remote_htlc_maximum_msat, last_stable_connection, in_payments_offered, in_payments_fulfilled, in_msatoshi_offered, in_msatoshi_fulfilled, out_payments_offered, out_payments_fulfilled, out_msatoshi_offered, out_msatoshi_fulfilled, close_attempt_height FROM channels WHERE state != ?;",
         .query = "SELECT  id, peer_id, scid, full_channel_id, channel_config_local, channel_config_remote, state, funder, channel_flags, require_confirm_inputs_local, require_confirm_inputs_remote, minimum_depth, next_index_local, next_index_remote, next_htlc_id, funding_tx_id, funding_tx_outnum, funding_satoshi, our_funding_satoshi, funding_locked_remote, push_msatoshi, msatoshi_local, fundingkey_remote, revocation_basepoint_remote, payment_basepoint_remote, htlc_basepoint_remote, delayed_payment_basepoint_remote, per_commit_remote, old_per_commit_remote, shachain_remote_id, shutdown_scriptpubkey_remote, shutdown_keyidx_local, last_sent_commit_state, last_sent_commit_id, last_tx, last_sig, last_was_revoke, first_blocknum, min_possible_feerate, max_possible_feerate, msatoshi_to_us_min, msatoshi_to_us_max, future_per_commitment_point, last_sent_commit, feerate_base, feerate_ppm, remote_upfront_shutdown_script, local_static_remotekey_start, remote_static_remotekey_start, channel_type, shutdown_scriptpubkey_local, closer, state_change_reason, revocation_basepoint_local, payment_basepoint_local, htlc_basepoint_local, delayed_payment_basepoint_local, funding_pubkey_local, shutdown_wrong_txid, shutdown_wrong_outnum, lease_expiry, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt, htlc_minimum_msat, htlc_maximum_msat, alias_local, alias_remote, ignore_fee_limits, remote_feerate_base, remote_feerate_ppm, remote_cltv_expiry_delta, remote_htlc_minimum_msat, remote_htlc_maximum_msat, last_stable_connection, in_payments_offered, in_payments_fulfilled, in_msatoshi_offered, in_msatoshi_fulfilled, out_payments_offered, out_payments_fulfilled, out_msatoshi_offered, out_msatoshi_fulfilled, close_attempt_height FROM channels WHERE state != $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table339,
         .num_colnames = ARRAY_SIZE(col_table339),
    },
    {
         .name = "DELETE FROM channel_feerates WHERE channel_id=?",
         .query = "DELETE FROM channel_feerates WHERE channel_id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "DELETE FROM vars WHERE name = 'runes_uniqueid'",
         .query = "DELETE FROM vars WHERE name = 'runes_uniqueid'",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD failonionreply BLOB;",
         .query = "ALTER TABLE payments ADD failonionreply BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD splice_amnt BIGINT DEFAULT 0",
         .query = "ALTER TABLE channel_funding_inflights ADD splice_amnt BIGINT DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD COLUMN last_was_revoke INTEGER;",
         .query = "ALTER TABLE channels ADD COLUMN last_was_revoke INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "DELETE FROM blocks WHERE height IS NULL;",
         .query = "DELETE FROM blocks WHERE height IS NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE channels SET full_channel_id = ? WHERE id = ?;",
         .query = "UPDATE channels SET full_channel_id = $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "SELECT  funding_tx_id, funding_tx_outnum, funding_feerate, funding_satoshi, our_funding_satoshi, funding_psbt, last_tx, last_sig, funding_tx_remote_sigs_received, lease_expiry, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt, lease_blockheight_start, lease_fee, lease_satoshi, splice_amnt, i_am_initiator, force_sign_first, remote_funding FROM channel_funding_inflights WHERE channel_id = ? ORDER BY funding_feerate",
         .query = "SELECT  funding_tx_id, funding_tx_outnum, funding_feerate, funding_satoshi, our_funding_satoshi, funding_psbt, last_tx, last_sig, funding_tx_remote_sigs_received, lease_expiry, lease_commit_sig, lease_chan_max_msat, lease_chan_max_ppt, lease_blockheight_start, lease_fee, lease_satoshi, splice_amnt, i_am_initiator, force_sign_first, remote_funding FROM channel_funding_inflights WHERE channel_id = $1 ORDER BY funding_feerate",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table334,
         .num_colnames = ARRAY_SIZE(col_table334),
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD lease_commit_sig BLOB DEFAULT NULL",
         .query = "ALTER TABLE channel_funding_inflights ADD lease_commit_sig BYTEA DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "INSERT INTO offers (  offer_id, bolt12, label, status) VALUES (?, ?, ?, ?);",
         .query = "INSERT INTO offers (  offer_id, bolt12, label, status) VALUES ($1, $2, $3, $4);",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD csv_lock INTEGER DEFAULT 1;",
         .query = "ALTER TABLE outputs ADD csv_lock INTEGER DEFAULT 1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM blocks WHERE height > ?",
         .query = "DELETE FROM blocks WHERE height > $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "DELETE FROM payments WHERE payment_hash = ?   AND groupid = ?   AND partid = ?   AND status = ?",
         .query = "DELETE FROM payments WHERE payment_hash = $1   AND groupid = $2   AND partid = $3   AND status = $4",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channel_blockheights (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  hstate INTEGER,  blockheight INTEGER,  UNIQUE (channel_id, hstate));",
         .query = "CREATE TABLE channel_blockheights (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  hstate INTEGER,  blockheight INTEGER,  UNIQUE (channel_id, hstate));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET state=? WHERE channels.id=?",
         .query = "UPDATE channels SET state=$1 WHERE channels.id=$2",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "DROP INDEX forwarded_payments_out_htlc_id;",
         .query = "DROP INDEX forwarded_payments_out_htlc_id;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "SELECT   c.id, p.node_id, c.fundingkey_remote, inflight.last_tx, inflight.last_sig, inflight.funding_satoshi, inflight.funding_tx_id FROM channels c  LEFT OUTER JOIN peers p   ON p.id = c.peer_id  LEFT OUTER JOIN   channel_funding_inflights inflight   ON c.id = inflight.channel_id WHERE inflight.last_tx IS NOT NULL;",
         .query = "SELECT   c.id, p.node_id, c.fundingkey_remote, inflight.last_tx, inflight.last_sig, inflight.funding_satoshi, inflight.funding_tx_id FROM channels c  LEFT OUTER JOIN peers p   ON p.id = c.peer_id  LEFT OUTER JOIN   channel_funding_inflights inflight   ON c.id = inflight.channel_id WHERE inflight.last_tx IS NOT NULL;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table257,
         .num_colnames = ARRAY_SIZE(col_table257),
    },
    {
    },
    {
         .name = "CREATE TABLE forwarded_payments (  in_htlc_id BIGINT REFERENCES channel_htlcs(id) ON DELETE SET NULL, out_htlc_id BIGINT REFERENCES channel_htlcs(id) ON DELETE SET NULL, in_channel_scid BIGINT, out_channel_scid BIGINT, in_msatoshi BIGINT, out_msatoshi BIGINT, state INTEGER, UNIQUE(in_htlc_id, out_htlc_id));",
         .query = "CREATE TABLE forwarded_payments (  in_htlc_id BIGINT REFERENCES channel_htlcs(id) ON DELETE SET NULL, out_htlc_id BIGINT REFERENCES channel_htlcs(id) ON DELETE SET NULL, in_channel_scid BIGINT, out_channel_scid BIGINT, in_msatoshi BIGINT, out_msatoshi BIGINT, state INTEGER, UNIQUE(in_htlc_id, out_htlc_id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE peers SET address = ?, feature_bits = ? WHERE id = ?",
         .query = "UPDATE peers SET address = $1, feature_bits = $2 WHERE id = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD i_am_initiator INTEGER DEFAULT 0",
         .query = "ALTER TABLE channel_funding_inflights ADD i_am_initiator INTEGER DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "CREATE TABLE datastore (  key BLOB,  data BLOB,  generation BIGINT,  PRIMARY KEY (key));",
         .query = "CREATE TABLE datastore (  key BYTEA,  data BYTEA,  generation BIGINT,  PRIMARY KEY (key));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_funding_inflights SET lease_satoshi = 0 WHERE lease_satoshi IS NULL;",
         .query = "UPDATE channel_funding_inflights SET lease_satoshi = 0 WHERE lease_satoshi IS NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM channel_funding_inflights WHERE channel_id = ?",
         .query = "DELETE FROM channel_funding_inflights WHERE channel_id = $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "SELECT blobval FROM vars WHERE name='genesis_hash'",
         .query = "SELECT blobval FROM vars WHERE name='genesis_hash'",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table401,
         .num_colnames = ARRAY_SIZE(col_table401),
    },
    {
    },
    {
         .name = "SELECT txid, outnum FROM utxoset WHERE spendheight < ?",
         .query = "SELECT txid, outnum FROM utxoset WHERE spendheight < $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table405,
         .num_colnames = ARRAY_SIZE(col_table405),
    },
    {
         .name = "DELETE FROM channel_funding_inflights WHERE channel_id = ?   AND funding_tx_id = ?   AND funding_tx_outnum = ?",
         .query = "DELETE FROM channel_funding_inflights WHERE channel_id = $1   AND funding_tx_id = $2   AND funding_tx_outnum = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET failchannel = REPLACE(failchannel, ':', 'x') WHERE failchannel IS NOT NULL;",
         .query = "UPDATE payments SET failchannel = REPLACE(failchannel, ':', 'x') WHERE failchannel IS NOT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE invoices ADD bolt11 TEXT;",
         .query = "ALTER TABLE invoices ADD bolt11 TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD in_msatoshi_fulfilled BIGINT DEFAULT 0;",
         .query = "ALTER TABLE channels ADD in_msatoshi_fulfilled BIGINT DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD faildirection INTEGER;",
         .query = "ALTER TABLE payments ADD faildirection INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE transactions SET blockheight = ?, txindex = ? WHERE id = ?",
         .query = "UPDATE transactions SET blockheight = $1, txindex = $2 WHERE id = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "INSERT INTO utxoset ( txid, outnum, blockheight, spendheight, txindex, scriptpubkey, satoshis) VALUES(?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO utxoset ( txid, outnum, blockheight, spendheight, txindex, scriptpubkey, satoshis) VALUES($1, $2, $3, $4, $5, $6, $7);",
         .placeholders = 7,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "SELECT * from outputs WHERE prev_out_tx=? AND prev_out_index=?",
         .query = "SELECT * from outputs WHERE prev_out_tx=$1 AND prev_out_index=$2",
         .placeholders = 2,
         .readonly = true,
         .colnames = col_table304,
         .num_colnames = ARRAY_SIZE(col_table304),
    },
    {
    },
    {
         .name = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE payment_hash = ? AND partid = ? AND groupid=?",
         .query = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE payment_hash = $1 AND partid = $2 AND groupid=$3",
         .placeholders = 3,
         .readonly = true,
         .colnames = col_table385,
         .num_colnames = ARRAY_SIZE(col_table385),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD COLUMN local_offer_id BLOB DEFAULT NULL REFERENCES offers(offer_id);",
         .query = "ALTER TABLE payments ADD COLUMN local_offer_id BYTEA DEFAULT NULL REFERENCES offers(offer_id);",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO invoicerequests (  invreq_id, bolt12, label, status) VALUES (?, ?, ?, ?);",
         .query = "INSERT INTO invoicerequests (  invreq_id, bolt12, label, status) VALUES ($1, $2, $3, $4);",
         .placeholders = 4,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT field1 FROM tablea;",
         .query = "SELECT field1 FROM tablea;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table486,
         .num_colnames = ARRAY_SIZE(col_table486),
    },
    {
    },
    {
         .name = "INSERT INTO runes_blacklist VALUES (?,?)",
         .query = "INSERT INTO runes_blacklist VALUES ($1,$2)",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE forwards ADD rowid BIGINT",
         .query = "ALTER TABLE forwards ADD rowid BIGINT",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "DELETE FROM channels WHERE state=1",
         .query = "DELETE FROM channels WHERE state=1",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_blockheights  (channel_id, hstate, blockheight) SELECT id, 4, 0 FROM channels WHERE funder = 0;",
         .query = "INSERT INTO channel_blockheights  (channel_id, hstate, blockheight) SELECT id, 4, 0 FROM channels WHERE funder = 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "INSERT INTO blocks (height) VALUES ((SELECT MIN(first_blocknum) FROM channels)) ON CONFLICT(height) DO NOTHING;",
         .query = "INSERT INTO blocks (height) VALUES ((SELECT MIN(first_blocknum) FROM channels)) ON CONFLICT(height) DO NOTHING;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD we_filled INTEGER;",
         .query = "ALTER TABLE channel_htlcs ADD we_filled INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX forwarded_payments_state ON forwarded_payments (state)",
         .query = "CREATE INDEX forwarded_payments_state ON forwarded_payments (state)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX local_anchors_idx ON local_anchors (channel_id)",
         .query = "CREATE INDEX local_anchors_idx ON local_anchors (channel_id)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "WITH numbered_rows AS ( SELECT in_channel_scid, in_htlc_id, row_number() OVER () AS rn FROM forwards) UPDATE forwards SET rowid = numbered_rows.rn FROM numbered_rows WHERE forwards.in_channel_scid = numbered_rows.in_channel_scid AND forwards.in_htlc_id = numbered_rows.in_htlc_id;",
         .query = "WITH numbered_rows AS ( SELECT in_channel_scid, in_htlc_id, row_number() OVER () AS rn FROM forwards) UPDATE forwards SET rowid = numbered_rows.rn FROM numbered_rows WHERE forwards.in_channel_scid = numbered_rows.in_channel_scid AND forwards.in_htlc_id = numbered_rows.in_htlc_id;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_configs DEFAULT VALUES;",
         .query = "INSERT INTO channel_configs DEFAULT VALUES;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD completed_at INTEGER DEFAULT NULL;",
         .query = "ALTER TABLE payments ADD completed_at INTEGER DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO vars(name, val)  VALUES('next_pay_index',     COALESCE((SELECT MAX(pay_index) FROM invoices WHERE state=1), 0) + 1  );",
         .query = "INSERT INTO vars(name, val)  VALUES('next_pay_index',     COALESCE((SELECT MAX(pay_index) FROM invoices WHERE state=1), 0) + 1  );",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT addrtype FROM addresses WHERE keyidx=?",
         .query = "SELECT addrtype FROM addresses WHERE keyidx=$1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table316,
         .num_colnames = ARRAY_SIZE(col_table316),
    },
    {
         .name = "ALTER TABLE channels ADD remote_htlc_maximum_msat BIGINT DEFAULT NULL;",
         .query = "ALTER TABLE channels ADD remote_htlc_maximum_msat BIGINT DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE vars SET intval = CAST(val AS INTEGER) WHERE name IN ('bip32_max_index', 'last_processed_block', 'next_pay_index')",
         .query = "UPDATE vars SET intval = CAST(val AS INTEGER) WHERE name IN ('bip32_max_index', 'last_processed_block', 'next_pay_index')",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "CREATE TABLE transactions (  id BLOB, blockheight INTEGER REFERENCES blocks(height) ON DELETE SET NULL, txindex INTEGER, rawtx BLOB, PRIMARY KEY (id));",
         .query = "CREATE TABLE transactions (  id BYTEA, blockheight INTEGER REFERENCES blocks(height) ON DELETE SET NULL, txindex INTEGER, rawtx BYTEA, PRIMARY KEY (id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "CREATE INDEX payments_idx ON payments (payment_hash)",
         .query = "CREATE INDEX payments_idx ON payments (payment_hash)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channeltxs (  id BIGSERIAL, channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE, type INTEGER, transaction_id BLOB REFERENCES transactions(id) ON DELETE CASCADE, input_num INTEGER, blockheight INTEGER REFERENCES blocks(height) ON DELETE CASCADE, PRIMARY KEY(id));",
         .query = "CREATE TABLE channeltxs (  id BIGSERIAL, channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE, type INTEGER, transaction_id BYTEA REFERENCES transactions(id) ON DELETE CASCADE, input_num INTEGER, blockheight INTEGER REFERENCES blocks(height) ON DELETE CASCADE, PRIMARY KEY(id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_htlcs SET malformed_onion = 0 WHERE malformed_onion IS NULL",
         .query = "UPDATE channel_htlcs SET malformed_onion = 0 WHERE malformed_onion IS NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "SELECT  channels.id, peers.node_id FROM  channels JOIN  peers ON (peers.id = channels.peer_id)",
         .query = "SELECT  channels.id, peers.node_id FROM  channels JOIN  peers ON (peers.id = channels.peer_id)",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table253,
         .num_colnames = ARRAY_SIZE(col_table253),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT id  FROM invoices WHERE label = ?;",
         .query = "SELECT id  FROM invoices WHERE label = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table289,
         .num_colnames = ARRAY_SIZE(col_table289),
    },
    {
         .name = "SELECT rawtx FROM transactions WHERE id=?",
         .query = "SELECT rawtx FROM transactions WHERE id=$1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table423,
         .num_colnames = ARRAY_SIZE(col_table423),
    },
    {
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD COLUMN max_commit_num BIGINT default NULL;",
         .query = "ALTER TABLE channel_htlcs ADD COLUMN max_commit_num BIGINT default NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE local_anchors (  channel_id BIGSERIAL REFERENCES channels(id),  commitment_index BIGINT,  commitment_txid BLOB,  commitment_anchor_outnum INTEGER,  commitment_fee BIGINT,  commitment_weight INTEGER)",
         .query = "CREATE TABLE local_anchors (  channel_id BIGSERIAL REFERENCES channels(id),  commitment_index BIGINT,  commitment_txid BYTEA,  commitment_anchor_outnum INTEGER,  commitment_fee BIGINT,  commitment_weight INTEGER)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD lease_blockheight_start INTEGER DEFAULT 0",
         .query = "ALTER TABLE channel_funding_inflights ADD lease_blockheight_start INTEGER DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT bolt11, id FROM payments WHERE bolt11 IS NOT NULL;",
         .query = "SELECT bolt11, id FROM payments WHERE bolt11 IS NOT NULL;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table280,
         .num_colnames = ARRAY_SIZE(col_table280),
    },
    {
         .name = "SELECT offer_id FROM offers;",
         .query = "SELECT offer_id FROM offers;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table445,
         .num_colnames = ARRAY_SIZE(col_table445),
    },
    {
         .name = "SELECT start_index, end_index FROM runes_blacklist ORDER BY start_index ASC",
         .query = "SELECT start_index, end_index FROM runes_blacklist ORDER BY start_index ASC",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table464,
         .num_colnames = ARRAY_SIZE(col_table464),
    },
    {
    },
    {
    },
    {
         .name = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til , csv_lock , is_in_coinbase FROM outputs WHERE status != ?",
         .query = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til , csv_lock , is_in_coinbase FROM outputs WHERE status != $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table309,
         .num_colnames = ARRAY_SIZE(col_table309),
    },
    {
    },
    {
         .name = "CREATE TABLE vars (  name VARCHAR(32), val VARCHAR(255), PRIMARY KEY (name));",
         .query = "CREATE TABLE vars (  name VARCHAR(32), val VARCHAR(255), PRIMARY KEY (name));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE htlc_sigs ADD inflight_tx_outnum INTEGER",
         .query = "ALTER TABLE htlc_sigs ADD inflight_tx_outnum INTEGER",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE outputs SET scriptpubkey = ? WHERE prev_out_tx = ?    AND prev_out_index = ?",
         .query = "UPDATE outputs SET scriptpubkey = $1 WHERE prev_out_tx = $2    AND prev_out_index = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX channel_idx ON htlc_sigs (channelid)",
         .query = "CREATE INDEX channel_idx ON htlc_sigs (channelid)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT bolt11, id FROM invoices WHERE bolt11 IS NOT NULL;",
         .query = "SELECT bolt11, id FROM invoices WHERE bolt11 IS NOT NULL;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table278,
         .num_colnames = ARRAY_SIZE(col_table278),
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD lease_chan_max_msat BIGINT DEFAULT NULL",
         .query = "ALTER TABLE channel_funding_inflights ADD lease_chan_max_msat BIGINT DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD out_payments_offered INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD out_payments_offered INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels   SET out_payments_offered = COALESCE(out_payments_offered, 0) + 1     , out_msatoshi_offered = COALESCE(out_msatoshi_offered, 0) + ? WHERE id = ?;",
         .query = "UPDATE channels   SET out_payments_offered = COALESCE(out_payments_offered, 0) + 1     , out_msatoshi_offered = COALESCE(out_msatoshi_offered, 0) + $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE peers SET last_known_address = ? WHERE id = ?;",
         .query = "UPDATE peers SET last_known_address = $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_htlcs SET hstate=?, payment_key=?, malformed_onion=?, failuremsg=?, localfailmsg=?, we_filled=?, max_commit_num=? WHERE id=?",
         .query = "UPDATE channel_htlcs SET hstate=$1, payment_key=$2, malformed_onion=$3, failuremsg=$4, localfailmsg=$5, we_filled=$6, max_commit_num=$7 WHERE id=$8",
         .placeholders = 8,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_htlcs SET payment_key=NULL, routing_onion=NULL, failuremsg=NULL, shared_secret=NULL, localfailmsg=NULL  WHERE id=?",
         .query = "UPDATE channel_htlcs SET payment_key=NULL, routing_onion=NULL, failuremsg=NULL, shared_secret=NULL, localfailmsg=NULL  WHERE id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "SELECT blockheight, txindex, outnum FROM utxoset WHERE blockheight = ?",
         .query = "SELECT blockheight, txindex, outnum FROM utxoset WHERE blockheight = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table418,
         .num_colnames = ARRAY_SIZE(col_table418),
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE channel_htlcs SET partid = 0;",
         .query = "UPDATE channel_htlcs SET partid = 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO invoice_fallbacks            ( invoice_id, scriptpubkey )     VALUES ( ?, ?);",
         .query = "INSERT INTO invoice_fallbacks            ( invoice_id, scriptpubkey )     VALUES ( $1, $2);",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE payments ( id BIGSERIAL, timestamp INTEGER, status INTEGER, payment_hash BLOB, destination BLOB, msatoshi BIGINT, payment_preimage BLOB, path_secrets BLOB, route_nodes BLOB, route_channels BLOB, failonionreply BLOB, faildestperm INTEGER, failindex INTEGER, failcode INTEGER, failnode BLOB, failchannel TEXT, failupdate BLOB, msatoshi_sent BIGINT, faildetail TEXT, description TEXT, faildirection INTEGER, bolt11 TEXT, total_msat BIGINT, partid BIGINT, groupid BIGINT NOT NULL DEFAULT 0, local_offer_id BLOB DEFAULT NULL REFERENCES offers(offer_id), PRIMARY KEY (id), UNIQUE (payment_hash, partid, groupid))",
         .query = "CREATE TABLE payments ( id BIGSERIAL, timestamp INTEGER, status INTEGER, payment_hash BYTEA, destination BYTEA, msatoshi BIGINT, payment_preimage BYTEA, path_secrets BYTEA, route_nodes BYTEA, route_channels BYTEA, failonionreply BYTEA, faildestperm INTEGER, failindex INTEGER, failcode INTEGER, failnode BYTEA, failchannel TEXT, failupdate BYTEA, msatoshi_sent BIGINT, faildetail TEXT, description TEXT, faildirection INTEGER, bolt11 TEXT, total_msat BIGINT, partid BIGINT, groupid BIGINT NOT NULL DEFAULT 0, local_offer_id BYTEA DEFAULT NULL REFERENCES offers(offer_id), PRIMARY KEY (id), UNIQUE (payment_hash, partid, groupid))",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD closer INTEGER DEFAULT 2;",
         .query = "ALTER TABLE channels ADD closer INTEGER DEFAULT 2;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM shachains WHERE id IN (  SELECT shachain_remote_id   FROM channels   WHERE channels.id=?)",
         .query = "DELETE FROM shachains WHERE id IN (  SELECT shachain_remote_id   FROM channels   WHERE channels.id=$1)",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "SELECT   id, state, last_tx FROM channels",
         .query = "SELECT   id, state, last_tx FROM channels",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table277,
         .num_colnames = ARRAY_SIZE(col_table277),
    },
    {
    },
    {
    },
    {
         .name = "SELECT MAX(id) FROM invoices;",
         .query = "SELECT MAX(id) FROM invoices;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table269,
         .num_colnames = ARRAY_SIZE(col_table269),
    },
    {
         .name = "SELECT data, generation FROM datastore WHERE key = ?",
         .query = "SELECT data, generation FROM datastore WHERE key = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table458,
         .num_colnames = ARRAY_SIZE(col_table458),
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD msatoshi_sent BIGINT;",
         .query = "ALTER TABLE payments ADD msatoshi_sent BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD delayed_payment_basepoint_local BLOB",
         .query = "ALTER TABLE channels ADD delayed_payment_basepoint_local BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT spendheight FROM utxoset WHERE spendheight IS NOT NULL ORDER BY spendheight ASC LIMIT 1",
         .query = "SELECT spendheight FROM utxoset WHERE spendheight IS NOT NULL ORDER BY spendheight ASC LIMIT 1",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table417,
         .num_colnames = ARRAY_SIZE(col_table417),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO transaction_annotations (txid, idx, location, type, channel) VALUES (?, ?, ?, ?, ?) ON CONFLICT(txid,idx) DO NOTHING;",
         .query = "INSERT INTO transaction_annotations (txid, idx, location, type, channel) VALUES ($1, $2, $3, $4, $5) ON CONFLICT(txid,idx) DO NOTHING;",
         .placeholders = 5,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD ignore_fee_limits INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD ignore_fee_limits INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE forwarded_payments ADD resolved_time BIGINT",
         .query = "ALTER TABLE forwarded_payments ADD resolved_time BIGINT",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "DELETE FROM utxoset WHERE blockheight IN (  SELECT DISTINCT(blockheight)  FROM utxoset LEFT OUTER JOIN blocks on (blockheight = blocks.height)   WHERE blocks.hash IS NULL);",
         .query = "DELETE FROM utxoset WHERE blockheight IN (  SELECT DISTINCT(blockheight)  FROM utxoset LEFT OUTER JOIN blocks on (blockheight = blocks.height)   WHERE blocks.hash IS NULL);",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "CREATE TABLE penalty_bases (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE, commitnum BIGINT, txid BLOB, outnum INTEGER, amount BIGINT, PRIMARY KEY (channel_id, commitnum));",
         .query = "CREATE TABLE penalty_bases (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE, commitnum BIGINT, txid BYTEA, outnum INTEGER, amount BIGINT, PRIMARY KEY (channel_id, commitnum));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET scid = ? WHERE short_channel_id = ?",
         .query = "UPDATE channels SET scid = $1 WHERE short_channel_id = $2",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "CREATE INDEX utxoset_spend ON utxoset (spendheight)",
         .query = "CREATE INDEX utxoset_spend ON utxoset (spendheight)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD remote_ann_node_sig BLOB;",
         .query = "ALTER TABLE channels ADD remote_ann_node_sig BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD partid BIGINT;",
         .query = "ALTER TABLE channel_htlcs ADD partid BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM htlc_sigs WHERE channelid=?",
         .query = "DELETE FROM htlc_sigs WHERE channelid=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_blockheights  (channel_id, hstate, blockheight) SELECT id, 14, 0 FROM channels WHERE funder = 1;",
         .query = "INSERT INTO channel_blockheights  (channel_id, hstate, blockheight) SELECT id, 14, 0 FROM channels WHERE funder = 1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT failonionreply, faildestperm, failindex, failcode, failnode, failscid, failupdate, faildetail, faildirection  FROM payments WHERE payment_hash=? AND partid=? AND groupid=?;",
         .query = "SELECT failonionreply, faildestperm, failindex, failcode, failnode, failscid, failupdate, faildetail, faildirection  FROM payments WHERE payment_hash=$1 AND partid=$2 AND groupid=$3;",
         .placeholders = 3,
         .readonly = true,
         .colnames = col_table389,
         .num_colnames = ARRAY_SIZE(col_table389),
    },
    {
         .name = "DELETE FROM peers WHERE id=?",
         .query = "DELETE FROM peers WHERE id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET total_msat = msatoshi;",
         .query = "UPDATE payments SET total_msat = msatoshi;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD paydescription TEXT;",
         .query = "ALTER TABLE payments ADD paydescription TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT id, local_static_remotekey_start, option_anchor_outputs, channel_flags, alias_remote, minimum_depth FROM channels",
         .query = "SELECT id, local_static_remotekey_start, option_anchor_outputs, channel_flags, alias_remote, minimum_depth FROM channels",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table267,
         .num_colnames = ARRAY_SIZE(col_table267),
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD force_sign_first INTEGER DEFAULT 0",
         .query = "ALTER TABLE channel_funding_inflights ADD force_sign_first INTEGER DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET failscid = ? WHERE id = ?",
         .query = "UPDATE payments SET failscid = $1 WHERE id = $2",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_configs SET  dust_limit_satoshis=?,  max_htlc_value_in_flight_msat=?,  channel_reserve_satoshis=?,  htlc_minimum_msat=?,  to_self_delay=?,  max_accepted_htlcs=?,  max_dust_htlc_exposure_msat=? WHERE id=?;",
         .query = "UPDATE channel_configs SET  dust_limit_satoshis=$1,  max_htlc_value_in_flight_msat=$2,  channel_reserve_satoshis=$3,  htlc_minimum_msat=$4,  to_self_delay=$5,  max_accepted_htlcs=$6,  max_dust_htlc_exposure_msat=$7 WHERE id=$8;",
         .placeholders = 8,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE peers (  id BIGSERIAL, node_id BLOB UNIQUE, address TEXT, PRIMARY KEY (id));",
         .query = "CREATE TABLE peers (  id BIGSERIAL, node_id BYTEA UNIQUE, address TEXT, PRIMARY KEY (id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channeltxs (  channel_id, type, transaction_id, input_num, blockheight) VALUES (?, ?, ?, ?, ?);",
         .query = "INSERT INTO channeltxs (  channel_id, type, transaction_id, input_num, blockheight) VALUES ($1, $2, $3, $4, $5);",
         .placeholders = 5,
         .readonly = false,
    },
    {
         .name = "SELECT key, data, generation FROM datastore ORDER BY key;",
         .query = "SELECT key, data, generation FROM datastore ORDER BY key;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table460,
         .num_colnames = ARRAY_SIZE(col_table460),
    },
    {
    },
    {
         .name = "CREATE TABLE utxoset ( txid BLOB, outnum INT, blockheight INT REFERENCES blocks(height) ON DELETE CASCADE, spendheight INT REFERENCES blocks(height) ON DELETE SET NULL, txindex INT, scriptpubkey BLOB, satoshis BIGINT, PRIMARY KEY(txid, outnum));",
         .query = "CREATE TABLE utxoset ( txid BYTEA, outnum INT, blockheight INT REFERENCES blocks(height) ON DELETE CASCADE, spendheight INT REFERENCES blocks(height) ON DELETE SET NULL, txindex INT, scriptpubkey BYTEA, satoshis BIGINT, PRIMARY KEY(txid, outnum));",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "INSERT INTO transactions (  id, blockheight, txindex, rawtx) VALUES (?, ?, ?, ?);",
         .query = "INSERT INTO transactions (  id, blockheight, txindex, rawtx) VALUES ($1, $2, $3, $4);",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE db_upgrades (upgrade_from INTEGER, lightning_version TEXT);",
         .query = "CREATE TABLE db_upgrades (upgrade_from INTEGER, lightning_version TEXT);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT id FROM channels WHERE scid IS NOT NULL AND alias_local IS NULL;",
         .query = "SELECT id FROM channels WHERE scid IS NOT NULL AND alias_local IS NULL;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table282,
         .num_colnames = ARRAY_SIZE(col_table282),
    },
    {
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD lease_chan_max_ppt INTEGER DEFAULT NULL",
         .query = "ALTER TABLE channel_funding_inflights ADD lease_chan_max_ppt INTEGER DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT blockheight, txindex FROM transactions WHERE id=?",
         .query = "SELECT blockheight, txindex FROM transactions WHERE id=$1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table424,
         .num_colnames = ARRAY_SIZE(col_table424),
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE invoices SET expiry_time=9223372036854775807;",
         .query = "UPDATE invoices SET expiry_time=9223372036854775807;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT bolt12, label, status  FROM invoicerequests WHERE invreq_id = ?;",
         .query = "SELECT bolt12, label, status  FROM invoicerequests WHERE invreq_id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table451,
         .num_colnames = ARRAY_SIZE(col_table451),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD description TEXT;",
         .query = "ALTER TABLE payments ADD description TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD payment_basepoint_local BLOB",
         .query = "ALTER TABLE channels ADD payment_basepoint_local BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET alias_local = ? WHERE id = ?;",
         .query = "UPDATE channels SET alias_local = $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
         .name = "SELECT name FROM sqlite_master WHERE type='table';",
         .query = "SELECT name FROM sqlite_master WHERE type='table';",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table477,
         .num_colnames = ARRAY_SIZE(col_table477),
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD htlc_basepoint_local BLOB",
         .query = "ALTER TABLE channels ADD htlc_basepoint_local BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO vars (name, blobval) VALUES ('genesis_hash', ?);",
         .query = "INSERT INTO vars (name, blobval) VALUES ('genesis_hash', $1);",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO tableb (id, field1, field2) VALUES (0, 1, 2);",
         .query = "INSERT INTO tableb (id, field1, field2) VALUES (0, 1, 2);",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE invoices   SET state = ?      , updated_index = ? WHERE id = ?",
         .query = "UPDATE invoices   SET state = $1      , updated_index = $2 WHERE id = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD fail_immediate INTEGER DEFAULT 0",
         .query = "ALTER TABLE channel_htlcs ADD fail_immediate INTEGER DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE invoices ADD pay_index BIGINT;",
         .query = "ALTER TABLE invoices ADD pay_index BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD updated_index BIGINT DEFAULT 0",
         .query = "ALTER TABLE invoices ADD updated_index BIGINT DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT key, data, generation FROM datastore WHERE key >= ? ORDER BY key;",
         .query = "SELECT key, data, generation FROM datastore WHERE key >= $1 ORDER BY key;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table459,
         .num_colnames = ARRAY_SIZE(col_table459),
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD our_funding_satoshi BIGINT DEFAULT 0;",
         .query = "ALTER TABLE channels ADD our_funding_satoshi BIGINT DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM penalty_bases WHERE channel_id = ? AND commitnum = ?",
         .query = "DELETE FROM penalty_bases WHERE channel_id = $1 AND commitnum = $2",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT invreq_id FROM invoicerequests;",
         .query = "SELECT invreq_id FROM invoicerequests;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table452,
         .num_colnames = ARRAY_SIZE(col_table452),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD COLUMN option_anchor_outputs INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD COLUMN option_anchor_outputs INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "UPDATE channels SET STATE = 8 WHERE state > 8;",
         .query = "UPDATE channels SET STATE = 8 WHERE state > 8;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels   SET in_payments_offered = COALESCE(in_payments_offered, 0) + 1     , in_msatoshi_offered = COALESCE(in_msatoshi_offered, 0) + ? WHERE id = ?;",
         .query = "UPDATE channels   SET in_payments_offered = COALESCE(in_payments_offered, 0) + 1     , in_msatoshi_offered = COALESCE(in_msatoshi_offered, 0) + $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "SELECT MAX(groupid) FROM payments WHERE payment_hash = ?",
         .query = "SELECT MAX(groupid) FROM payments WHERE payment_hash = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table382,
         .num_colnames = ARRAY_SIZE(col_table382),
    },
    {
         .name = "SELECT blockheight, txindex, outnum FROM utxoset WHERE spendheight = ?",
         .query = "SELECT blockheight, txindex, outnum FROM utxoset WHERE spendheight = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table416,
         .num_colnames = ARRAY_SIZE(col_table416),
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD COLUMN route_channels BLOB;",
         .query = "ALTER TABLE payments ADD COLUMN route_channels BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT  id, channel_htlc_id, msatoshi, cltv_expiry, hstate, payment_hash, payment_key, routing_onion, failuremsg, malformed_onion, shared_secret, received_time, we_filled, fail_immediate FROM channel_htlcs WHERE direction= ? AND channel_id= ? AND hstate NOT IN (?, ?)",
         .query = "SELECT  id, channel_htlc_id, msatoshi, cltv_expiry, hstate, payment_hash, payment_key, routing_onion, failuremsg, malformed_onion, shared_secret, received_time, we_filled, fail_immediate FROM channel_htlcs WHERE direction= $1 AND channel_id= $2 AND hstate NOT IN ($3, $4)",
         .placeholders = 4,
         .readonly = true,
         .colnames = col_table378,
         .num_colnames = ARRAY_SIZE(col_table378),
    },
    {
         .name = "ALTER TABLE channels ADD htlc_minimum_msat BIGINT DEFAULT 0",
         .query = "ALTER TABLE channels ADD htlc_minimum_msat BIGINT DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "INSERT INTO forwards SELECT in_channel_scid, COALESCE(    (SELECT channel_htlc_id FROM channel_htlcs WHERE id = forwarded_payments.in_htlc_id),    -_ROWID_  ), out_channel_scid, (SELECT channel_htlc_id FROM channel_htlcs WHERE id = forwarded_payments.out_htlc_id), in_msatoshi, out_msatoshi, state, received_time, resolved_time, failcode, forward_style FROM forwarded_payments",
         .query = "INSERT INTO forwards SELECT in_channel_scid, COALESCE(    (SELECT channel_htlc_id FROM channel_htlcs WHERE id = forwarded_payments.in_htlc_id),    -(((ctid::text::point)[0]::bigint << 32) | (ctid::text::point)[1]::bigint)  ), out_channel_scid, (SELECT channel_htlc_id FROM channel_htlcs WHERE id = forwarded_payments.out_htlc_id), in_msatoshi, out_msatoshi, state, received_time, resolved_time, failcode, forward_style FROM forwarded_payments",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD scid BIGINT;",
         .query = "ALTER TABLE channels ADD scid BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET  last_sent_commit=? WHERE id=?",
         .query = "UPDATE channels SET  last_sent_commit=$1 WHERE id=$2",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE tableb (   id REFERENCES tablea(id) ON DELETE CASCADE,  field1 INTEGER,  field2 INTEGER);",
         .query = "CREATE TABLE tableb (   id REFERENCES tablea(id) ON DELETE CASCADE,  field1 INTEGER,  field2 INTEGER);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT   c.id, p.node_id, c.last_tx, c.funding_satoshi, c.fundingkey_remote, c.last_sig FROM channels c  LEFT OUTER JOIN peers p  ON p.id = c.peer_id;",
         .query = "SELECT   c.id, p.node_id, c.last_tx, c.funding_satoshi, c.fundingkey_remote, c.last_sig FROM channels c  LEFT OUTER JOIN peers p  ON p.id = c.peer_id;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table259,
         .num_colnames = ARRAY_SIZE(col_table259),
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE outputs ADD COLUMN channel_id BIGINT;",
         .query = "ALTER TABLE outputs ADD COLUMN channel_id BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM runes;",
         .query = "DELETE FROM runes;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO local_anchors VALUES (?,?,?,?,?,?)",
         .query = "INSERT INTO local_anchors VALUES ($1,$2,$3,$4,$5,$6)",
         .placeholders = 6,
         .readonly = false,
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD last_sent_commit BLOB;",
         .query = "ALTER TABLE channels ADD last_sent_commit BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT type, keyindex, prev_out_tx, prev_out_index, channel_id, peer_id, commitment_point FROM outputs WHERE scriptpubkey IS NULL;",
         .query = "SELECT type, keyindex, prev_out_tx, prev_out_index, channel_id, peer_id, commitment_point FROM outputs WHERE scriptpubkey IS NULL;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table249,
         .num_colnames = ARRAY_SIZE(col_table249),
    },
    {
         .name = "CREATE UNIQUE INDEX invoices_pay_index ON invoices(pay_index);",
         .query = "CREATE UNIQUE INDEX invoices_pay_index ON invoices(pay_index);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE shachain_known (  shachain_id BIGINT REFERENCES shachains(id) ON DELETE CASCADE, pos INTEGER, idx BIGINT, hash BLOB, PRIMARY KEY (shachain_id, pos));",
         .query = "CREATE TABLE shachain_known (  shachain_id BIGINT REFERENCES shachains(id) ON DELETE CASCADE, pos INTEGER, idx BIGINT, hash BYTEA, PRIMARY KEY (shachain_id, pos));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD remote_upfront_shutdown_script BLOB;",
         .query = "ALTER TABLE channels ADD remote_upfront_shutdown_script BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD htlc_maximum_msat BIGINT DEFAULT 2100000000000000",
         .query = "ALTER TABLE channels ADD htlc_maximum_msat BIGINT DEFAULT 2100000000000000",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT id  FROM invoices WHERE pay_index IS NOT NULL   AND pay_index > ? ORDER BY pay_index ASC LIMIT 1;",
         .query = "SELECT id  FROM invoices WHERE pay_index IS NOT NULL   AND pay_index > $1 ORDER BY pay_index ASC LIMIT 1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table301,
         .num_colnames = ARRAY_SIZE(col_table301),
    },
    {
         .name = "INSERT INTO payments (id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11, groupid, local_offer_id)SELECT id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11, 0, local_offer_id FROM temp_payments;",
         .query = "INSERT INTO payments (id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11, groupid, local_offer_id)SELECT id, timestamp, status, payment_hash, destination, msatoshi, payment_preimage, path_secrets, route_nodes, route_channels, failonionreply, faildestperm, failindex, failcode, failnode, failchannel, failupdate, msatoshi_sent, faildetail, description, faildirection, bolt11, 0, local_offer_id FROM temp_payments;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT CAST(COALESCE(SUM(in_msatoshi - out_msatoshi), 0) AS BIGINT) FROM forwards  WHERE in_channel_scid = ? AND in_htlc_id IS NULL AND state = ?;",
         .query = "SELECT CAST(COALESCE(SUM(in_msatoshi - out_msatoshi), 0) AS BIGINT) FROM forwards  WHERE in_channel_scid = $1 AND in_htlc_id IS NULL AND state = $2;",
         .placeholders = 2,
         .readonly = true,
         .colnames = col_table435,
         .num_colnames = ARRAY_SIZE(col_table435),
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE invoices ADD paid_outnum INTEGER DEFAULT NULL",
         .query = "ALTER TABLE invoices ADD paid_outnum INTEGER DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "DELETE FROM channel_htlcs WHERE channel_id=?",
         .query = "DELETE FROM channel_htlcs WHERE channel_id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "UPDATE outputs SET spend_height = ?,  status = ? WHERE prev_out_tx = ? AND prev_out_index = ?",
         .query = "UPDATE outputs SET spend_height = $1,  status = $2 WHERE prev_out_tx = $3 AND prev_out_index = $4",
         .placeholders = 4,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "UPDATE channels   SET in_payments_fulfilled = COALESCE(in_payments_fulfilled, 0) + 1     , in_msatoshi_fulfilled = COALESCE(in_msatoshi_fulfilled, 0) + ? WHERE id = ?;",
         .query = "UPDATE channels   SET in_payments_fulfilled = COALESCE(in_payments_fulfilled, 0) + 1     , in_msatoshi_fulfilled = COALESCE(in_msatoshi_fulfilled, 0) + $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD msatoshi_to_us_min BIGINT;",
         .query = "ALTER TABLE channels ADD msatoshi_to_us_min BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "DELETE FROM peers WHERE id NOT IN (SELECT peer_id FROM channels);",
         .query = "DELETE FROM peers WHERE id NOT IN (SELECT peer_id FROM channels);",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE invoicerequests SET status=? WHERE invreq_id = ?;",
         .query = "UPDATE invoicerequests SET status=$1 WHERE invreq_id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til , csv_lock , is_in_coinbase FROM outputs",
         .query = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til , csv_lock , is_in_coinbase FROM outputs",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table308,
         .num_colnames = ARRAY_SIZE(col_table308),
    },
    {
         .name = "SELECT  p.node_id, full_channel_id, scid, alias_local, alias_remote, funder, closer, channel_flags, next_index_local, next_index_remote, next_htlc_id, funding_tx_id, funding_tx_outnum, funding_satoshi, push_msatoshi, msatoshi_local, msatoshi_to_us_min, msatoshi_to_us_max, last_tx, channel_type, state_change_reason, lease_commit_sig, last_stable_connection FROM channels LEFT JOIN peers p ON p.id = peer_id WHERE state = ?;",
         .query = "SELECT  p.node_id, full_channel_id, scid, alias_local, alias_remote, funder, closer, channel_flags, next_index_local, next_index_remote, next_htlc_id, funding_tx_id, funding_tx_outnum, funding_satoshi, push_msatoshi, msatoshi_local, msatoshi_to_us_min, msatoshi_to_us_max, last_tx, channel_type, state_change_reason, lease_commit_sig, last_stable_connection FROM channels LEFT JOIN peers p ON p.id = peer_id WHERE state = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table337,
         .num_colnames = ARRAY_SIZE(col_table337),
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "DELETE FROM htlc_sigs WHERE channelid = ?",
         .query = "DELETE FROM htlc_sigs WHERE channelid = $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE outputs (  prev_out_tx BLOB, prev_out_index INTEGER, value BIGINT, type INTEGER, status INTEGER, keyindex INTEGER, PRIMARY KEY (prev_out_tx, prev_out_index));",
         .query = "CREATE TABLE outputs (  prev_out_tx BYTEA, prev_out_index INTEGER, value BIGINT, type INTEGER, status INTEGER, keyindex INTEGER, PRIMARY KEY (prev_out_tx, prev_out_index));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD state_change_reason INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD state_change_reason INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE forwards ADD updated_index BIGINT DEFAULT 0",
         .query = "ALTER TABLE forwards ADD updated_index BIGINT DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE updated_index >= ? ORDER BY updated_index LIMIT ?;",
         .query = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE updated_index >= $1 ORDER BY updated_index LIMIT $2;",
         .placeholders = 2,
         .readonly = true,
         .colnames = col_table391,
         .num_colnames = ARRAY_SIZE(col_table391),
    },
    {
         .name = "INSERT INTO vars (name, intval) VALUES (?, ?);",
         .query = "INSERT INTO vars (name, intval) VALUES ($1, $2);",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_htlcs SET localfailmsg=decode('2002', 'hex') WHERE malformed_onion != 0 AND direction = 1;",
         .query = "UPDATE channel_htlcs SET localfailmsg=decode('2002', 'hex') WHERE malformed_onion != 0 AND direction = 1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD COLUMN peer_id BLOB;",
         .query = "ALTER TABLE outputs ADD COLUMN peer_id BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 11, local_feerate_per_kw FROM channels WHERE funder = 1 and local_feerate_per_kw != remote_feerate_per_kw;",
         .query = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 11, local_feerate_per_kw FROM channels WHERE funder = 1 and local_feerate_per_kw != remote_feerate_per_kw;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, reserved_til, csv_lock, is_in_coinbase FROM outputs WHERE channel_id IS NOT NULL AND confirmation_height IS NULL",
         .query = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, reserved_til, csv_lock, is_in_coinbase FROM outputs WHERE channel_id IS NOT NULL AND confirmation_height IS NULL",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table310,
         .num_colnames = ARRAY_SIZE(col_table310),
    },
    {
         .name = "UPDATE channels SET  shachain_remote_id=?,  scid=?,  full_channel_id=?,  state=?,  funder=?,  channel_flags=?,  minimum_depth=?,  next_index_local=?,  next_index_remote=?,  next_htlc_id=?,  funding_tx_id=?,  funding_tx_outnum=?,  funding_satoshi=?,  our_funding_satoshi=?,  funding_locked_remote=?,  push_msatoshi=?,  msatoshi_local=?,  shutdown_scriptpubkey_remote=?,  shutdown_keyidx_local=?,  channel_config_local=?,  last_tx=?, last_sig=?,  last_was_revoke=?,  min_possible_feerate=?,  max_possible_feerate=?,  msatoshi_to_us_min=?,  msatoshi_to_us_max=?,  feerate_base=?,  feerate_ppm=?,  remote_upfront_shutdown_script=?,  local_static_remotekey_start=?,  remote_static_remotekey_start=?,  channel_type=?,  shutdown_scriptpubkey_local=?,  closer=?,  state_change_reason=?,  shutdown_wrong_txid=?,  shutdown_wrong_outnum=?,  lease_expiry=?,  lease_commit_sig=?,  lease_chan_max_msat=?,  lease_chan_max_ppt=?,  htlc_minimum_msat=?,  htlc_maximum_msat=?,  alias_local=?,  alias_remote=?,  ignore_fee_limits=?,  remote_feerate_base=?,  remote_feerate_ppm=?,  remote_cltv_expiry_delta=?,  remote_htlc_minimum_msat=?,  remote_htlc_maximum_msat=?,  last_stable_connection=?,  require_confirm_inputs_remote=?,  close_attempt_height=? WHERE id=?",
         .query = "UPDATE channels SET  shachain_remote_id=$1,  scid=$2,  full_channel_id=$3,  state=$4,  funder=$5,  channel_flags=$6,  minimum_depth=$7,  next_index_local=$8,  next_index_remote=$9,  next_htlc_id=$10,  funding_tx_id=$11,  funding_tx_outnum=$12,  funding_satoshi=$13,  our_funding_satoshi=$14,  funding_locked_remote=$15,  push_msatoshi=$16,  msatoshi_local=$17,  shutdown_scriptpubkey_remote=$18,  shutdown_keyidx_local=$19,  channel_config_local=$20,  last_tx=$21, last_sig=$22,  last_was_revoke=$23,  min_possible_feerate=$24,  max_possible_feerate=$25,  msatoshi_to_us_min=$26,  msatoshi_to_us_max=$27,  feerate_base=$28,  feerate_ppm=$29,  remote_upfront_shutdown_script=$30,  local_static_remotekey_start=$31,  remote_static_remotekey_start=$32,  channel_type=$33,  shutdown_scriptpubkey_local=$34,  closer=$35,  state_change_reason=$36,  shutdown_wrong_txid=$37,  shutdown_wrong_outnum=$38,  lease_expiry=$39,  lease_commit_sig=$40,  lease_chan_max_msat=$41,  lease_chan_max_ppt=$42,  htlc_minimum_msat=$43,  htlc_maximum_msat=$44,  alias_local=$45,  alias_remote=$46,  ignore_fee_limits=$47,  remote_feerate_base=$48,  remote_feerate_ppm=$49,  remote_cltv_expiry_delta=$50,  remote_htlc_minimum_msat=$51,  remote_htlc_maximum_msat=$52,  last_stable_connection=$53,  require_confirm_inputs_remote=$54,  close_attempt_height=$55 WHERE id=$56",
         .placeholders = 56,
         .readonly = false,
    },
    {
         .name = "SELECT id FROM transactions WHERE blockheight=?",
         .query = "SELECT id FROM transactions WHERE blockheight=$1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table425,
         .num_colnames = ARRAY_SIZE(col_table425),
    },
    {
         .name = "CREATE TABLE addresses (  keyidx BIGINT,  addrtype INTEGER)",
         .query = "CREATE TABLE addresses (  keyidx BIGINT,  addrtype INTEGER)",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT version FROM version LIMIT 1",
         .query = "SELECT version FROM version LIMIT 1",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table0,
         .num_colnames = ARRAY_SIZE(col_table0),
    },
    {
         .name = "ALTER TABLE outputs ADD reserved_til INTEGER DEFAULT NULL;",
         .query = "ALTER TABLE outputs ADD reserved_til INTEGER DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD local_static_remotekey_start BIGINT DEFAULT 0",
         .query = "ALTER TABLE channels ADD local_static_remotekey_start BIGINT DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD COLUMN lease_satoshi BIGINT;",
         .query = "ALTER TABLE channel_funding_inflights ADD COLUMN lease_satoshi BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT  t.id, t.rawtx, t.blockheight, t.txindex FROM  transactions t LEFT JOIN  channels c ON (t.channel_id = c.id) ORDER BY t.blockheight, t.txindex ASC",
         .query = "SELECT  t.id, t.rawtx, t.blockheight, t.txindex FROM  transactions t LEFT JOIN  channels c ON (t.channel_id = c.id) ORDER BY t.blockheight, t.txindex ASC",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table438,
         .num_colnames = ARRAY_SIZE(col_table438),
    },
    {
         .name = "ALTER TABLE invoices ADD COLUMN msatoshi_received BIGINT;",
         .query = "ALTER TABLE invoices ADD COLUMN msatoshi_received BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO datastore VALUES (?, ?, 0);",
         .query = "INSERT INTO datastore VALUES ($1, $2, 0);",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD updated_index BIGINT DEFAULT 0",
         .query = "ALTER TABLE payments ADD updated_index BIGINT DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM channel_funding_inflights  WHERE channel_id=? AND last_tx IS NULL",
         .query = "DELETE FROM channel_funding_inflights  WHERE channel_id=$1 AND last_tx IS NULL",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "SELECT (COALESCE(MAX(id), -1) + 1) FROM runes",
         .query = "SELECT (COALESCE(MAX(id), -1) + 1) FROM runes",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table463,
         .num_colnames = ARRAY_SIZE(col_table463),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE payments RENAME TO temp_payments;",
         .query = "ALTER TABLE payments RENAME TO temp_payments;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO shachains (min_index, num_valid) VALUES (?, 0);",
         .query = "INSERT INTO shachains (min_index, num_valid) VALUES ($1, 0);",
         .placeholders = 1,
         .readonly = false,
    },
    {
         .name = "SELECT channel_id, direction, cltv_expiry, channel_htlc_id, payment_hash FROM channel_htlcs WHERE channel_id = ? AND min_commit_num <= ? AND ((max_commit_num IS NULL) OR max_commit_num >= ?);",
         .query = "SELECT channel_id, direction, cltv_expiry, channel_htlc_id, payment_hash FROM channel_htlcs WHERE channel_id = $1 AND min_commit_num <= $2 AND ((max_commit_num IS NULL) OR max_commit_num >= $3);",
         .placeholders = 3,
         .readonly = true,
         .colnames = col_table380,
         .num_colnames = ARRAY_SIZE(col_table380),
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD in_msatoshi_offered BIGINT DEFAULT 0;",
         .query = "ALTER TABLE channels ADD in_msatoshi_offered BIGINT DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE  status = ? AND  id >= ? ORDER BY id LIMIT ?;",
         .query = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE  status = $1 AND  id >= $2 ORDER BY id LIMIT $3;",
         .placeholders = 3,
         .readonly = true,
         .colnames = col_table396,
         .num_colnames = ARRAY_SIZE(col_table396),
    },
    {
         .name = "UPDATE payments   SET path_secrets = NULL     , route_nodes = NULL     , route_channels = NULL WHERE payment_hash = ? AND partid = ? AND groupid=?;",
         .query = "UPDATE payments   SET path_secrets = NULL     , route_nodes = NULL     , route_channels = NULL WHERE payment_hash = $1 AND partid = $2 AND groupid=$3;",
         .placeholders = 3,
         .readonly = false,
    },
    {
    },
    {
         .name = "SELECT hstate, blockheight FROM channel_blockheights WHERE channel_id = ?",
         .query = "SELECT hstate, blockheight FROM channel_blockheights WHERE channel_id = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table329,
         .num_colnames = ARRAY_SIZE(col_table329),
    },
    {
         .name = "ALTER TABLE channels ADD remote_static_remotekey_start BIGINT DEFAULT 0",
         .query = "ALTER TABLE channels ADD remote_static_remotekey_start BIGINT DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD remote_feerate_base INTEGER DEFAULT NULL;",
         .query = "ALTER TABLE channels ADD remote_feerate_base INTEGER DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT * FROM channels WHERE peer_id = ?;",
         .query = "SELECT * FROM channels WHERE peer_id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table371,
         .num_colnames = ARRAY_SIZE(col_table371),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "DROP INDEX forwarded_payments_state;",
         .query = "DROP INDEX forwarded_payments_state;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD min_possible_feerate INTEGER;",
         .query = "ALTER TABLE channels ADD min_possible_feerate INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channel_funding_inflights (  channel_id BIGSERIAL REFERENCES channels(id) ON DELETE CASCADE, funding_tx_id BLOB, funding_tx_outnum INTEGER, funding_feerate INTEGER, funding_satoshi BIGINT, our_funding_satoshi BIGINT, funding_psbt BLOB, last_tx BLOB, last_sig BLOB, funding_tx_remote_sigs_received INTEGER, PRIMARY KEY (channel_id, funding_tx_id));",
         .query = "CREATE TABLE channel_funding_inflights (  channel_id BIGSERIAL REFERENCES channels(id) ON DELETE CASCADE, funding_tx_id BYTEA, funding_tx_outnum INTEGER, funding_feerate INTEGER, funding_satoshi BIGINT, our_funding_satoshi BIGINT, funding_psbt BYTEA, last_tx BYTEA, last_sig BYTEA, funding_tx_remote_sigs_received INTEGER, PRIMARY KEY (channel_id, funding_tx_id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_funding_inflights ADD lease_expiry INTEGER DEFAULT 0",
         .query = "ALTER TABLE channel_funding_inflights ADD lease_expiry INTEGER DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT rune, last_used_nsec FROM runes WHERE id = ?",
         .query = "SELECT rune, last_used_nsec FROM runes WHERE id = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table465,
         .num_colnames = ARRAY_SIZE(col_table465),
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "CREATE TABLE shachains (  id BIGSERIAL, min_index BIGINT, num_valid BIGINT, PRIMARY KEY (id));",
         .query = "CREATE TABLE shachains (  id BIGSERIAL, min_index BIGINT, num_valid BIGINT, PRIMARY KEY (id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD paid_timestamp BIGINT;",
         .query = "ALTER TABLE invoices ADD paid_timestamp BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET msatoshi_sent = msatoshi;",
         .query = "UPDATE payments SET msatoshi_sent = msatoshi;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE vars SET blobval = CAST(val AS BLOB) WHERE name = 'genesis_hash'",
         .query = "UPDATE vars SET blobval = CAST(val AS BYTEA) WHERE name = 'genesis_hash'",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, reserved_til, csv_lock, is_in_coinbase FROM outputs WHERE prev_out_tx = ? AND prev_out_index = ?",
         .query = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, reserved_til, csv_lock, is_in_coinbase FROM outputs WHERE prev_out_tx = $1 AND prev_out_index = $2",
         .placeholders = 2,
         .readonly = true,
         .colnames = col_table311,
         .num_colnames = ARRAY_SIZE(col_table311),
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD failcode INTEGER;",
         .query = "ALTER TABLE payments ADD failcode INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE payments SET partid = 0;",
         .query = "UPDATE payments SET partid = 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT min_index, num_valid FROM shachains WHERE id=?",
         .query = "SELECT min_index, num_valid FROM shachains WHERE id=$1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table322,
         .num_colnames = ARRAY_SIZE(col_table322),
    },
    {
         .name = "INSERT INTO outputs (  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, csv_lock) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO outputs (  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey, csv_lock) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, $13, $14);",
         .placeholders = 14,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD last_stable_connection BIGINT DEFAULT 0;",
         .query = "ALTER TABLE channels ADD last_stable_connection BIGINT DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE datastore SET data=?, generation=generation+1 WHERE key=?;",
         .query = "UPDATE datastore SET data=$1, generation=generation+1 WHERE key=$2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
         .name = "CREATE TABLE payments (  id BIGSERIAL,  timestamp INTEGER,  status INTEGER,  payment_hash BLOB,  destination BLOB,  msatoshi BIGINT,  PRIMARY KEY (id),  UNIQUE (payment_hash));",
         .query = "CREATE TABLE payments (  id BIGSERIAL,  timestamp INTEGER,  status INTEGER,  payment_hash BYTEA,  destination BYTEA,  msatoshi BIGINT,  PRIMARY KEY (id),  UNIQUE (payment_hash));",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "CREATE INDEX output_height_idx ON outputs (confirmation_height, spend_height);",
         .query = "CREATE INDEX output_height_idx ON outputs (confirmation_height, spend_height);",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO channel_feerates  VALUES(?, ?, ?)",
         .query = "INSERT INTO channel_feerates  VALUES($1, $2, $3)",
         .placeholders = 3,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "CREATE INDEX invoice_update_idx ON invoices (updated_index)",
         .query = "CREATE INDEX invoice_update_idx ON invoices (updated_index)",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channel_funding_inflights SET last_tx = ? WHERE channel_id = ?   AND funding_tx_id = ?;",
         .query = "UPDATE channel_funding_inflights SET last_tx = $1 WHERE channel_id = $2   AND funding_tx_id = $3;",
         .placeholders = 3,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "SELECT invoice_id  FROM invoice_fallbacks WHERE scriptpubkey = ?;",
         .query = "SELECT invoice_id  FROM invoice_fallbacks WHERE scriptpubkey = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table292,
         .num_colnames = ARRAY_SIZE(col_table292),
    },
    {
         .name = "ALTER TABLE channels ADD channel_type BLOB DEFAULT NULL;",
         .query = "ALTER TABLE channels ADD channel_type BYTEA DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET short_channel_id = NULL;",
         .query = "UPDATE channels SET short_channel_id = NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "INSERT INTO channel_state_changes (  channel_id, timestamp, old_state, new_state, cause, message) VALUES (?, ?, ?, ?, ?, ?);",
         .query = "INSERT INTO channel_state_changes (  channel_id, timestamp, old_state, new_state, cause, message) VALUES ($1, $2, $3, $4, $5, $6);",
         .placeholders = 6,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD COLUMN path_secrets BLOB;",
         .query = "ALTER TABLE payments ADD COLUMN path_secrets BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD out_msatoshi_fulfilled BIGINT DEFAULT 0;",
         .query = "ALTER TABLE channels ADD out_msatoshi_fulfilled BIGINT DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE channel_configs (  id BIGSERIAL,  dust_limit_satoshis BIGINT,  max_htlc_value_in_flight_msat BIGINT,  channel_reserve_satoshis BIGINT,  htlc_minimum_msat BIGINT,  to_self_delay INTEGER,  max_accepted_htlcs INTEGER,  PRIMARY KEY (id));",
         .query = "CREATE TABLE channel_configs (  id BIGSERIAL,  dust_limit_satoshis BIGINT,  max_htlc_value_in_flight_msat BIGINT,  channel_reserve_satoshis BIGINT,  htlc_minimum_msat BIGINT,  to_self_delay INTEGER,  max_accepted_htlcs INTEGER,  PRIMARY KEY (id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD failindex INTEGER;",
         .query = "ALTER TABLE payments ADD failindex INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE shachain_known SET idx=?, hash=? WHERE shachain_id=? AND pos=?",
         .query = "UPDATE shachain_known SET idx=$1, hash=$2 WHERE shachain_id=$3 AND pos=$4",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "SELECT t.blockheight, t.rawtx FROM channeltxs c JOIN transactions t ON t.id = c.transaction_id WHERE c.channel_id = ? AND t.blockheight IS NOT NULL AND c.type = ? ORDER BY c.id ASC;",
         .query = "SELECT t.blockheight, t.rawtx FROM channeltxs c JOIN transactions t ON t.id = c.transaction_id WHERE c.channel_id = $1 AND t.blockheight IS NOT NULL AND c.type = $2 ORDER BY c.id ASC;",
         .placeholders = 2,
         .readonly = true,
         .colnames = col_table427,
         .num_colnames = ARRAY_SIZE(col_table427),
    },
    {
         .name = "UPDATE invoices SET pay_index=id WHERE state=1;",
         .query = "UPDATE invoices SET pay_index=id WHERE state=1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD faildestperm INTEGER;",
         .query = "ALTER TABLE payments ADD faildestperm INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT status  FROM invoicerequests WHERE invreq_id = ?;",
         .query = "SELECT status  FROM invoicerequests WHERE invreq_id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table454,
         .num_colnames = ARRAY_SIZE(col_table454),
    },
    {
         .name = "SELECT dust_limit_satoshis, max_htlc_value_in_flight_msat, channel_reserve_satoshis, htlc_minimum_msat, to_self_delay, max_accepted_htlcs, max_dust_htlc_exposure_msat FROM channel_configs WHERE id= ? ;",
         .query = "SELECT dust_limit_satoshis, max_htlc_value_in_flight_msat, channel_reserve_satoshis, htlc_minimum_msat, to_self_delay, max_accepted_htlcs, max_dust_htlc_exposure_msat FROM channel_configs WHERE id= $1 ;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table335,
         .num_colnames = ARRAY_SIZE(col_table335),
    },
    {
    },
    {
         .name = "INSERT INTO version VALUES (1)",
         .query = "INSERT INTO version VALUES (1)",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD remote_feerate_ppm INTEGER DEFAULT NULL;",
         .query = "ALTER TABLE channels ADD remote_feerate_ppm INTEGER DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "SELECT state FROM invoices WHERE id = ?;",
         .query = "SELECT state FROM invoices WHERE id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table298,
         .num_colnames = ARRAY_SIZE(col_table298),
    },
    {
    },
    {
         .name = "INSERT INTO shachain_known (shachain_id, pos, idx, hash) VALUES (?, ?, ?, ?);",
         .query = "INSERT INTO shachain_known (shachain_id, pos, idx, hash) VALUES ($1, $2, $3, $4);",
         .placeholders = 4,
         .readonly = false,
    },
    {
         .name = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE  payment_hash = ? ORDER BY id;",
         .query = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE  payment_hash = $1 ORDER BY id;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table393,
         .num_colnames = ARRAY_SIZE(col_table393),
    },
    {
    },
    {
         .name = "DELETE FROM invoices WHERE id=?;",
         .query = "DELETE FROM invoices WHERE id=$1;",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
         .name = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til, csv_lock, is_in_coinbase FROM outputs WHERE status = ? OR (status = ? AND reserved_til <= ?)ORDER BY RANDOM();",
         .query = "SELECT  prev_out_tx, prev_out_index, value, type, status, keyindex, channel_id, peer_id, commitment_point, option_anchor_outputs, confirmation_height, spend_height, scriptpubkey , reserved_til, csv_lock, is_in_coinbase FROM outputs WHERE status = $1 OR (status = $2 AND reserved_til <= $3)ORDER BY RANDOM();",
         .placeholders = 3,
         .readonly = true,
         .colnames = col_table313,
         .num_colnames = ARRAY_SIZE(col_table313),
    },
    {
         .name = "UPDATE offers SET status=? WHERE offer_id = ?;",
         .query = "UPDATE offers SET status=$1 WHERE offer_id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD COLUMN spend_height INTEGER REFERENCES blocks(height) ON DELETE SET NULL;",
         .query = "ALTER TABLE outputs ADD COLUMN spend_height INTEGER REFERENCES blocks(height) ON DELETE SET NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD lease_expiry INTEGER DEFAULT 0",
         .query = "ALTER TABLE channels ADD lease_expiry INTEGER DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE transactions ADD type BIGINT;",
         .query = "ALTER TABLE transactions ADD type BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE offers (  offer_id BLOB, bolt12 TEXT, label TEXT, status INTEGER, PRIMARY KEY (offer_id));",
         .query = "CREATE TABLE offers (  offer_id BYTEA, bolt12 TEXT, label TEXT, status INTEGER, PRIMARY KEY (offer_id));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE payments SET bolt11 = ? WHERE id = ?;",
         .query = "UPDATE payments SET bolt11 = $1 WHERE id = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT MAX(id) FROM payments;",
         .query = "SELECT MAX(id) FROM payments;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table272,
         .num_colnames = ARRAY_SIZE(col_table272),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channel_configs ADD max_dust_htlc_exposure_msat BIGINT DEFAULT 50000000",
         .query = "ALTER TABLE channel_configs ADD max_dust_htlc_exposure_msat BIGINT DEFAULT 50000000",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "DROP TABLE temp_payments;",
         .query = "DROP TABLE temp_payments;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD scriptpubkey BLOB;",
         .query = "ALTER TABLE outputs ADD scriptpubkey BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT h.channel_htlc_id, h.cltv_expiry, h.direction, h.msatoshi, h.payment_hash, h.hstate FROM channel_htlcs h WHERE channel_id = ? ORDER BY id ASC",
         .query = "SELECT h.channel_htlc_id, h.cltv_expiry, h.direction, h.msatoshi, h.payment_hash, h.hstate FROM channel_htlcs h WHERE channel_id = $1 ORDER BY id ASC",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table461,
         .num_colnames = ARRAY_SIZE(col_table461),
    },
    {
    },
    {
         .name = "ALTER TABLE vars ADD COLUMN blobval BLOB",
         .query = "ALTER TABLE vars ADD COLUMN blobval BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "UPDATE payments   SET failonionreply=?     , faildestperm=?     , failindex=?     , failcode=?     , failnode=?     , failscid=?     , faildirection=?     , failupdate=?     , faildetail=? WHERE payment_hash=? AND partid=?;",
         .query = "UPDATE payments   SET failonionreply=$1     , faildestperm=$2     , failindex=$3     , failcode=$4     , failnode=$5     , failscid=$6     , faildirection=$7     , failupdate=$8     , faildetail=$9 WHERE payment_hash=$10 AND partid=$11;",
         .placeholders = 11,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 1, remote_feerate_per_kw FROM channels WHERE funder = 0 and local_feerate_per_kw != remote_feerate_per_kw;",
         .query = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 1, remote_feerate_per_kw FROM channels WHERE funder = 0 and local_feerate_per_kw != remote_feerate_per_kw;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE forwarded_payments SET received_time=0 WHERE received_time IS NULL;",
         .query = "UPDATE forwarded_payments SET received_time=0 WHERE received_time IS NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD fees_msat BIGINT DEFAULT 0",
         .query = "ALTER TABLE channel_htlcs ADD fees_msat BIGINT DEFAULT 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE vars SET name = 'last_invoices_created_index' WHERE name = 'last_invoice_created_index'",
         .query = "UPDATE vars SET name = 'last_invoices_created_index' WHERE name = 'last_invoice_created_index'",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD COLUMN payment_preimage BLOB;",
         .query = "ALTER TABLE payments ADD COLUMN payment_preimage BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD COLUMN confirmation_height INTEGER REFERENCES blocks(height) ON DELETE SET NULL;",
         .query = "ALTER TABLE outputs ADD COLUMN confirmation_height INTEGER REFERENCES blocks(height) ON DELETE SET NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT signature FROM htlc_sigs WHERE channelid = ? AND inflight_tx_id is NULL",
         .query = "SELECT signature FROM htlc_sigs WHERE channelid = $1 AND inflight_tx_id is NULL",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table325,
         .num_colnames = ARRAY_SIZE(col_table325),
    },
    {
         .name = "DELETE FROM datastore WHERE key = ?",
         .query = "DELETE FROM datastore WHERE key = $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT id FROM peers WHERE node_id = ?",
         .query = "SELECT id FROM peers WHERE node_id = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table358,
         .num_colnames = ARRAY_SIZE(col_table358),
    },
    {
         .name = "UPDATE channels SET feerate_base = ?, feerate_ppm = ?;",
         .query = "UPDATE channels SET feerate_base = $1, feerate_ppm = $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "DELETE FROM runes_blacklist",
         .query = "DELETE FROM runes_blacklist",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD shutdown_wrong_outnum INTEGER DEFAULT NULL",
         .query = "ALTER TABLE channels ADD shutdown_wrong_outnum INTEGER DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET  fundingkey_remote=?,  revocation_basepoint_remote=?,  payment_basepoint_remote=?,  htlc_basepoint_remote=?,  delayed_payment_basepoint_remote=?,  per_commit_remote=?,  old_per_commit_remote=?,  channel_config_remote=?,  future_per_commitment_point=? WHERE id=?",
         .query = "UPDATE channels SET  fundingkey_remote=$1,  revocation_basepoint_remote=$2,  payment_basepoint_remote=$3,  htlc_basepoint_remote=$4,  delayed_payment_basepoint_remote=$5,  per_commit_remote=$6,  old_per_commit_remote=$7,  channel_config_remote=$8,  future_per_commitment_point=$9 WHERE id=$10",
         .placeholders = 10,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD lease_chan_max_ppt INTEGER DEFAULT NULL",
         .query = "ALTER TABLE channels ADD lease_chan_max_ppt INTEGER DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD failscid BIGINT;",
         .query = "ALTER TABLE payments ADD failscid BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT bolt12, label, status  FROM offers WHERE offer_id = ?;",
         .query = "SELECT bolt12, label, status  FROM offers WHERE offer_id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table444,
         .num_colnames = ARRAY_SIZE(col_table444),
    },
    {
         .name = "SELECT  state, in_msatoshi, out_msatoshi, in_channel_scid, out_channel_scid, in_htlc_id, out_htlc_id, received_time, resolved_time, failcode , forward_style , rowid , updated_index FROM forwards  WHERE  (1 = ? OR state = ?) AND  rowid >= ? ORDER BY rowid LIMIT ?;",
         .query = "SELECT  state, in_msatoshi, out_msatoshi, in_channel_scid, out_channel_scid, in_htlc_id, out_htlc_id, received_time, resolved_time, failcode , forward_style , rowid , updated_index FROM forwards  WHERE  (1 = $1 OR state = $2) AND  rowid >= $3 ORDER BY rowid LIMIT $4;",
         .placeholders = 4,
         .readonly = true,
         .colnames = col_table433,
         .num_colnames = ARRAY_SIZE(col_table433),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "CREATE INDEX forwarded_payments_out_htlc_id ON forwarded_payments (out_htlc_id);",
         .query = "CREATE INDEX forwarded_payments_out_htlc_id ON forwarded_payments (out_htlc_id);",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "UPDATE invoices SET state=? WHERE state=? AND local_offer_id = ?;",
         .query = "UPDATE invoices SET state=$1 WHERE state=$2 AND local_offer_id = $3;",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "DELETE FROM blocks WHERE height > (SELECT MIN(first_blocknum) FROM channels);",
         .query = "DELETE FROM blocks WHERE height > (SELECT MIN(first_blocknum) FROM channels);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT short_channel_id FROM channels",
         .query = "SELECT short_channel_id FROM channels",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table261,
         .num_colnames = ARRAY_SIZE(col_table261),
    },
    {
         .name = "UPDATE forwards SET  updated_index=?, in_msatoshi=?, out_msatoshi=?, state=?, resolved_time=?, failcode=?, forward_style=? WHERE in_htlc_id=? AND in_channel_scid=?",
         .query = "UPDATE forwards SET  updated_index=$1, in_msatoshi=$2, out_msatoshi=$3, state=$4, resolved_time=$5, failcode=$6, forward_style=$7 WHERE in_htlc_id=$8 AND in_channel_scid=$9",
         .placeholders = 9,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE channel_funding_inflights SET  funding_psbt=?, funding_tx_remote_sigs_received=?, last_tx=?, last_sig=? WHERE  channel_id=? AND funding_tx_id=? AND funding_tx_outnum=?",
         .query = "UPDATE channel_funding_inflights SET  funding_psbt=$1, funding_tx_remote_sigs_received=$2, last_tx=$3, last_sig=$4 WHERE  channel_id=$5 AND funding_tx_id=$6 AND funding_tx_outnum=$7",
         .placeholders = 7,
         .readonly = false,
    },
    {
    },
    {
         .name = "INSERT INTO vars (name, intval) VALUES ('coin_moves_count', 0);",
         .query = "INSERT INTO vars (name, intval) VALUES ('coin_moves_count', 0);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD first_blocknum BIGINT;",
         .query = "ALTER TABLE channels ADD first_blocknum BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD full_channel_id BLOB DEFAULT NULL;",
         .query = "ALTER TABLE channels ADD full_channel_id BYTEA DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE invoice_fallbacks (  scriptpubkey BLOB,  invoice_id BIGINT REFERENCES invoices(id) ON DELETE CASCADE,  PRIMARY KEY (scriptpubkey));",
         .query = "CREATE TABLE invoice_fallbacks (  scriptpubkey BYTEA,  invoice_id BIGINT REFERENCES invoices(id) ON DELETE CASCADE,  PRIMARY KEY (scriptpubkey));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD future_per_commitment_point BLOB;",
         .query = "ALTER TABLE channels ADD future_per_commitment_point BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT id  FROM invoices WHERE state = ?   AND expiry_time <= ?",
         .query = "SELECT id  FROM invoices WHERE state = $1   AND expiry_time <= $2",
         .placeholders = 2,
         .readonly = true,
         .colnames = col_table285,
         .num_colnames = ARRAY_SIZE(col_table285),
    },
    {
         .name = "DELETE FROM payments WHERE payment_hash = ?     AND status = ?",
         .query = "DELETE FROM payments WHERE payment_hash = $1     AND status = $2",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "DELETE FROM blocks WHERE hash = ?",
         .query = "DELETE FROM blocks WHERE hash = $1",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "CREATE TABLE payments (  id BIGSERIAL,  timestamp INTEGER,  status INTEGER,  payment_hash BLOB,  direction INTEGER,  destination BLOB,  msatoshi BIGINT,  PRIMARY KEY (id),  UNIQUE (payment_hash));",
         .query = "CREATE TABLE payments (  id BIGSERIAL,  timestamp INTEGER,  status INTEGER,  payment_hash BYTEA,  direction INTEGER,  destination BYTEA,  msatoshi BIGINT,  PRIMARY KEY (id),  UNIQUE (payment_hash));",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE channel_htlcs SET max_commit_num = (SELECT GREATEST(next_index_local, next_index_remote)  FROM channels WHERE id=channel_id) WHERE (hstate=9 OR hstate=19);",
         .query = "UPDATE channel_htlcs SET max_commit_num = (SELECT GREATEST(next_index_local, next_index_remote)  FROM channels WHERE id=channel_id) WHERE (hstate=9 OR hstate=19);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET min_possible_feerate=0, max_possible_feerate=250000;",
         .query = "UPDATE channels SET min_possible_feerate=0, max_possible_feerate=250000;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO tablea (id, field1) VALUES (0, 1);",
         .query = "INSERT INTO tablea (id, field1) VALUES (0, 1);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT intval FROM vars WHERE name= ? LIMIT 1",
         .query = "SELECT intval FROM vars WHERE name= $1 LIMIT 1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table4,
         .num_colnames = ARRAY_SIZE(col_table4),
    },
    {
         .name = "CREATE TABLE channel_state_changes (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  timestamp BIGINT,  old_state INTEGER,  new_state INTEGER,  cause INTEGER,  message TEXT);",
         .query = "CREATE TABLE channel_state_changes (  channel_id BIGINT REFERENCES channels(id) ON DELETE CASCADE,  timestamp BIGINT,  old_state INTEGER,  new_state INTEGER,  cause INTEGER,  message TEXT);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM channel_blockheights WHERE channel_id=?",
         .query = "DELETE FROM channel_blockheights WHERE channel_id=$1",
         .placeholders = 1,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD faildetail TEXT;",
         .query = "ALTER TABLE payments ADD faildetail TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE payments ADD bolt11 TEXT;",
         .query = "ALTER TABLE payments ADD bolt11 TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE outputs ADD option_anchor_outputs INTEGER DEFAULT 0;",
         .query = "ALTER TABLE outputs ADD option_anchor_outputs INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "CREATE INDEX forwards_created_idx ON forwards (rowid)",
         .query = "CREATE INDEX forwards_created_idx ON forwards (rowid)",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT 1  FROM offers WHERE offer_id = ?;",
         .query = "SELECT 1  FROM offers WHERE offer_id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table442,
         .num_colnames = ARRAY_SIZE(col_table442),
    },
    {
         .name = "ALTER TABLE channels ADD alias_local BIGINT DEFAULT NULL",
         .query = "ALTER TABLE channels ADD alias_local BIGINT DEFAULT NULL",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "UPDATE channels   SET msatoshi_to_us_min = msatoshi_local     , msatoshi_to_us_max = msatoshi_local     ;",
         .query = "UPDATE channels   SET msatoshi_to_us_min = msatoshi_local     , msatoshi_to_us_max = msatoshi_local     ;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE vars SET intval=? WHERE name=?;",
         .query = "UPDATE vars SET intval=$1 WHERE name=$2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET  revocation_basepoint_local = ?, payment_basepoint_local = ?, htlc_basepoint_local = ?, delayed_payment_basepoint_local = ?, funding_pubkey_local = ? WHERE id = ?;",
         .query = "UPDATE channels SET  revocation_basepoint_local = $1, payment_basepoint_local = $2, htlc_basepoint_local = $3, delayed_payment_basepoint_local = $4, funding_pubkey_local = $5 WHERE id = $6;",
         .placeholders = 6,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE htlc_sigs ADD inflight_tx_id BLOB",
         .query = "ALTER TABLE htlc_sigs ADD inflight_tx_id BYTEA",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "UPDATE channels SET first_blocknum=1 WHERE short_channel_id IS NOT NULL;",
         .query = "UPDATE channels SET first_blocknum=1 WHERE short_channel_id IS NOT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD in_payments_offered INTEGER DEFAULT 0;",
         .query = "ALTER TABLE channels ADD in_payments_offered INTEGER DEFAULT 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 14, remote_feerate_per_kw FROM channels WHERE funder = 1;",
         .query = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 14, remote_feerate_per_kw FROM channels WHERE funder = 1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET channel_type = ? WHERE id = ?",
         .query = "UPDATE channels SET channel_type = $1 WHERE id = $2",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "SELECT * FROM blocks WHERE height >= ?;",
         .query = "SELECT * FROM blocks WHERE height >= $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table409,
         .num_colnames = ARRAY_SIZE(col_table409),
    },
    {
         .name = "ALTER TABLE channels ADD max_possible_feerate INTEGER;",
         .query = "ALTER TABLE channels ADD max_possible_feerate INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO peers (node_id, address, feature_bits) VALUES (?, ?, ?);",
         .query = "INSERT INTO peers (node_id, address, feature_bits) VALUES ($1, $2, $3);",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE forwarded_payments ADD failcode INTEGER;",
         .query = "ALTER TABLE forwarded_payments ADD failcode INTEGER;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO payments SELECT id, timestamp, status, payment_hash, destination, msatoshi FROM temp_payments WHERE direction=1;",
         .query = "INSERT INTO payments SELECT id, timestamp, status, payment_hash, destination, msatoshi FROM temp_payments WHERE direction=1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE runes_blacklist (start_index BIGINT, end_index BIGINT);",
         .query = "CREATE TABLE runes_blacklist (start_index BIGINT, end_index BIGINT);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM vars WHERE name = 'last_invoice_created_index'",
         .query = "DELETE FROM vars WHERE name = 'last_invoice_created_index'",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT  state, in_msatoshi, out_msatoshi, in_channel_scid, out_channel_scid, in_htlc_id, out_htlc_id, received_time, resolved_time, failcode , forward_style , rowid , updated_index FROM forwards WHERE (1 = ? OR state = ?) AND (1 = ? OR in_channel_scid = ?) AND (1 = ? OR out_channel_scid = ?)",
         .query = "SELECT  state, in_msatoshi, out_msatoshi, in_channel_scid, out_channel_scid, in_htlc_id, out_htlc_id, received_time, resolved_time, failcode , forward_style , rowid , updated_index FROM forwards WHERE (1 = $1 OR state = $2) AND (1 = $3 OR in_channel_scid = $4) AND (1 = $5 OR out_channel_scid = $6)",
         .placeholders = 6,
         .readonly = true,
         .colnames = col_table431,
         .num_colnames = ARRAY_SIZE(col_table431),
    },
    {
         .name = "ALTER TABLE forwarded_payments ADD received_time BIGINT",
         .query = "ALTER TABLE forwarded_payments ADD received_time BIGINT",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "UPDATE channels SET remote_static_remotekey_start = 9223372036854775807, local_static_remotekey_start = 9223372036854775807 WHERE option_static_remotekey = 0",
         .query = "UPDATE channels SET remote_static_remotekey_start = 9223372036854775807, local_static_remotekey_start = 9223372036854775807 WHERE option_static_remotekey = 0",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DELETE FROM local_anchors WHERE channel_id = ? and commitment_index <= ?;",
         .query = "DELETE FROM local_anchors WHERE channel_id = $1 and commitment_index <= $2;",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "SELECT commitnum, txid, outnum, amount FROM penalty_bases WHERE channel_id = ?",
         .query = "SELECT commitnum, txid, outnum, amount FROM penalty_bases WHERE channel_id = $1",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table440,
         .num_colnames = ARRAY_SIZE(col_table440),
    },
    {
         .name = "UPDATE channels SET  remote_ann_node_sig=?,  remote_ann_bitcoin_sig=? WHERE id=?",
         .query = "UPDATE channels SET  remote_ann_node_sig=$1,  remote_ann_bitcoin_sig=$2 WHERE id=$3",
         .placeholders = 3,
         .readonly = false,
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE channels ADD shutdown_scriptpubkey_local BLOB;",
         .query = "ALTER TABLE channels ADD shutdown_scriptpubkey_local BYTEA;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE invoices ADD COLUMN local_offer_id BLOB DEFAULT NULL REFERENCES offers(offer_id);",
         .query = "ALTER TABLE invoices ADD COLUMN local_offer_id BYTEA DEFAULT NULL REFERENCES offers(offer_id);",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD groupid BIGINT;",
         .query = "ALTER TABLE channel_htlcs ADD groupid BIGINT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT MIN(expiry_time)  FROM invoices WHERE state = ?;",
         .query = "SELECT MIN(expiry_time)  FROM invoices WHERE state = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table287,
         .num_colnames = ARRAY_SIZE(col_table287),
    },
    {
         .name = "SELECT id FROM channels ORDER BY id DESC LIMIT 1;",
         .query = "SELECT id FROM channels ORDER BY id DESC LIMIT 1;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table338,
         .num_colnames = ARRAY_SIZE(col_table338),
    },
    {
         .name = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE local_invreq_id = ?;",
         .query = "SELECT  id, updated_index, status, destination, msatoshi, payment_hash, timestamp, payment_preimage, path_secrets, route_nodes, route_channels, msatoshi_sent, description, bolt11, paydescription, failonionreply, total_msat, partid, local_invreq_id, groupid, completed_at FROM payments WHERE local_invreq_id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table397,
         .num_colnames = ARRAY_SIZE(col_table397),
    },
    {
         .name = "UPDATE channels SET short_channel_id = REPLACE(short_channel_id, ':', 'x') WHERE short_channel_id IS NOT NULL;",
         .query = "UPDATE channels SET short_channel_id = REPLACE(short_channel_id, ':', 'x') WHERE short_channel_id IS NOT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE invoices (  id BIGSERIAL,  state INTEGER,  msatoshi BIGINT,  payment_hash BLOB,  payment_key BLOB,  label TEXT,  PRIMARY KEY (id),  UNIQUE (label),  UNIQUE (payment_hash));",
         .query = "CREATE TABLE invoices (  id BIGSERIAL,  state INTEGER,  msatoshi BIGINT,  payment_hash BYTEA,  payment_key BYTEA,  label TEXT,  PRIMARY KEY (id),  UNIQUE (label),  UNIQUE (payment_hash));",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "SELECT MAX(rowid) FROM forwards;",
         .query = "SELECT MAX(rowid) FROM forwards;",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table276,
         .num_colnames = ARRAY_SIZE(col_table276),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "ALTER TABLE payments ADD failchannel TEXT;",
         .query = "ALTER TABLE payments ADD failchannel TEXT;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "CREATE TABLE blocks (height INT, hash BLOB, prev_hash BLOB, UNIQUE(height));",
         .query = "CREATE TABLE blocks (height INT, hash BYTEA, prev_hash BYTEA, UNIQUE(height));",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "SELECT blobval FROM vars WHERE name='node_id'",
         .query = "SELECT blobval FROM vars WHERE name='node_id'",
         .placeholders = 0,
         .readonly = true,
         .colnames = col_table403,
         .num_colnames = ARRAY_SIZE(col_table403),
    },
    {
         .name = "INSERT INTO runes (id, rune) VALUES (?, ?);",
         .query = "INSERT INTO runes (id, rune) VALUES ($1, $2);",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "DELETE FROM forwards WHERE in_channel_scid = ? AND in_htlc_id IS NULL AND state = ?",
         .query = "DELETE FROM forwards WHERE in_channel_scid = $1 AND in_htlc_id IS NULL AND state = $2",
         .placeholders = 2,
         .readonly = false,
    },
    {
    },
    {
         .name = "ALTER TABLE channel_htlcs ADD COLUMN min_commit_num BIGINT default 0;",
         .query = "ALTER TABLE channel_htlcs ADD COLUMN min_commit_num BIGINT default 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "DROP TABLE forwarded_payments;",
         .query = "DROP TABLE forwarded_payments;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO channel_htlcs ( channel_id, channel_htlc_id, direction, origin_htlc, msatoshi, cltv_expiry, payment_hash, payment_key, hstate, routing_onion, malformed_onion, partid, groupid, fees_msat, min_commit_num) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, 0, ?, ?, ?, ?);",
         .query = "INSERT INTO channel_htlcs ( channel_id, channel_htlc_id, direction, origin_htlc, msatoshi, cltv_expiry, payment_hash, payment_key, hstate, routing_onion, malformed_onion, partid, groupid, fees_msat, min_commit_num) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, 0, $11, $12, $13, $14);",
         .placeholders = 14,
         .readonly = false,
    },
    {
         .name = "ALTER TABLE channels ADD funding_psbt BLOB DEFAULT NULL;",
         .query = "ALTER TABLE channels ADD funding_psbt BYTEA DEFAULT NULL;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
    },
    {
         .name = "CREATE TABLE tablea (  id BIGSERIAL, field1 INTEGER, PRIMARY KEY (id))",
         .query = "CREATE TABLE tablea (  id BIGSERIAL, field1 INTEGER, PRIMARY KEY (id))",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "UPDATE channels SET shutdown_keyidx_local=0 WHERE shutdown_keyidx_local = -1;",
         .query = "UPDATE channels SET shutdown_keyidx_local=0 WHERE shutdown_keyidx_local = -1;",
         .placeholders = 0,
         .readonly = false,
    },
    {
    },
    {
         .name = "SELECT local_offer_id FROM invoices WHERE id = ?;",
         .query = "SELECT local_offer_id FROM invoices WHERE id = $1;",
         .placeholders = 1,
         .readonly = true,
         .colnames = col_table299,
         .num_colnames = ARRAY_SIZE(col_table299),
    },
    {
    },
    {
    },
    {
    },
    {
    },
    {
         .name = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 4, local_feerate_per_kw FROM channels WHERE funder = 0;",
         .query = "INSERT INTO channel_feerates(channel_id, hstate, feerate_per_kw) SELECT id, 4, local_feerate_per_kw FROM channels WHERE funder = 0;",
         .placeholders = 0,
         .readonly = false,
    },
    {
         .name = "INSERT INTO addresses (  keyidx, addrtype) VALUES (?, ?);",
         .query = "INSERT INTO addresses (  keyidx, addrtype) VALUES ($1, $2);",
         .placeholders = 2,
         .readonly = false,
    },
    {
         .name = "DELETE FROM forwards WHERE in_channel_scid = ? AND in_htlc_id = ? AND state = ?",
         .query = "DELETE FROM forwards WHERE in_channel_scid = $1 AND in_htlc_id = $2 AND state = $3",
         .placeholders = 3,
         .readonly = false,
    },
    {
         .name = "UPDATE invoices   SET description = NULL,       updated_index = ? WHERE ID = ?;",
         .query = "UPDATE invoices   SET description = NULL,       updated_index = $1 WHERE ID = $2;",
         .placeholders = 2,
         .readonly = false,
    },
};

struct db_query_set postgres_query_set = {
         .name = "postgres",
         .query_table = db_postgres_queries,
         .query_table_size = ARRAY_SIZE(db_postgres_queries),
};

AUTODATA(db_queries, &postgres_query_set);
#endif /* HAVE_POSTGRES */

#endif /* LIGHTNINGD_WALLET_GEN_DB_POSTGRES */

// SHA256STAMP:1c473f9f95d73f64c4ea2c8adeab326aabac3f1e4b7717c48ff5501cb71d20d8
