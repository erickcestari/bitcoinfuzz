use lightning_invoice::Currency;
use secp256k1::{
    constants::{CURVE_ORDER, FIELD_SIZE},
    ecdsa::Signature,
};
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
            let signature = invoice.signature().0.to_standard().serialize_der().to_vec();
            let is_currency_bitcoin = invoice.currency() == Currency::Bitcoin;
            let has_payment_hash = invoice.payment_hash().is_some();

            match validate_signature(&signature) {
                Ok(true) => has_payment_hash && is_currency_bitcoin,
                _ => false,
            }
        }
        Err(_) => false,
    }
}

// Helper function to validate signature components
fn validate_signature(signature: &[u8]) -> Result<bool, ()> {
    // Check signature length (DER encoded signature is typically 70-73 bytes)
    if signature.len() < 8 || signature.len() > 73 {
        return Ok(false);
    }

    // First, try to parse the DER signature
    let sig = match Signature::from_der(signature) {
        Ok(s) => s,
        Err(_) => return Ok(false),
    };

    // Get the compact form to access R and S values
    let compact = sig.serialize_compact();

    // Extract R value (first 32 bytes)
    let r_bytes = &compact[0..32];

    // Compare R+N with P using byte array comparison
    // We need to check if R + N >= P

    // First, we check if R is already >= P (since N is positive, this would make R+N >= P)
    if bytes_greater_than_or_equal(r_bytes, &FIELD_SIZE) {
        return Ok(false);
    }

    // Manual calculation to check if R + N >= P
    // We need to add R + N and compare with P
    let mut sum = [0u8; 32];
    let mut carry = 0u16;

    // Add r_bytes and CURVE_ORDER (N) from least significant byte to most
    for i in (0..32).rev() {
        let r_val = r_bytes[i] as u16;
        let n_val = CURVE_ORDER[i] as u16;

        let total = r_val + n_val + carry;
        sum[i] = (total & 0xFF) as u8;
        carry = total >> 8;
    }

    // If there's a carry or sum >= P, then R + N >= P
    if carry > 0 || bytes_greater_than_or_equal(&sum, &FIELD_SIZE) {
        return Ok(false);
    }

    Ok(true)
}

// Helper function to compare two 32-byte arrays
fn bytes_greater_than_or_equal(a: &[u8], b: &[u8]) -> bool {
    for i in 0..32 {
        if a[i] > b[i] {
            return true;
        } else if a[i] < b[i] {
            return false;
        }
    }

    true
}
