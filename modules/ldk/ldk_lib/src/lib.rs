use lightning_invoice::Currency;
use std::{ffi::CStr, str::FromStr};
use std::ffi::CString;
use std::os::raw::c_char;

unsafe fn str_to_c_string(input: &str) -> *mut c_char {
    CString::new(input).unwrap().into_raw()
}

#[no_mangle]
pub unsafe extern "C" fn ldk_des_invoice(input: *const std::os::raw::c_char) -> *mut c_char {
    if input.is_null() {
        return str_to_c_string("0");
    }

    // Convert C string to Rust string
    let c_str = match CStr::from_ptr(input).to_str() {
        Ok(s) => s,
        Err(_) => return str_to_c_string("0"),
    };

    match lightning_invoice::SignedRawBolt11Invoice::from_str(c_str) {
        Ok(invoice) => {
            // If the destination pubkey was provided as a tagged field, use that
            // to verify the signature, otherwise recover it from the signature
            let is_signature_valid = if let Some(_) = invoice.payee_pub_key() {
                invoice.check_signature()
            } else {
                invoice.recover_payee_pub_key().is_ok()
            };
            let is_currency_bitcoin = invoice.currency() == Currency::Bitcoin;
            let has_payment_hash = invoice.payment_hash().is_some();
            if has_payment_hash && is_currency_bitcoin && is_signature_valid {
                let mut result = String::new();

                result.push_str("HASH=");
                result.push_str(&invoice.payment_hash().unwrap().0.to_string());

                result.push_str(";AMOUNT=");
                if let Some(amount) = invoice.amount_pico_btc()  {
                    let amount_milisatoshis = amount * 1_000_000_000;
                    result.push_str(&amount_milisatoshis.to_string());
                }
                
                result.push_str(";DESCRIPTION=");
                if let Some(description) = invoice.description() {
                    result.push_str(&description.to_string());
                }
                
                let invoice_payee_pub_key = match invoice.payee_pub_key() {
                    Some(payee) => Some(payee.clone()),
                    None => {match invoice.recover_payee_pub_key() {
                        Ok(payee) => Some(payee),
                        Err(_) => None,
                    }}
                };

                result.push_str(";RECIPIENT=");
                if let Some(recipient) = invoice_payee_pub_key{
                    result.push_str(&recipient.0.to_string());
                }
                
                result.push_str(";EXPIRY=");
                if let Some(expiry) = invoice.expiry_time() {
                    result.push_str(&expiry.as_seconds().to_string());
                }

                result.push_str(";TIMESTAMP=");
                result.push_str(&invoice.raw_invoice().data.timestamp.as_unix_timestamp().to_string());

                result.push_str(";ROUTING_HINTS=");
                result.push_str(&invoice.private_routes().len().to_string());

                result.push_str(";MIN_CLTV=");
                if let Some(min_final_cltv_expiry_delta) = invoice.min_final_cltv_expiry_delta() {
                    result.push_str(&min_final_cltv_expiry_delta.0.to_string());
                }

                return str_to_c_string(&result);
            }
            str_to_c_string("0")
        }
        Err(_) => str_to_c_string("0"),
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