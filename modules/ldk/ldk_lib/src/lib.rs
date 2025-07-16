use lightning::bitcoin::hex::{Case, DisplayHex};
use lightning::bolt11_invoice::{
    Bolt11Invoice, Bolt11InvoiceDescriptionRef, Bolt11SemanticError, Currency, ParseOrSemanticError,
};
use lightning::io::Cursor;
use lightning::ln::msgs;
use lightning::offers::offer::{self, Offer};
use lightning::util::ser::Readable;
use std::ffi::CString;
use std::os::raw::c_char;
use std::{ffi::CStr, str::FromStr};

unsafe fn str_to_c_string(input: &str) -> *mut c_char {
    CString::new(input).unwrap().into_raw()
}

#[no_mangle]
pub unsafe extern "C" fn ldk_des_invoice(input: *const std::os::raw::c_char) -> *mut c_char {
    if input.is_null() {
        return str_to_c_string("");
    }

    // Convert C string to Rust string
    let c_str = match CStr::from_ptr(input).to_str() {
        Ok(s) => s,
        Err(_) => return str_to_c_string(""),
    };

    match Bolt11Invoice::from_str(c_str) {
        Ok(invoice) => {
            if invoice.currency() != Currency::Bitcoin {
                return str_to_c_string("");
            }
            let mut result = String::new();

            result.push_str("HASH=");
            result.push_str(&invoice.payment_hash().to_string());

            result.push_str(";PAYMENT_SECRET=");
            result.push_str(&invoice.payment_secret().to_string());

            result.push_str(";AMOUNT=");
            if let Some(amount) = invoice.amount_milli_satoshis() {
                result.push_str(&amount.to_string());
            } else {
                result.push_str("0");
            }

            result.push_str(";DESCRIPTION=");
            if let Bolt11InvoiceDescriptionRef::Direct(direct_description) = invoice.description() {
                result.push_str(&direct_description.to_string());
            }

            result.push_str(";METADATA=");
            if let Some(metadata) = invoice.payment_metadata() {
                result.push_str(&metadata.to_hex_string(Case::Lower));
            }

            let invoice_payee_pub_key = match invoice.payee_pub_key() {
                Some(payee) => payee.clone(),
                None => invoice.recover_payee_pub_key(),
            };

            result.push_str(";RECIPIENT=");
            result.push_str(&invoice_payee_pub_key.to_string());

            result.push_str(";DESCRIPTION_HASH=");
            if let Bolt11InvoiceDescriptionRef::Hash(hash_description) = invoice.description() {
                result.push_str(&hash_description.0.to_string());
            }

            // Convert the expiry time to seconds, ensuring consistent overflow behavior
            // with other implementations like LND. The multiplication and division by 1000000000
            // may appear redundant, but it's intentionally mirroring the nanosecond conversion
            // logic used in LND to ensure the same overflow characteristics.
            result.push_str(";EXPIRY=");
            result.push_str(
                ((invoice.expiry_time().as_secs() * 1000000000) / 1000000000)
                    .to_string()
                    .as_str(),
            );


            result.push_str(";TIMESTAMP=");
            result.push_str(
                &invoice
                    .clone()
                    .into_signed_raw()
                    .raw_invoice()
                    .data
                    .timestamp
                    .as_unix_timestamp()
                    .to_string(),
            );

            result.push_str(";FALLBACK_ADDRESS=");
            // Use only the first fallback address for compatibility with LND,
            // which ignores additional fallback fields.
            // See: https://github.com/lightningnetwork/lnd/issues/9591
            let fallback = invoice.fallback_addresses().first().cloned();
            if let Some(addr) = fallback {
                result.push_str(&addr.to_string());
            }

            invoice.private_routes().iter().for_each(|route| {
                result.push_str(&";PRIVATE_ROUTE=[");
                route.0.iter().enumerate().for_each(|(i, hop)| {
                    if i == 0 {
                        result.push_str("(");
                    } else {
                        result.push_str(",(");
                    }
                    result.push_str("NODE_ID=");
                    result.push_str(&hop.src_node_id.to_string());
                    result.push_str(",SHORT_CHANNEL_ID=");
                    result.push_str(&hop.short_channel_id.to_string());
                    result.push_str(",FEES=");
                    result.push_str(&hop.fees.base_msat.to_string());
                    result.push_str(",CLTV_EXPIRY_DELTA=");
                    result.push_str(&hop.cltv_expiry_delta.to_string());
                    result.push_str(",PROPORTIONAL_MILLIONTHS=");
                    result.push_str(&hop.fees.proportional_millionths.to_string());
                    result.push_str(")");
                });
                result.push_str("]");
            });

            result.push_str(";MIN_CLTV=");
            result.push_str(&invoice.min_final_cltv_expiry_delta().to_string());

            result.push_str(";FEATURES=");
            if invoice.features().is_some() {
                let mut flags = invoice.features().unwrap().le_flags().to_vec();
                flags.reverse();
                result.push_str(&flags.to_hex_string(Case::Lower));
            }

            str_to_c_string(&result)
        }
        // Handle invoices without payment secrets by returning null
        // This is needed because some Lightning implementations don't require payment secrets,
        // and we need to maintain compatibility with these implementations
        Err(ParseOrSemanticError::SemanticError(Bolt11SemanticError::NoPaymentSecret)) => {
            std::ptr::null_mut()
        }
        // Handle invoices with multiple payment hashes by returning null
        // This is needed because some Lightning implementations don't require payment to have only one hash,
        // and we need to maintain compatibility with these implementations
        Err(ParseOrSemanticError::SemanticError(Bolt11SemanticError::MultiplePaymentHashes)) => {
            std::ptr::null_mut()
        }
        // Handle invoices with multiple descriptions hashes by returning null
        // This is needed because some Lightning implementations don't require to have only one description,
        // and we need to maintain compatibility with these implementations
        Err(ParseOrSemanticError::SemanticError(Bolt11SemanticError::MultipleDescriptions)) => {
            std::ptr::null_mut()
        }
        Err(_) => str_to_c_string(""),
    }
}

#[no_mangle]
pub unsafe extern "C" fn ldk_des_offer(input: *const std::os::raw::c_char) -> *mut c_char {
    if input.is_null() {
        return str_to_c_string("");
    }

    // Convert C string to Rust string
    let c_str = match CStr::from_ptr(input).to_str() {
        Ok(s) => s,
        Err(_) => return str_to_c_string(""),
    };

    match Offer::from_str(c_str) {
        Ok(offer) => {
            let mut result = String::new();

            result.push_str("CHAINS=");
            offer.chains().iter().for_each(|chain| {
                result.push_str(&format!("{};", chain.to_string()));
            });

            result.push_str("METADATA=");
            if let Some(metadata) = offer.metadata() {
                result.push_str(&metadata.to_hex_string(Case::Lower));
            }

            if let Some(amount) = offer.amount() {
                match amount {
                    offer::Amount::Bitcoin { amount_msats } => {
                        result.push_str(";AMOUNT=");
                        result.push_str(&amount_msats.to_string());
                    }
                    offer::Amount::Currency {
                        iso4217_code,
                        amount,
                    } => {
                        result.push_str(";AMOUNT=");
                        result.push_str(&amount.to_string());
                        result.push_str(";CURRENCY=");
                        let code_str = match std::str::from_utf8(&iso4217_code) {
                            Ok(s) => s,
                            Err(_) => "Unknown",
                        };
                        result.push_str(code_str);
                    }
                }
            }

            result.push_str(";DESCRIPTION=");
            if let Some(description) = offer.description() {
                result.push_str(description.0);
            }

            result.push_str(";FEATURES=");
            let features = offer.offer_features();
            let mut be_flags = features.le_flags().to_vec();
            be_flags.reverse();
            result.push_str(be_flags.to_hex_string(Case::Lower).as_str());

            result.push_str(";ABSOLUTE_EXPIRY=");
            if let Some(absolute_expiry) = offer.absolute_expiry() {
                result.push_str(absolute_expiry.as_secs().to_string().as_str());
            }

            offer.paths().iter().enumerate().for_each(|(i, path)| {
                path.blinded_hops().iter().for_each(|hop| {
                    result.push_str(&format!(";PATH_{}_HOP=", i));
                    result.push_str(hop.blinded_node_id.to_string().as_str());
                });
            });

            result.push_str(";ISSUER=");
            if let Some(issuer) = offer.issuer() {
                result.push_str(issuer.0);
            }

            result.push_str(";QUANTITY=");
            let quantity = offer.supported_quantity();
            match quantity {
                offer::Quantity::Bounded(n) => result.push_str(&n.to_string()),
                _ => (),
            }

            result.push_str(";ISSUER_ID=");
            if let Some(issuer_id) = offer.issuer_signing_pubkey() {
                result.push_str(&issuer_id.to_string());
            }

            str_to_c_string(&result)
        }
        Err(_) => str_to_c_string(""),
    }
}

pub fn deserialize_gossip_message(data: &[u8]) -> Result<String, String> {
    if data.len() < 2 {
        return Err("Buffer too small".to_string());
    }

    // Read the message type (first 2 bytes, big-endian)
    let msg_type = u16::from_be_bytes([data[0], data[1]]);

    // Check if it's a routing/gossip message (types 256-511)
    if msg_type < 256 || msg_type > 511 {
        return Err("Not a gossip message".to_string());
    }

    // Create a cursor for the entire message (including type bytes)
    let mut cursor = Cursor::new(data);
    let mut result = String::new();
    result.push_str(&format!("Message Type: {}\n", msg_type));

    // Parse based on specific message type using LengthReadable
    match msg_type {
        256 => {
            // ChannelAnnouncement
            match msgs::ChannelAnnouncement::read(&mut cursor) {
                Ok(msg) => {
                    result.push_str("Channel Announcement\n");
                    result.push_str(&format!(
                        "Short Channel ID: {}\n",
                        msg.contents.short_channel_id
                    ));
                    result.push_str(&format!("Node ID 1: {:02x?}\n", msg.contents.node_id_1));
                    result.push_str(&format!("Node ID 2: {:02x?}\n", msg.contents.node_id_2));
                    result.push_str(&format!(
                        "Bitcoin Key 1: {:02x?}\n",
                        msg.contents.bitcoin_key_1
                    ));
                    result.push_str(&format!(
                        "Bitcoin Key 2: {:02x?}\n",
                        msg.contents.bitcoin_key_2
                    ));
                    result.push_str(&format!("Chain Hash: {:02x?}\n", msg.contents.chain_hash));
                }
                Err(e) => return Err(format!("Failed to parse ChannelAnnouncement: {:?}", e)),
            }
        }
        257 => {
            // NodeAnnouncement
            match msgs::NodeAnnouncement::read(&mut cursor) {
                Ok(msg) => {
                    result.push_str("Node Announcement\n");
                    result.push_str(&format!("Node ID: {:02x?}\n", msg.contents.node_id));
                    let alias = String::from_utf8_lossy(&msg.contents.alias.0)
                        .trim_end_matches('\0')
                        .to_string();
                    result.push_str(&format!("Alias: {}\n", alias));
                    result.push_str(&format!("Timestamp: {}\n", msg.contents.timestamp));
                    result.push_str(&format!(
                        "RGB Color: {:02x}{:02x}{:02x}\n",
                        msg.contents.rgb[0], msg.contents.rgb[1], msg.contents.rgb[2]
                    ));
                    result.push_str(&format!(
                        "Addresses: {} entries\n",
                        msg.contents.addresses.len()
                    ));
                }
                Err(e) => return Err(format!("Failed to parse NodeAnnouncement: {:?}", e)),
            }
        }
        258 => {
            // ChannelUpdate
            match msgs::ChannelUpdate::read(&mut cursor) {
                Ok(msg) => {
                    result.push_str("Channel Update\n");
                    result.push_str(&format!(
                        "Short Channel ID: {}\n",
                        msg.contents.short_channel_id
                    ));
                    result.push_str(&format!("Timestamp: {}\n", msg.contents.timestamp));
                    result.push_str(&format!("Fee Base: {} msat\n", msg.contents.fee_base_msat));
                    result.push_str(&format!(
                        "Fee Rate: {} millionths\n",
                        msg.contents.fee_proportional_millionths
                    ));
                    result.push_str(&format!(
                        "CLTV Expiry Delta: {}\n",
                        msg.contents.cltv_expiry_delta
                    ));
                    result.push_str(&format!(
                        "HTLC Min: {} msat\n",
                        msg.contents.htlc_minimum_msat
                    ));
                    result.push_str(&format!(
                        "HTLC Max: {} msat\n",
                        msg.contents.htlc_maximum_msat
                    ));
                    result.push_str(&format!(
                        "Channel Flags: 0x{:02x}\n",
                        msg.contents.channel_flags
                    ));
                    result.push_str(&format!(
                        "Message Flags: 0x{:02x}\n",
                        msg.contents.message_flags
                    ));
                }
                Err(e) => return Err(format!("Failed to parse ChannelUpdate: {:?}", e)),
            }
        }
        259 => {
            // AnnouncementSignatures
            match msgs::AnnouncementSignatures::read(&mut cursor) {
                Ok(msg) => {
                    result.push_str("Announcement Signatures\n");
                    result.push_str(&format!("Channel ID: {:02x?}\n", msg.channel_id));
                    result.push_str(&format!("Short Channel ID: {}\n", msg.short_channel_id));
                }
                Err(e) => return Err(format!("Failed to parse AnnouncementSignatures: {:?}", e)),
            }
        }
        261 => {
            // QueryShortChannelIds
            match msgs::QueryShortChannelIds::read(&mut cursor) {
                Ok(msg) => {
                    result.push_str("Query Short Channel IDs\n");
                    result.push_str(&format!("Chain Hash: {:02x?}\n", msg.chain_hash));
                    result.push_str(&format!(
                        "Number of Channel IDs: {}\n",
                        msg.short_channel_ids.len()
                    ));
                }
                Err(e) => return Err(format!("Failed to parse QueryShortChannelIds: {:?}", e)),
            }
        }
        262 => {
            // ReplyShortChannelIdsEnd
            match msgs::ReplyShortChannelIdsEnd::read(&mut cursor) {
                Ok(msg) => {
                    result.push_str("Reply Short Channel IDs End\n");
                    result.push_str(&format!("Chain Hash: {:02x?}\n", msg.chain_hash));
                    result.push_str(&format!("Full Information: {}\n", msg.full_information));
                }
                Err(e) => return Err(format!("Failed to parse ReplyShortChannelIdsEnd: {:?}", e)),
            }
        }
        263 => {
            // QueryChannelRange
            match msgs::QueryChannelRange::read(&mut cursor) {
                Ok(msg) => {
                    result.push_str("Query Channel Range\n");
                    result.push_str(&format!("Chain Hash: {:02x?}\n", msg.chain_hash));
                    result.push_str(&format!("First Block: {}\n", msg.first_blocknum));
                    result.push_str(&format!("Number of Blocks: {}\n", msg.number_of_blocks));
                }
                Err(e) => return Err(format!("Failed to parse QueryChannelRange: {:?}", e)),
            }
        }
        264 => {
            // ReplyChannelRange
            match msgs::ReplyChannelRange::read(&mut cursor) {
                Ok(msg) => {
                    result.push_str("Reply Channel Range\n");
                    result.push_str(&format!("Chain Hash: {:02x?}\n", msg.chain_hash));
                    result.push_str(&format!("First Block: {}\n", msg.first_blocknum));
                    result.push_str(&format!("Number of Blocks: {}\n", msg.number_of_blocks));
                    result.push_str(&format!("Sync Complete: {}\n", msg.sync_complete));
                    result.push_str(&format!(
                        "Short Channel IDs: {} entries\n",
                        msg.short_channel_ids.len()
                    ));
                }
                Err(e) => return Err(format!("Failed to parse ReplyChannelRange: {:?}", e)),
            }
        }
        265 => {
            // GossipTimestampFilter
            match msgs::GossipTimestampFilter::read(&mut cursor) {
                Ok(msg) => {
                    result.push_str("Gossip Timestamp Filter\n");
                    result.push_str(&format!("Chain Hash: {:02x?}\n", msg.chain_hash));
                    result.push_str(&format!("First Timestamp: {}\n", msg.first_timestamp));
                    result.push_str(&format!("Timestamp Range: {}\n", msg.timestamp_range));
                }
                Err(e) => return Err(format!("Failed to parse GossipTimestampFilter: {:?}", e)),
            }
        }
        _ => {
            result.push_str("Unknown gossip message type\n");
        }
    }

    Ok(result)
}

#[no_mangle]
pub extern "C" fn ldk_free_string(ptr: *mut c_char) {
    if !ptr.is_null() {
        unsafe {
            let _ = CString::from_raw(ptr);
        }
    }
}
