use std::ffi::CString;
use std::os::raw::c_char;
use std::slice;

use psbt_v2::bitcoin::Psbt;
use psbt_v2::bitcoin::hex::DisplayHex;

unsafe fn str_to_c_string(input: &str) -> *mut c_char {
    CString::new(input).unwrap().into_raw()
}

/// Frees a C string created by `str_to_c_string`.
///
/// # Safety
/// The pointer must have been created by `str_to_c_string` and not yet freed.
/// After calling this function, the pointer is invalid and must not be used.
#[no_mangle]
pub unsafe extern "C" fn rust_psbt_free_c_string(ptr: *mut c_char) {
    if !ptr.is_null() {
        // Convert the raw pointer back to a CString, which will be dropped
        // and free the memory when it goes out of scope
        let _ = CString::from_raw(ptr);
    }
}

#[no_mangle]
pub unsafe extern "C" fn rust_psbt_psbt_parse(data: *const u8, len: usize) -> *mut c_char {
    let data_slice = slice::from_raw_parts(data, len);

    match Psbt::deserialize(data_slice) {
        Ok(psbt) => {
            let mut result = String::new();
            let tx = psbt.unsigned_tx;

            result.push_str(&format!("tx.version={};", tx.version));
            result.push_str(&format!("tx.locktime={};", tx.lock_time));
            result.push_str(&format!("tx.inputs={};", tx.input.len()));
            result.push_str(&format!("tx.outputs={};", tx.output.len()));

            result.push_str(&format!("psbt.inputs={};", psbt.inputs.len()));
            result.push_str(&format!("psbt.outputs={};", psbt.outputs.len()));

            result.push_str("tx_inputs=[");
            for input in tx.input.iter() {
                result.push_str(&format!(
                    "{{txid={}:{};",
                    input.previous_output.txid, input.previous_output.vout
                ));
                result.push_str(&format!("sequence={};", input.sequence));
                result.push_str(&format!("scriptsig={:x};", input.script_sig));
                result.push_str(&format!("witness_stack="));
                for (j, element) in input.witness.iter().enumerate() {
                    if j > 0 {
                        result.push(',');
                    }
                    result.push_str(&element.to_lower_hex_string());
                }
                result.push_str(";}");
            }
            result.push_str("];");

            result.push_str("psbt_inputs=[");
            for input in psbt.inputs.iter() {
                result.push_str(&format!(
                    "{{redeem={};",
                    input
                        .redeem_script.as_ref()
                        .map(|redeem| redeem.to_hex_string())
                        .unwrap_or("".to_string())
                ));
                result.push_str(&format!(
                    "script_sig_final={};",
                    input
                        .final_script_sig.as_ref()
                        .map(|script_sig| script_sig.to_hex_string())
                        .unwrap_or("".to_string())
                ));
                result.push_str(&format!(
                    "witness_script={};",
                    input
                        .witness_script.as_ref()
                        .map(|witness| witness.to_hex_string())
                        .unwrap_or("".to_string())
                ));
                result.push_str("final_witness_script=");
                if let Some(witness) = input.final_script_witness.as_ref() {
                    for (j, element) in witness.iter().enumerate() {
                        if j > 0 {
                            result.push(',');
                        }
                        result.push_str(&element.to_lower_hex_string());
                    }
                }
                result.push_str(";}");
            }
            result.push_str("];");

            result.push_str("tx_outputs=[");
            for output in tx.output.iter() {
                result.push_str(&format!("{{value={};", output.value.to_sat()));
                result.push_str(&format!(
                    "script={};}}",
                    output.script_pubkey.to_hex_string()
                ));
            }
            result.push_str("];");

            result.push_str("psbt_outputs=[");
            for output in psbt.outputs.iter() {
                result.push_str(&format!(
                    "{{redeem={};",
                    output
                        .redeem_script.as_ref()
                        .map(|redeem| redeem.to_hex_string())
                        .unwrap_or("".to_string())
                ));
                result.push_str(&format!(
                    "witness_script={};}}",
                    output
                        .witness_script.as_ref()
                        .map(|witness| witness.to_hex_string())
                        .unwrap_or("".to_string())
                ));
            }
            result.push_str("]");

            str_to_c_string(&result)
        }
        Err(_) => std::ptr::null_mut(),
    }
}
