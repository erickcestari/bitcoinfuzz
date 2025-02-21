use lightning_invoice::Currency;
use std::str::FromStr;

#[no_mangle]
pub unsafe extern "C" fn ldk_des_invoice(data: *const u8, len: usize) -> bool {
    if data.is_null() || len == 0 {
        return false;
    }

    let data_slice = std::slice::from_raw_parts(data, len);

    let s = match std::str::from_utf8(data_slice) {
        Ok(v) => v,
        Err(_) => return false,
    };

    match lightning_invoice::SignedRawBolt11Invoice::from_str(s) {
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

            has_payment_hash && is_currency_bitcoin && is_signature_valid
        }
        Err(_) => false,
    }
}
