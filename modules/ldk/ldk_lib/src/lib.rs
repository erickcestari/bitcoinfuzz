use lightning::bitcoin::hex::{Case, DisplayHex};
use lightning::bolt11_invoice::{
    Bolt11Invoice, Bolt11InvoiceDescriptionRef, Bolt11SemanticError, Currency, ParseOrSemanticError,
};
use lightning::offers::refund::Refund;
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

            result.push_str(";AMOUNT=");
            if let Some(amount) = invoice.amount_milli_satoshis() {
                result.push_str(&amount.to_string());
            }

            result.push_str(";DESCRIPTION=");
            if let Bolt11InvoiceDescriptionRef::Direct(direct_description) = invoice.description() {
                result.push_str(&direct_description.to_string());
            }

            let invoice_payee_pub_key = match invoice.payee_pub_key() {
                Some(payee) => payee.clone(),
                None => invoice.recover_payee_pub_key(),
            };

            result.push_str(";RECIPIENT=");
            result.push_str(&invoice_payee_pub_key.to_string());

            result.push_str(";EXPIRY=");
            result.push_str(&invoice.expiry_time().as_secs().to_string());

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

            result.push_str(";ROUTING_HINTS=");
            result.push_str(&invoice.private_routes().len().to_string());

            result.push_str(";MIN_CLTV=");
            result.push_str(&invoice.min_final_cltv_expiry_delta().to_string());

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
pub unsafe extern "C" fn ldk_des_invoice_request(
    input: *const std::os::raw::c_char,
) -> *mut c_char {
    if input.is_null() {
        return str_to_c_string("");
    }

    // Convert C string to Rust string
    let c_str = match CStr::from_ptr(input).to_str() {
        Ok(s) => s,
        Err(_) => return str_to_c_string(""),
    };

    match Refund::from_str(c_str) {
        Ok(invoice_request) => {
            let mut result = String::new();

            result.push_str("CHAIN=");
            result.push_str(&invoice_request.chain().to_string());

            result.push_str(";METADATA=");
            result.push_str(&invoice_request.payer_metadata().to_hex_string(Case::Lower));

            result.push_str(";AMOUNT=");
            result.push_str(&invoice_request.amount_msats().to_string());

            result.push_str(";DESCRIPTION=");
            result.push_str(invoice_request.description().0);

            result.push_str(";FEATURES=");
            let features = invoice_request.features();
            let mut be_flags = features.le_flags().to_vec();
            be_flags.reverse();
            result.push_str(be_flags.to_hex_string(Case::Lower).as_str());

            result.push_str(";ABSOLUTE_EXPIRY=");
            if let Some(absolute_expiry) = invoice_request.absolute_expiry() {
                result.push_str(absolute_expiry.as_secs().to_string().as_str());
            }

            invoice_request.paths().iter().for_each(|path| {
                path.blinded_hops().iter().for_each(|hop| {
                    result.push_str(";BLINDED_HOP=");
                    result.push_str(hop.blinded_node_id.to_string().as_str());
                });
            });

            result.push_str(";ISSUER=");
            if let Some(issuer) = invoice_request.issuer() {
                result.push_str(issuer.0);
            }

            result.push_str(";QUANTITY=");
            if let Some(quantity) = invoice_request.quantity() {
                result.push_str(&quantity.to_string());
            }

            result.push_str(";ISSUER_ID=");
            result.push_str(&invoice_request.payer_signing_pubkey().to_string());

            result.push_str(";NOTE=");
            if let Some(note) = invoice_request.payer_note() {
                result.push_str(note.0);
            }

            str_to_c_string(&result)
        }
        Err(_) => str_to_c_string(""),
    }
}

#[no_mangle]
pub extern "C" fn ldk_free_string(ptr: *mut c_char) {
    if !ptr.is_null() {
        unsafe {
            let _ = CString::from_raw(ptr);
        }
    }
}
