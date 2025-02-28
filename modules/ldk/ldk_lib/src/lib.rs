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
        Ok(_) => true,
        Err(_) => false,
    }
}
