/**
 * Custom Mutator for Lightning Network Onion Packets
 *
 * This custom mutator is designed for fuzzing Lightning Network onion routing
 * packets. It performs structure-aware mutations by decrypting the onion
 * packet, mutating the plaintext payload, and then re-encrypting and
 * re-authenticating the packet.
 *
 * Supports both standard and blinded onion payloads for route blinding.
 *
 * ONION PACKET STRUCTURE:
 * The fuzzer input contains an onion packet with the following format:
 *   [private_key:32][version:1][ephemeral_pubkey:33][hop_payloads:1300][hmac:32]
 *
 * Total size: 1398 bytes
 *
 * Fields:
 *   - private_key (32 bytes): Bob's private key used to decrypt the packet
 *   - version (1 byte): Packet version number (typically 0)
 *   - ephemeral_pubkey (33 bytes): Compressed secp256k1 public key for ECDH
 *   - hop_payloads (1300 bytes): Encrypted routing information and payment data
 *   - hmac (32 bytes): HMAC-SHA256 authentication tag
 *
 * HOP PAYLOADS FORMAT:
 * For legacy format:
 *   - length: 1 byte, always 0x00
 *   - payload: remaining bytes
 *
 * For TLV format (BigSize encoding):
 *   - If length < 0xfd: single byte length
 *   - If length >= 0xfd: 0xfd followed by be16(length)
 *   - payload: TLV stream
 *
 * MUTATION ALGORITHM:
 *
 * 1. Key Mutation (1% probability):
 *    - Generates a new random private key for Bob
 *    - Creates a new ephemeral keypair and updates the public key in the packet
 *
 * 2. Decryption Phase:
 *    a. Extract Bob's private key and the ephemeral public key from the packet
 *    b. Compute shared secret: ECDH(bob_private_key, ephemeral_public_key)
 *    c. Derive cryptographic keys from the shared secret using HMAC-SHA256:
 *       - rho: ChaCha20 encryption key
 *       - mu: HMAC authentication key
 *    d. Generate ChaCha20 keystream:
 *       - Key: rho
 *       - Nonce: 96-bit zero nonce (0x000000000000000000000000)
 *       - Counter: 0
 *       - Output: 1300 bytes of pseudo-random stream
 *    e. Decrypt hop_payloads by XORing with the keystream
 *
 * 3. Mutation Phase:
 *    a. Standard Mutation (40%):
 *       - Mutate the entire decrypted payload
 *       - Tests parser robustness and length validation
 *    b. Structure-Aware TLV Mutation (40%):
 *       - Parse TLV structure from decrypted payload
 *       - Apply structure-aware mutations: modify values, add/remove records,
 *         duplicate records, change types, or generate new valid payloads
 *       - Tests TLV-specific parsing logic and semantic validation
 *    c. Blinded Payload Mutation (20%):
 *       - Generate or mutate blinded payloads with encrypted_recipient_data
 *       - Structure-aware mutation of inner encrypted TLVs
 *       - Tests route blinding parsing and decryption logic
 *
 * 4. Re-encryption Phase:
 *    a. XOR the mutated payload with the same keystream to re-encrypt
 *    b. Calculate new HMAC-SHA256 over the encrypted payload using the mu key
 *    c. Reconstruct the complete packet with all components
 */

/**
 * BLINDED PAYLOAD SUPPORT:
 *
 * When generating/mutating blinded payloads, the mutator:
 * 1. Generates a random blinding point (path_key) - a valid secp256k1 public key
 * 2. Adds TLV type 12 (current_path_key) containing the blinding point
 * 3. Computes shared secret: ss = ECDH(node_private_key, blinding_point)
 * 4. Derives rho key: rho = HMAC-SHA256(key="rho", message=ss)
 * 5. Encrypts inner TLV payload with ChaCha20-Poly1305(key=rho, nonce=0)
 * 6. Adds TLV type 10 (encrypted_recipient_data) with the ciphertext
 *
 * The encrypted_recipient_data inner TLVs match LDK's actual format:
 *
 * ForwardTlvs:
 *   - TLV type 2: short_channel_id (u64) - next hop channel
 *   - TLV type 10: payment_relay - cltv_expiry_delta(u16) +
 *                  fee_proportional_millionths(u32) + fee_base_msat(tu32)
 *   - TLV type 12: payment_constraints - max_cltv_expiry(u32) +
 *                  htlc_minimum_msat(tu64)
 *   - TLV type 14: features (optional)
 *
 * ReceiveTlvs:
 *   - TLV type 12: payment_constraints
 *   - TLV type 65536: payment_secret (32 bytes)
 *   - TLV type 65537: payment_context
 *
 * DummyTlvs:
 *   - TLV type 10: payment_relay
 *   - TLV type 12: payment_constraints
 *   - TLV type 65539: is_dummy marker (empty)
 *
 * The mutator applies structure-aware mutations to these inner TLVs
 * (add/remove/update) before encrypting, testing the blinded path
 * decryption and validation logic in LDK.
 */

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <custommutator/utils/crypto/chacha20.h>
#include <custommutator/utils/crypto/chacha20poly1305.h>
#include <custommutator/utils/crypto/hmac_sha256.h>
#include <external/secp256k1/include/secp256k1.h>
#include <external/secp256k1/include/secp256k1_ecdh.h>
#include <vector>

extern "C" size_t LLVMFuzzerMutate(uint8_t *Data, size_t Size, size_t MaxSize);
extern "C" size_t LLVMFuzzerCustomMutator(uint8_t *fuzz_data, size_t size,
                                          size_t max_size, unsigned int seed);

// Default onion packet template: a valid TLV-encoded onion packet containing
// forwarding instructions. Used as the starting point for mutation-based
// fuzzing.
constexpr uint8_t default_onion[1398] = {
    0x70, 0xe9, 0x3e, 0xa1, 0x41, 0xe1, 0xfc, 0x67, 0x3e, 0x01, 0x7e, 0x97,
    0xea, 0xdc, 0x6b, 0x96, 0x8f, 0x38, 0x5c, 0x2a, 0xec, 0xb0, 0x3b, 0xfb,
    0x32, 0xaf, 0x3c, 0x54, 0xec, 0x18, 0xdb, 0x5c, 0x00, 0x03, 0x51, 0x8f,
    0xed, 0xd2, 0x78, 0x4e, 0x90, 0xea, 0xf4, 0xd4, 0x9c, 0x80, 0x8c, 0x47,
    0xb0, 0x8a, 0xa3, 0x0e, 0xcc, 0x05, 0x8c, 0x31, 0x57, 0xce, 0x72, 0xc0,
    0x66, 0x8f, 0x23, 0xa4, 0x1d, 0x7e, 0x5c, 0xc7, 0x63, 0x19, 0x3b, 0x26,
    0xf6, 0xeb, 0x83, 0x22, 0xfe, 0x75, 0xed, 0x36, 0xb8, 0xba, 0x7c, 0x8a,
    0x33, 0x39, 0xad, 0x51, 0xd5, 0xc3, 0xa8, 0x57, 0x2b, 0x84, 0xa7, 0x6c,
    0x66, 0xb3, 0x92, 0xd8, 0x45, 0x7f, 0x02, 0x31, 0xd8, 0x23, 0x78, 0x28,
    0x1f, 0x8a, 0x91, 0xf2, 0xbd, 0x1d, 0xbf, 0x1e, 0xa7, 0xab, 0xda, 0x5f,
    0x31, 0x63, 0x53, 0x8e, 0xee, 0x63, 0xc1, 0xb8, 0x8b, 0x5f, 0x67, 0x7f,
    0x22, 0xaf, 0xbe, 0x4e, 0x43, 0x3c, 0x36, 0x31, 0x02, 0x4d, 0x9e, 0x57,
    0x6c, 0x3c, 0x0d, 0x2b, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0xdb,
    0x96, 0xd6, 0xe0, 0xb7, 0x51, 0xa7, 0xd1, 0x5f, 0x01, 0x5c, 0x9d, 0x27,
    0xda, 0xeb, 0xed, 0x74, 0x63, 0xe3, 0x4c, 0x7d, 0xbc, 0xad, 0x59, 0xa8,
    0xd8, 0x47, 0x5a, 0xce, 0x6f, 0x33};

constexpr size_t KEY_SIZE = 32;
constexpr size_t PUBLIC_KEY_SIZE = 33;
constexpr size_t VERSION_SIZE = 1;
constexpr size_t HOP_PAYLOADS_SIZE = 1300;
constexpr size_t HMAC_SIZE = 32;

constexpr size_t PACKET_SIZE =
    KEY_SIZE + VERSION_SIZE + PUBLIC_KEY_SIZE + HOP_PAYLOADS_SIZE + HMAC_SIZE;

static_assert(std::size(default_onion) == PACKET_SIZE);

// Offsets within the packet structure
constexpr size_t PRIVATE_KEY_OFFSET = 0;
constexpr size_t VERSION_OFFSET = KEY_SIZE;
constexpr size_t PUBLIC_KEY_OFFSET = VERSION_OFFSET + VERSION_SIZE;
constexpr size_t HOP_PAYLOADS_OFFSET = PUBLIC_KEY_OFFSET + PUBLIC_KEY_SIZE;
constexpr size_t HMAC_OFFSET = HOP_PAYLOADS_OFFSET + HOP_PAYLOADS_SIZE;

// Key mutation probability
constexpr unsigned int KEY_MUTATION_PROBABILITY = 1; // 1% chance

// Payload mutation strategy probabilities (must sum to 100)
constexpr unsigned int STANDARD_MUTATION_PROBABILITY = 40;
constexpr unsigned int TLV_STRUCTURE_MUTATION_PROBABILITY = 40;
constexpr unsigned int BLINDED_PAYLOAD_PROBABILITY = 20;

constexpr unsigned int STANDARD_THRESHOLD = STANDARD_MUTATION_PROBABILITY;
constexpr unsigned int TLV_STRUCTURE_THRESHOLD =
    STANDARD_THRESHOLD + TLV_STRUCTURE_MUTATION_PROBABILITY;
constexpr unsigned int BLINDED_PAYLOAD_THRESHOLD =
    TLV_STRUCTURE_THRESHOLD + BLINDED_PAYLOAD_PROBABILITY;

static_assert(BLINDED_PAYLOAD_THRESHOLD == 100,
              "Mutation probabilities must sum to 100");

// ChaCha20-Poly1305 constants
constexpr size_t POLY1305_TAG_SIZE = 16;

// BigSize encoding constants for TLV format
constexpr uint8_t BIGSIZE_ONE_BYTE_MAX = 0xfc;
constexpr uint8_t BIGSIZE_TWO_BYTES = 0xfd;
constexpr uint8_t BIGSIZE_FOUR_BYTES = 0xfe;
constexpr uint8_t BIGSIZE_EIGHT_BYTES = 0xff;
constexpr uint16_t MIN_TWO_BYTE_VALUE = 0xfd;
constexpr uint16_t MIN_TLV_LENGTH = 2;
constexpr uint16_t MAX_TLV_LENGTH = 1265;

// --- Outer onion TLV types (standard hop payload) ---
constexpr uint64_t TLV_TYPE_AMT_TO_FORWARD = 2;
constexpr uint64_t TLV_TYPE_OUTGOING_CLTV = 4;
constexpr uint64_t TLV_TYPE_SHORT_CHANNEL_ID = 6;
constexpr uint64_t TLV_TYPE_PAYMENT_DATA = 8;
constexpr uint64_t TLV_TYPE_ENCRYPTED_RECIPIENT_DATA = 10;
constexpr uint64_t TLV_TYPE_CURRENT_PATH_KEY = 12;
constexpr uint64_t TLV_TYPE_TOTAL_AMOUNT_MSAT = 18;

// --- Inner blinded TLV types (encrypted_recipient_data) ---
// These match LDK's actual ForwardTlvs/ReceiveTlvs/DummyTlvs encoding.
constexpr uint64_t BLINDED_TLV_SHORT_CHANNEL_ID = 2;
constexpr uint64_t BLINDED_TLV_NEXT_TRAMPOLINE = 4;
constexpr uint64_t BLINDED_TLV_NEXT_BLINDING_OVERRIDE = 8;
constexpr uint64_t BLINDED_TLV_PAYMENT_RELAY = 10;
constexpr uint64_t BLINDED_TLV_PAYMENT_CONSTRAINTS = 12;
constexpr uint64_t BLINDED_TLV_FEATURES = 14;
constexpr uint64_t BLINDED_TLV_PAYMENT_SECRET = 65536;
constexpr uint64_t BLINDED_TLV_PAYMENT_CONTEXT = 65537;
constexpr uint64_t BLINDED_TLV_IS_DUMMY = 65539;

// Common outer TLV types for random selection
static const uint64_t COMMON_TLV_TYPES[] = {
    TLV_TYPE_AMT_TO_FORWARD,
    TLV_TYPE_OUTGOING_CLTV,
    TLV_TYPE_SHORT_CHANNEL_ID,
    TLV_TYPE_PAYMENT_DATA,
    TLV_TYPE_ENCRYPTED_RECIPIENT_DATA,
    TLV_TYPE_CURRENT_PATH_KEY,
    16,
    TLV_TYPE_TOTAL_AMOUNT_MSAT,
    5482373484};
constexpr size_t NUM_COMMON_TYPES = std::size(COMMON_TLV_TYPES);

// Inner blinded TLV types for random selection
static const uint64_t BLINDED_INNER_TLV_TYPES[] = {
    BLINDED_TLV_SHORT_CHANNEL_ID,
    BLINDED_TLV_NEXT_TRAMPOLINE,
    BLINDED_TLV_NEXT_BLINDING_OVERRIDE,
    BLINDED_TLV_PAYMENT_RELAY,
    BLINDED_TLV_PAYMENT_CONSTRAINTS,
    BLINDED_TLV_FEATURES,
    BLINDED_TLV_PAYMENT_SECRET,
    BLINDED_TLV_PAYMENT_CONTEXT,
    BLINDED_TLV_IS_DUMMY};
constexpr size_t NUM_BLINDED_INNER_TYPES = std::size(BLINDED_INNER_TLV_TYPES);

// Blinded payload variant for generation
enum class BlindedVariant : uint8_t {
  Forward = 0,
  Receive = 1,
  Dummy = 2,
  NumVariants = 3,
};

// Forward declarations
static void derive_key(const uint8_t *shared_secret, uint8_t *derived_key,
                       const char *key_type);
static bool compute_shared_secret(const uint8_t *private_key,
                                  const uint8_t *public_key_bytes,
                                  uint8_t *shared_secret);

// ---------------------------------------------------------------------------
// TLV record and hop payload structures
// ---------------------------------------------------------------------------

struct TLVRecord {
  uint64_t type;
  std::vector<uint8_t> value;

  size_t encoded_size() const {
    return bigsize_encoded_size(type) + bigsize_encoded_size(value.size()) +
           value.size();
  }

  static size_t bigsize_encoded_size(uint64_t val) {
    if (val <= BIGSIZE_ONE_BYTE_MAX)
      return 1;
    if (val <= 0xFFFF)
      return 3;
    if (val <= 0xFFFFFFFF)
      return 5;
    return 9;
  }
};

struct TLVHopPayload {
  size_t total_length;
  std::vector<TLVRecord> records;
  bool valid;
  size_t parse_end_offset;

  TLVHopPayload() : total_length(0), valid(false), parse_end_offset(0) {}
};

// ---------------------------------------------------------------------------
// secp256k1 context
// ---------------------------------------------------------------------------

static secp256k1_context *get_secp256k1_context() {
  static secp256k1_context *g_secp256k1_ctx = secp256k1_context_create(
      SECP256K1_CONTEXT_SIGN | SECP256K1_CONTEXT_VERIFY);
  return g_secp256k1_ctx;
}

// ---------------------------------------------------------------------------
// BigSize encoding / decoding
// ---------------------------------------------------------------------------

struct BigSizeResult {
  bool valid;
  uint64_t value;
  size_t bytes_read;
};

static BigSizeResult decode_bigsize(const uint8_t *data, size_t available) {
  BigSizeResult result = {false, 0, 0};

  if (available < 1)
    return result;

  uint8_t first = data[0];

  if (first <= BIGSIZE_ONE_BYTE_MAX) {
    result.valid = true;
    result.value = first;
    result.bytes_read = 1;
  } else if (first == BIGSIZE_TWO_BYTES) {
    if (available < 3)
      return result;
    result.value = (static_cast<uint64_t>(data[1]) << 8) | data[2];
    if (result.value >= MIN_TWO_BYTE_VALUE) {
      result.valid = true;
      result.bytes_read = 3;
    }
  } else if (first == BIGSIZE_FOUR_BYTES) {
    if (available < 5)
      return result;
    result.value = (static_cast<uint64_t>(data[1]) << 24) |
                   (static_cast<uint64_t>(data[2]) << 16) |
                   (static_cast<uint64_t>(data[3]) << 8) | data[4];
    if (result.value > 0xFFFF) {
      result.valid = true;
      result.bytes_read = 5;
    }
  } else if (first == BIGSIZE_EIGHT_BYTES) {
    if (available < 9)
      return result;
    result.value = (static_cast<uint64_t>(data[1]) << 56) |
                   (static_cast<uint64_t>(data[2]) << 48) |
                   (static_cast<uint64_t>(data[3]) << 40) |
                   (static_cast<uint64_t>(data[4]) << 32) |
                   (static_cast<uint64_t>(data[5]) << 24) |
                   (static_cast<uint64_t>(data[6]) << 16) |
                   (static_cast<uint64_t>(data[7]) << 8) | data[8];
    if (result.value > 0xFFFFFFFF) {
      result.valid = true;
      result.bytes_read = 9;
    }
  }

  return result;
}

static size_t encode_bigsize(uint8_t *dest, uint64_t value) {
  if (value <= BIGSIZE_ONE_BYTE_MAX) {
    dest[0] = static_cast<uint8_t>(value);
    return 1;
  } else if (value <= 0xFFFF) {
    dest[0] = BIGSIZE_TWO_BYTES;
    dest[1] = (value >> 8) & 0xFF;
    dest[2] = value & 0xFF;
    return 3;
  } else if (value <= 0xFFFFFFFF) {
    dest[0] = BIGSIZE_FOUR_BYTES;
    dest[1] = (value >> 24) & 0xFF;
    dest[2] = (value >> 16) & 0xFF;
    dest[3] = (value >> 8) & 0xFF;
    dest[4] = value & 0xFF;
    return 5;
  } else {
    dest[0] = BIGSIZE_EIGHT_BYTES;
    dest[1] = (value >> 56) & 0xFF;
    dest[2] = (value >> 48) & 0xFF;
    dest[3] = (value >> 40) & 0xFF;
    dest[4] = (value >> 32) & 0xFF;
    dest[5] = (value >> 24) & 0xFF;
    dest[6] = (value >> 16) & 0xFF;
    dest[7] = (value >> 8) & 0xFF;
    dest[8] = value & 0xFF;
    return 9;
  }
}

// ---------------------------------------------------------------------------
// TLV parsing and serialization
// ---------------------------------------------------------------------------

static TLVHopPayload parse_tlv_hop_payload(const uint8_t *data,
                                           size_t available) {
  TLVHopPayload payload;
  size_t offset = 0;

  if (available < 1)
    return payload;

  BigSizeResult length_result = decode_bigsize(data, available);
  if (!length_result.valid)
    return payload;

  if (length_result.value == 0) {
    payload.valid = false;
    return payload;
  }

  payload.total_length = length_result.value;
  offset = length_result.bytes_read;

  size_t tlv_end = offset + payload.total_length;
  if (tlv_end > available)
    tlv_end = available;

  uint64_t last_type = 0;
  bool first_record = true;

  while (offset < tlv_end) {
    BigSizeResult type_result = decode_bigsize(data + offset, tlv_end - offset);
    if (!type_result.valid)
      break;
    offset += type_result.bytes_read;

    if (!first_record && type_result.value <= last_type)
      break;
    last_type = type_result.value;
    first_record = false;

    if (offset >= tlv_end)
      break;
    BigSizeResult value_len_result =
        decode_bigsize(data + offset, tlv_end - offset);
    if (!value_len_result.valid)
      break;
    offset += value_len_result.bytes_read;

    if (value_len_result.value > tlv_end - offset)
      break;

    TLVRecord record;
    record.type = type_result.value;
    record.value.assign(data + offset, data + offset + value_len_result.value);
    payload.records.push_back(record);

    offset += value_len_result.value;
  }

  payload.valid = !payload.records.empty();
  payload.parse_end_offset = offset;

  return payload;
}

// Parse a raw TLV stream (no length prefix) into records
static std::vector<TLVRecord> parse_tlv_stream(const uint8_t *data,
                                                size_t available) {
  std::vector<TLVRecord> records;
  size_t offset = 0;
  uint64_t last_type = 0;
  bool first_record = true;

  while (offset < available) {
    BigSizeResult type_result =
        decode_bigsize(data + offset, available - offset);
    if (!type_result.valid)
      break;
    offset += type_result.bytes_read;

    if (!first_record && type_result.value <= last_type)
      break;
    last_type = type_result.value;
    first_record = false;

    if (offset >= available)
      break;
    BigSizeResult value_len_result =
        decode_bigsize(data + offset, available - offset);
    if (!value_len_result.valid)
      break;
    offset += value_len_result.bytes_read;

    if (value_len_result.value > available - offset)
      break;

    TLVRecord record;
    record.type = type_result.value;
    record.value.assign(data + offset, data + offset + value_len_result.value);
    records.push_back(record);

    offset += value_len_result.value;
  }

  return records;
}

// Serialize a raw TLV stream (no length prefix)
static std::vector<uint8_t>
serialize_tlv_stream(const std::vector<TLVRecord> &records) {
  std::vector<uint8_t> out;
  uint8_t buf[9];

  for (const auto &record : records) {
    size_t n = encode_bigsize(buf, record.type);
    out.insert(out.end(), buf, buf + n);

    n = encode_bigsize(buf, record.value.size());
    out.insert(out.end(), buf, buf + n);

    out.insert(out.end(), record.value.begin(), record.value.end());
  }

  return out;
}

static size_t serialize_tlv_hop_payload(const TLVHopPayload &payload,
                                        uint8_t *dest, size_t max_size) {
  size_t tlv_stream_size = 0;
  for (const auto &record : payload.records)
    tlv_stream_size += record.encoded_size();

  size_t length_prefix_size = TLVRecord::bigsize_encoded_size(tlv_stream_size);
  if (length_prefix_size > max_size)
    return 0;
  size_t offset = encode_bigsize(dest, tlv_stream_size);
  if (offset >= max_size)
    return 0;

  for (const auto &record : payload.records) {
    size_t type_size = TLVRecord::bigsize_encoded_size(record.type);
    if (offset + type_size > max_size)
      break;
    offset += encode_bigsize(dest + offset, record.type);

    size_t len_size = TLVRecord::bigsize_encoded_size(record.value.size());
    if (offset + len_size > max_size)
      break;
    offset += encode_bigsize(dest + offset, record.value.size());

    size_t value_to_copy = std::min(record.value.size(), max_size - offset);
    memcpy(dest + offset, record.value.data(), value_to_copy);
    offset += value_to_copy;

    if (offset >= max_size)
      break;
  }

  return offset;
}

// ---------------------------------------------------------------------------
// Random data helpers
// ---------------------------------------------------------------------------

static std::vector<uint8_t> generate_buffer(size_t size) {
  if (size == 0)
    return {};
  std::vector<uint8_t> vec(size);
  for (size_t i = 0; i < vec.size(); i++)
    vec[i] = static_cast<uint8_t>(rand() & 0xFF);
  LLVMFuzzerMutate(vec.data(), vec.size(), vec.size());
  return vec;
}

static std::vector<uint8_t> generate_tu_int(size_t max_bytes) {
  if (max_bytes == 0)
    return {0};
  size_t actual_bytes = 1 + (rand() % max_bytes);
  std::vector<uint8_t> result = generate_buffer(actual_bytes);

  // Strip leading zeros for minimal encoding (HighZeroBytesDroppedBigSize)
  while (result.size() > 1 && result[0] == 0)
    result.erase(result.begin());

  return result;
}

static uint64_t generate_random_tlv_type() {
  uint64_t value = 0;
  auto *bytes = reinterpret_cast<uint8_t *>(&value);
  for (size_t i = 0; i < sizeof(value); i++)
    bytes[i] = static_cast<uint8_t>(rand() & 0xFF);
  LLVMFuzzerMutate(bytes, sizeof(value), sizeof(value));
  return value;
}

static uint64_t mutate_tlv_type_value(uint64_t existing_type) {
  uint64_t value = existing_type;
  LLVMFuzzerMutate(reinterpret_cast<uint8_t *>(&value), sizeof(value),
                   sizeof(value));
  return value;
}

// ---------------------------------------------------------------------------
// Value generators for outer onion TLV types
// ---------------------------------------------------------------------------

static std::vector<uint8_t> generate_value_for_type(uint64_t type) {
  switch (type) {
  case TLV_TYPE_AMT_TO_FORWARD:
    return generate_tu_int(8);

  case TLV_TYPE_OUTGOING_CLTV:
    return generate_tu_int(4);

  case TLV_TYPE_SHORT_CHANNEL_ID:
    return generate_buffer(8);

  case TLV_TYPE_PAYMENT_DATA: {
    std::vector<uint8_t> value = generate_buffer(32);
    auto tu64 = generate_tu_int(8);
    value.insert(value.end(), tu64.begin(), tu64.end());
    return value;
  }

  case TLV_TYPE_CURRENT_PATH_KEY: {
    std::vector<uint8_t> value(33);
    value[0] = (rand() % 2) ? 0x02 : 0x03;
    for (size_t i = 1; i < 33; i++)
      value[i] = static_cast<uint8_t>(rand() & 0xFF);
    LLVMFuzzerMutate(value.data() + 1, 32, 32);
    return value;
  }

  case TLV_TYPE_TOTAL_AMOUNT_MSAT:
    return generate_tu_int(8);

  default: {
    constexpr size_t max_len = 256;
    std::vector<uint8_t> value(max_len);
    for (size_t i = 0; i < max_len; i++)
      value[i] = static_cast<uint8_t>(rand() & 0xFF);
    size_t seed_size = 1 + (rand() % max_len);
    size_t new_size = LLVMFuzzerMutate(value.data(), seed_size, max_len);
    value.resize(new_size);
    return value;
  }
  }
}

// ---------------------------------------------------------------------------
// Value generators for inner blinded TLV types (matching LDK encoding)
// ---------------------------------------------------------------------------

// PaymentRelay: cltv_expiry_delta(u16) + fee_proportional_millionths(u32) +
//               fee_base_msat(HighZeroBytesDroppedBigSize<u32>)
static std::vector<uint8_t> generate_payment_relay() {
  std::vector<uint8_t> value;

  // cltv_expiry_delta: u16 big-endian
  uint16_t cltv = static_cast<uint16_t>(rand());
  value.push_back((cltv >> 8) & 0xFF);
  value.push_back(cltv & 0xFF);

  // fee_proportional_millionths: u32 big-endian
  uint32_t fee_prop = static_cast<uint32_t>(rand());
  value.push_back((fee_prop >> 24) & 0xFF);
  value.push_back((fee_prop >> 16) & 0xFF);
  value.push_back((fee_prop >> 8) & 0xFF);
  value.push_back(fee_prop & 0xFF);

  // fee_base_msat: HighZeroBytesDroppedBigSize<u32> (truncated)
  auto fee_base = generate_tu_int(4);
  value.insert(value.end(), fee_base.begin(), fee_base.end());

  return value;
}

// PaymentConstraints: max_cltv_expiry(u32) +
//                     htlc_minimum_msat(HighZeroBytesDroppedBigSize<u64>)
static std::vector<uint8_t> generate_payment_constraints() {
  std::vector<uint8_t> value;

  // max_cltv_expiry: u32 big-endian
  uint32_t max_cltv = static_cast<uint32_t>(rand());
  value.push_back((max_cltv >> 24) & 0xFF);
  value.push_back((max_cltv >> 16) & 0xFF);
  value.push_back((max_cltv >> 8) & 0xFF);
  value.push_back(max_cltv & 0xFF);

  // htlc_minimum_msat: HighZeroBytesDroppedBigSize<u64> (truncated)
  auto htlc_min = generate_tu_int(8);
  value.insert(value.end(), htlc_min.begin(), htlc_min.end());

  return value;
}

// Generate a valid compressed public key (for next_blinding_override or
// next_trampoline)
static std::vector<uint8_t> generate_compressed_pubkey() {
  std::vector<uint8_t> value(33);
  value[0] = (rand() % 2) ? 0x02 : 0x03;
  for (size_t i = 1; i < 33; i++)
    value[i] = static_cast<uint8_t>(rand() & 0xFF);
  LLVMFuzzerMutate(value.data() + 1, 32, 32);
  return value;
}

static std::vector<uint8_t>
generate_blinded_inner_value_for_type(uint64_t type) {
  switch (type) {
  case BLINDED_TLV_SHORT_CHANNEL_ID:
    return generate_buffer(8);

  case BLINDED_TLV_NEXT_TRAMPOLINE:
    return generate_compressed_pubkey();

  case BLINDED_TLV_NEXT_BLINDING_OVERRIDE:
    return generate_compressed_pubkey();

  case BLINDED_TLV_PAYMENT_RELAY:
    return generate_payment_relay();

  case BLINDED_TLV_PAYMENT_CONSTRAINTS:
    return generate_payment_constraints();

  case BLINDED_TLV_FEATURES:
    // Empty or small feature bits
    if (rand() % 2 == 0)
      return {};
    return generate_buffer(1 + (rand() % 8));

  case BLINDED_TLV_PAYMENT_SECRET:
    return generate_buffer(32);

  case BLINDED_TLV_PAYMENT_CONTEXT: {
    // PaymentContext is a TLV-based enum: variant byte + encoded variant data
    // Variants: 1=Bolt12Offer, 2=Bolt12Refund, 3=AsyncBolt12Offer
    std::vector<uint8_t> value;
    uint8_t variant = 1 + (rand() % 3);
    value.push_back(variant);
    if (variant == 1) {
      // Bolt12OfferContext: offer_id(32) + invoice_request fields
      auto ctx = generate_buffer(32 + (rand() % 64));
      value.insert(value.end(), ctx.begin(), ctx.end());
    } else if (variant == 2) {
      // Bolt12RefundContext: empty struct
      // No additional data needed
    } else {
      // AsyncBolt12OfferContext: offer_nonce(16)
      auto nonce = generate_buffer(16);
      value.insert(value.end(), nonce.begin(), nonce.end());
    }
    return value;
  }

  case BLINDED_TLV_IS_DUMMY:
    return {}; // Empty value, just a marker

  default: {
    size_t len = rand() % 64;
    return generate_buffer(len);
  }
  }
}

// ---------------------------------------------------------------------------
// Blinding keypair generation
// ---------------------------------------------------------------------------

struct BlindingKeypair {
  uint8_t private_key[KEY_SIZE];
  uint8_t public_key[PUBLIC_KEY_SIZE];
  bool valid;
};

static BlindingKeypair generate_blinding_keypair() {
  BlindingKeypair result = {{0}, {0}, false};
  secp256k1_context *ctx = get_secp256k1_context();
  if (!ctx)
    return result;

  for (size_t i = 0; i < KEY_SIZE; i++)
    result.private_key[i] = static_cast<uint8_t>(rand() & 0xFF);
  LLVMFuzzerMutate(result.private_key, KEY_SIZE, KEY_SIZE);

  if (!secp256k1_ec_seckey_verify(ctx, result.private_key)) {
    result.private_key[0] = 0x01;
    for (size_t i = 1; i < KEY_SIZE - 1; i++)
      result.private_key[i] = static_cast<uint8_t>(rand() & 0xFF);
    result.private_key[KEY_SIZE - 1] = 0x01;
    if (!secp256k1_ec_seckey_verify(ctx, result.private_key))
      return result;
  }

  secp256k1_pubkey pubkey;
  if (!secp256k1_ec_pubkey_create(ctx, &pubkey, result.private_key))
    return result;

  size_t output_len = PUBLIC_KEY_SIZE;
  if (!secp256k1_ec_pubkey_serialize(ctx, result.public_key, &output_len,
                                     &pubkey, SECP256K1_EC_COMPRESSED))
    return result;

  result.valid = true;
  return result;
}

// ---------------------------------------------------------------------------
// Crypto helpers
// ---------------------------------------------------------------------------

static void derive_key(const uint8_t *shared_secret, uint8_t *derived_key,
                       const char *key_type) {
  size_t key_type_len = strlen(key_type);
  CHMAC_SHA256 hmac(reinterpret_cast<const unsigned char *>(key_type),
                    key_type_len);
  hmac.Write(shared_secret, KEY_SIZE);
  hmac.Finalize(derived_key);
}

struct DerivedKeys {
  uint8_t rho[KEY_SIZE];
  uint8_t mu[KEY_SIZE];
};

static void derive_all_keys(const uint8_t *shared_secret, DerivedKeys *keys) {
  derive_key(shared_secret, keys->rho, "rho");
  derive_key(shared_secret, keys->mu, "mu");
}

static bool compute_shared_secret(const uint8_t *private_key,
                                  const uint8_t *public_key_bytes,
                                  uint8_t *shared_secret) {
  secp256k1_context *ctx = get_secp256k1_context();
  if (!ctx)
    return false;

  secp256k1_pubkey public_key;
  if (!secp256k1_ec_pubkey_parse(ctx, &public_key, public_key_bytes,
                                 PUBLIC_KEY_SIZE))
    return false;

  if (!secp256k1_ecdh(ctx, shared_secret, &public_key, private_key, nullptr,
                      nullptr))
    return false;

  return true;
}

static void generate_keystream(const uint8_t *rho_key, uint8_t *keystream) {
  std::span<const std::byte> key_span(
      reinterpret_cast<const std::byte *>(rho_key), KEY_SIZE);

  ChaCha20 chacha(key_span);
  ChaCha20::Nonce96 nonce = {0, 0};
  chacha.Seek(nonce, 0);

  std::span<std::byte> keystream_span(reinterpret_cast<std::byte *>(keystream),
                                      HOP_PAYLOADS_SIZE);
  chacha.Keystream(keystream_span);
}

static void xor_buffers(uint8_t *dest, const uint8_t *src, const uint8_t *key,
                        size_t length) {
  for (size_t i = 0; i < length; i++)
    dest[i] = src[i] ^ key[i];
}

static void calculate_hmac(const uint8_t *mu_key, const uint8_t *payload,
                           size_t payload_size, uint8_t *hmac_output) {
  CHMAC_SHA256 hmac(mu_key, KEY_SIZE);
  hmac.Write(payload, payload_size);
  hmac.Finalize(hmac_output);
}

// Encrypt with ChaCha20-Poly1305 (for encrypted_recipient_data)
static std::vector<uint8_t>
encrypt_recipient_data(const uint8_t *rho_key,
                       const std::vector<uint8_t> &plaintext) {
  std::vector<uint8_t> ciphertext(plaintext.size() + POLY1305_TAG_SIZE);

  std::span<const std::byte> key_span(
      reinterpret_cast<const std::byte *>(rho_key), KEY_SIZE);
  AEADChaCha20Poly1305 aead(key_span);

  std::span<const std::byte> plain_span(
      reinterpret_cast<const std::byte *>(plaintext.data()), plaintext.size());
  std::span<std::byte> cipher_span(
      reinterpret_cast<std::byte *>(ciphertext.data()), ciphertext.size());

  AEADChaCha20Poly1305::Nonce96 nonce = {0, 0};
  std::span<const std::byte> empty_aad;

  aead.Encrypt(plain_span, empty_aad, nonce, cipher_span);

  return ciphertext;
}

// ---------------------------------------------------------------------------
// Standard (outer) TLV mutation
// ---------------------------------------------------------------------------

static void mutate_tlv_value(TLVRecord &record) {
  int strategy = rand() % 4;

  switch (strategy) {
  case 0:
    record.value = generate_value_for_type(record.type);
    break;
  default: {
    size_t old_size = record.value.size();
    record.value.resize(old_size + 32);
    size_t new_size =
        LLVMFuzzerMutate(record.value.data(), old_size, record.value.size());
    record.value.resize(new_size);
    break;
  }
  }
}

static void add_tlv_record(TLVHopPayload &payload) {
  TLVRecord new_record;

  if (rand() % 2 == 0) {
    new_record.type = COMMON_TLV_TYPES[rand() % NUM_COMMON_TYPES];
  } else {
    new_record.type = generate_random_tlv_type();
  }

  new_record.value = generate_value_for_type(new_record.type);

  auto it = payload.records.begin();
  while (it != payload.records.end() && it->type < new_record.type)
    ++it;

  payload.records.insert(it, new_record);
}

static void remove_tlv_record(TLVHopPayload &payload) {
  if (payload.records.size() > 1) {
    size_t idx = rand() % payload.records.size();
    payload.records.erase(payload.records.begin() + idx);
  }
}

static void mutate_tlv_type(TLVHopPayload &payload) {
  if (payload.records.empty())
    return;

  size_t idx = rand() % payload.records.size();
  int type_mutation = rand() % 4;

  switch (type_mutation) {
  case 0:
    payload.records[idx].type = COMMON_TLV_TYPES[rand() % NUM_COMMON_TYPES];
    break;
  case 1:
    payload.records[idx].type =
        mutate_tlv_type_value(payload.records[idx].type);
    break;
  case 2:
    payload.records[idx].type++;
    break;
  case 3:
    payload.records[idx].type--;
    break;
  }
}

static void mutate_tlv_structure(TLVHopPayload &payload) {
  int num_mutations = 1 + (rand() % 3);

  for (int i = 0; i < num_mutations; i++) {
    int mutation_type = rand() % 10;

    switch (mutation_type) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
      if (!payload.records.empty()) {
        size_t idx = rand() % payload.records.size();
        mutate_tlv_value(payload.records[idx]);
      }
      break;
    case 5:
    case 6:
    case 7:
      add_tlv_record(payload);
      break;
    case 8:
      remove_tlv_record(payload);
      break;
    case 9:
      mutate_tlv_type(payload);
      break;
    }
  }
}

static TLVHopPayload generate_new_tlv_payload() {
  TLVHopPayload payload;
  payload.valid = true;

  int num_records = 2 + (rand() % 4);

  TLVRecord amt_record;
  amt_record.type = TLV_TYPE_AMT_TO_FORWARD;
  amt_record.value = generate_value_for_type(TLV_TYPE_AMT_TO_FORWARD);
  payload.records.push_back(amt_record);

  TLVRecord cltv_record;
  cltv_record.type = TLV_TYPE_OUTGOING_CLTV;
  cltv_record.value = generate_value_for_type(TLV_TYPE_OUTGOING_CLTV);
  payload.records.push_back(cltv_record);

  for (int i = 2; i < num_records; i++)
    add_tlv_record(payload);

  auto last = std::unique(
      payload.records.begin(), payload.records.end(),
      [](const TLVRecord &a, const TLVRecord &b) { return a.type == b.type; });
  payload.records.erase(last, payload.records.end());

  return payload;
}

// ---------------------------------------------------------------------------
// Inner blinded TLV mutation (structure-aware)
// ---------------------------------------------------------------------------

// Mutate a single inner blinded TLV record's value
static void mutate_blinded_inner_value(TLVRecord &record) {
  int strategy = rand() % 4;

  switch (strategy) {
  case 0:
    // Regenerate with correct format for known blinded types
    record.value = generate_blinded_inner_value_for_type(record.type);
    break;
  default: {
    // Raw fuzzer mutation
    size_t old_size = record.value.size();
    record.value.resize(old_size + 32);
    size_t new_size =
        LLVMFuzzerMutate(record.value.data(), old_size, record.value.size());
    record.value.resize(new_size);
    break;
  }
  }
}

// Add a new record to a blinded inner TLV stream
static void add_blinded_inner_record(std::vector<TLVRecord> &records) {
  TLVRecord new_record;

  if (rand() % 3 < 2) {
    new_record.type =
        BLINDED_INNER_TLV_TYPES[rand() % NUM_BLINDED_INNER_TYPES];
  } else {
    new_record.type = generate_random_tlv_type();
  }

  new_record.value = generate_blinded_inner_value_for_type(new_record.type);

  auto it = records.begin();
  while (it != records.end() && it->type < new_record.type)
    ++it;

  records.insert(it, new_record);
}

// Remove a record from a blinded inner TLV stream
static void remove_blinded_inner_record(std::vector<TLVRecord> &records) {
  if (records.size() > 1) {
    size_t idx = rand() % records.size();
    records.erase(records.begin() + idx);
  }
}

// Mutate a record's type in a blinded inner TLV stream
static void mutate_blinded_inner_type(std::vector<TLVRecord> &records) {
  if (records.empty())
    return;

  size_t idx = rand() % records.size();
  int type_mutation = rand() % 4;

  switch (type_mutation) {
  case 0:
    records[idx].type =
        BLINDED_INNER_TLV_TYPES[rand() % NUM_BLINDED_INNER_TYPES];
    break;
  case 1:
    records[idx].type = mutate_tlv_type_value(records[idx].type);
    break;
  case 2:
    records[idx].type++;
    break;
  case 3:
    records[idx].type--;
    break;
  }
}

// Duplicate a record (creates ordering violations or duplicate types)
static void duplicate_blinded_inner_record(std::vector<TLVRecord> &records) {
  if (records.empty())
    return;

  size_t idx = rand() % records.size();
  TLVRecord dup = records[idx];

  // Insert at random position
  size_t insert_pos = rand() % (records.size() + 1);
  records.insert(records.begin() + insert_pos, dup);
}

// Structure-aware mutation of inner blinded TLV records
static void
mutate_blinded_inner_tlv_structure(std::vector<TLVRecord> &records) {
  int num_mutations = 1 + (rand() % 3);

  for (int i = 0; i < num_mutations; i++) {
    int mutation_type = rand() % 12;

    switch (mutation_type) {
    case 0:
    case 1:
    case 2:
    case 3:
      // Mutate a record's value (33%)
      if (!records.empty()) {
        size_t idx = rand() % records.size();
        mutate_blinded_inner_value(records[idx]);
      }
      break;
    case 4:
    case 5:
    case 6:
      // Add a new record (25%)
      add_blinded_inner_record(records);
      break;
    case 7:
    case 8:
      // Remove a record (17%)
      remove_blinded_inner_record(records);
      break;
    case 9:
      // Mutate type field (8%)
      mutate_blinded_inner_type(records);
      break;
    case 10:
      // Duplicate a record (8%)
      duplicate_blinded_inner_record(records);
      break;
    case 11:
      // Swap two records (ordering violation) (8%)
      if (records.size() >= 2) {
        size_t a = rand() % records.size();
        size_t b = rand() % records.size();
        if (a != b)
          std::swap(records[a], records[b]);
      }
      break;
    }
  }
}

// ---------------------------------------------------------------------------
// Blinded payload generation (per LDK variant)
// ---------------------------------------------------------------------------

// Generate ForwardTlvs inner records: scid(2) + relay(10) + constraints(12)
// + optional features(14) + optional next_blinding_override(8)
static std::vector<TLVRecord> generate_forward_inner_records() {
  std::vector<TLVRecord> records;

  TLVRecord scid;
  scid.type = BLINDED_TLV_SHORT_CHANNEL_ID;
  scid.value = generate_buffer(8);
  records.push_back(scid);

  TLVRecord relay;
  relay.type = BLINDED_TLV_PAYMENT_RELAY;
  relay.value = generate_payment_relay();
  records.push_back(relay);

  TLVRecord constraints;
  constraints.type = BLINDED_TLV_PAYMENT_CONSTRAINTS;
  constraints.value = generate_payment_constraints();
  records.push_back(constraints);

  if (rand() % 3 == 0) {
    TLVRecord features;
    features.type = BLINDED_TLV_FEATURES;
    features.value = generate_buffer(1 + (rand() % 4));
    records.push_back(features);
  }

  if (rand() % 4 == 0) {
    TLVRecord override_key;
    override_key.type = BLINDED_TLV_NEXT_BLINDING_OVERRIDE;
    override_key.value = generate_compressed_pubkey();
    // Insert in sorted position
    auto it = records.begin();
    while (it != records.end() && it->type < override_key.type)
      ++it;
    records.insert(it, override_key);
  }

  return records;
}

// Generate ReceiveTlvs inner records: constraints(12) + secret(65536) +
// context(65537)
static std::vector<TLVRecord> generate_receive_inner_records() {
  std::vector<TLVRecord> records;

  TLVRecord constraints;
  constraints.type = BLINDED_TLV_PAYMENT_CONSTRAINTS;
  constraints.value = generate_payment_constraints();
  records.push_back(constraints);

  TLVRecord secret;
  secret.type = BLINDED_TLV_PAYMENT_SECRET;
  secret.value = generate_buffer(32);
  records.push_back(secret);

  TLVRecord context;
  context.type = BLINDED_TLV_PAYMENT_CONTEXT;
  context.value = generate_blinded_inner_value_for_type(BLINDED_TLV_PAYMENT_CONTEXT);
  records.push_back(context);

  return records;
}

// Generate DummyTlvs inner records: relay(10) + constraints(12) +
// is_dummy(65539)
static std::vector<TLVRecord> generate_dummy_inner_records() {
  std::vector<TLVRecord> records;

  TLVRecord relay;
  relay.type = BLINDED_TLV_PAYMENT_RELAY;
  relay.value = generate_payment_relay();
  records.push_back(relay);

  TLVRecord constraints;
  constraints.type = BLINDED_TLV_PAYMENT_CONSTRAINTS;
  constraints.value = generate_payment_constraints();
  records.push_back(constraints);

  TLVRecord dummy_marker;
  dummy_marker.type = BLINDED_TLV_IS_DUMMY;
  dummy_marker.value = {}; // Empty
  records.push_back(dummy_marker);

  return records;
}

// Generate inner records for a specific blinded variant
static std::vector<TLVRecord>
generate_blinded_inner_records(BlindedVariant variant) {
  switch (variant) {
  case BlindedVariant::Forward:
    return generate_forward_inner_records();
  case BlindedVariant::Receive:
    return generate_receive_inner_records();
  case BlindedVariant::Dummy:
    return generate_dummy_inner_records();
  default:
    return generate_forward_inner_records();
  }
}

// ---------------------------------------------------------------------------
// Blinded payload: encrypt inner TLVs and build outer payload
// ---------------------------------------------------------------------------

// Build the outer TLV hop payload containing encrypted_recipient_data and
// current_path_key, plus standard forwarding fields.
static TLVHopPayload
build_blinded_outer_payload(const uint8_t *recipient_private_key,
                            const std::vector<uint8_t> &inner_tlv_stream) {
  TLVHopPayload payload;
  payload.valid = true;

  // Generate blinding keypair
  BlindingKeypair blinding = generate_blinding_keypair();
  if (!blinding.valid) {
    return generate_new_tlv_payload(); // Fallback
  }

  // Compute shared secret: ECDH(recipient_private_key, blinding_pubkey)
  uint8_t shared_secret[KEY_SIZE];
  if (!compute_shared_secret(recipient_private_key, blinding.public_key,
                             shared_secret)) {
    return generate_new_tlv_payload(); // Fallback
  }

  // Derive rho for inner encryption
  uint8_t rho[KEY_SIZE];
  derive_key(shared_secret, rho, "rho");

  // Encrypt inner TLV stream
  std::vector<uint8_t> encrypted_data =
      encrypt_recipient_data(rho, inner_tlv_stream);

  // Build outer records
  TLVRecord amt;
  amt.type = TLV_TYPE_AMT_TO_FORWARD;
  amt.value = generate_value_for_type(TLV_TYPE_AMT_TO_FORWARD);
  payload.records.push_back(amt);

  TLVRecord cltv;
  cltv.type = TLV_TYPE_OUTGOING_CLTV;
  cltv.value = generate_value_for_type(TLV_TYPE_OUTGOING_CLTV);
  payload.records.push_back(cltv);

  TLVRecord enc_data;
  enc_data.type = TLV_TYPE_ENCRYPTED_RECIPIENT_DATA;
  enc_data.value = encrypted_data;
  payload.records.push_back(enc_data);

  TLVRecord path_key;
  path_key.type = TLV_TYPE_CURRENT_PATH_KEY;
  path_key.value.assign(blinding.public_key,
                        blinding.public_key + PUBLIC_KEY_SIZE);
  payload.records.push_back(path_key);

  // Sort by type
  std::sort(
      payload.records.begin(), payload.records.end(),
      [](const TLVRecord &a, const TLVRecord &b) { return a.type < b.type; });

  return payload;
}

// Generate a fresh blinded TLV payload with a random variant
static TLVHopPayload
generate_blinded_tlv_payload(const uint8_t *recipient_private_key) {
  auto variant = static_cast<BlindedVariant>(
      rand() % static_cast<uint8_t>(BlindedVariant::NumVariants));

  std::vector<TLVRecord> inner_records =
      generate_blinded_inner_records(variant);
  std::vector<uint8_t> inner_stream = serialize_tlv_stream(inner_records);

  return build_blinded_outer_payload(recipient_private_key, inner_stream);
}

// Mutate an existing blinded payload's inner TLVs.
// Decrypts, parses inner TLVs, mutates them, re-encrypts.
// If the payload doesn't have encrypted_recipient_data, generates fresh.
static TLVHopPayload
mutate_blinded_tlv_payload(const uint8_t *recipient_private_key,
                           TLVHopPayload &existing_payload) {
  // Find the encrypted_recipient_data and current_path_key records
  TLVRecord *enc_data_record = nullptr;
  TLVRecord *path_key_record = nullptr;

  for (auto &record : existing_payload.records) {
    if (record.type == TLV_TYPE_ENCRYPTED_RECIPIENT_DATA)
      enc_data_record = &record;
    if (record.type == TLV_TYPE_CURRENT_PATH_KEY)
      path_key_record = &record;
  }

  // If no existing blinded data, generate fresh
  if (!enc_data_record || !path_key_record ||
      path_key_record->value.size() != PUBLIC_KEY_SIZE) {
    return generate_blinded_tlv_payload(recipient_private_key);
  }

  // Compute shared secret using existing path_key
  uint8_t shared_secret[KEY_SIZE];
  if (!compute_shared_secret(recipient_private_key,
                             path_key_record->value.data(), shared_secret)) {
    return generate_blinded_tlv_payload(recipient_private_key);
  }

  uint8_t rho[KEY_SIZE];
  derive_key(shared_secret, rho, "rho");

  // Attempt to decrypt the encrypted_recipient_data
  // Format: ciphertext(N-16 bytes) + poly1305_tag(16 bytes)
  if (enc_data_record->value.size() <= POLY1305_TAG_SIZE) {
    // Too small to contain valid data, generate fresh
    return generate_blinded_tlv_payload(recipient_private_key);
  }

  size_t ciphertext_len =
      enc_data_record->value.size() - POLY1305_TAG_SIZE;
  std::vector<uint8_t> plaintext(ciphertext_len);

  std::span<const std::byte> key_span(
      reinterpret_cast<const std::byte *>(rho), KEY_SIZE);
  AEADChaCha20Poly1305 aead(key_span);

  std::span<const std::byte> cipher_span(
      reinterpret_cast<const std::byte *>(enc_data_record->value.data()),
      enc_data_record->value.size());
  std::span<std::byte> plain_span(
      reinterpret_cast<std::byte *>(plaintext.data()), plaintext.size());

  AEADChaCha20Poly1305::Nonce96 nonce = {0, 0};
  std::span<const std::byte> empty_aad;

  bool decrypted = aead.Decrypt(cipher_span, empty_aad, nonce, plain_span);

  std::vector<TLVRecord> inner_records;

  if (decrypted) {
    // Parse existing inner TLVs
    inner_records = parse_tlv_stream(plaintext.data(), plaintext.size());
  }

  if (inner_records.empty()) {
    // Decryption or parsing failed; generate fresh inner records
    auto variant = static_cast<BlindedVariant>(
        rand() % static_cast<uint8_t>(BlindedVariant::NumVariants));
    inner_records = generate_blinded_inner_records(variant);
  }

  // Apply structure-aware mutations to inner records
  mutate_blinded_inner_tlv_structure(inner_records);

  // Serialize mutated inner TLVs
  std::vector<uint8_t> inner_stream = serialize_tlv_stream(inner_records);

  // Re-encrypt with same key (same path_key)
  std::vector<uint8_t> new_encrypted =
      encrypt_recipient_data(rho, inner_stream);

  // Update the encrypted_recipient_data in the existing payload
  enc_data_record->value = new_encrypted;

  // Optionally mutate outer records too (20% chance)
  if (rand() % 5 == 0) {
    for (auto &record : existing_payload.records) {
      if (record.type != TLV_TYPE_ENCRYPTED_RECIPIENT_DATA &&
          record.type != TLV_TYPE_CURRENT_PATH_KEY) {
        if (rand() % 3 == 0)
          mutate_tlv_value(record);
      }
    }
  }

  return existing_payload;
}

// ---------------------------------------------------------------------------
// Packet construction
// ---------------------------------------------------------------------------

static size_t build_template_packet(uint8_t *fuzz_data, size_t max_size) {
  if (max_size < PACKET_SIZE)
    return 0;
  memcpy(fuzz_data, default_onion, PACKET_SIZE);
  return PACKET_SIZE;
}

// ---------------------------------------------------------------------------
// Main custom mutator entry point
// ---------------------------------------------------------------------------

size_t LLVMFuzzerCustomMutator(uint8_t *fuzz_data, size_t size, size_t max_size,
                               unsigned int seed) {
  if (size < PACKET_SIZE)
    return build_template_packet(fuzz_data, max_size);

  srand(seed);

  // Optionally mutate keys
  bool should_mutate_keys =
      static_cast<unsigned int>(rand() % 100) < KEY_MUTATION_PROBABILITY;
  if (should_mutate_keys) {
    LLVMFuzzerMutate(fuzz_data + PRIVATE_KEY_OFFSET, KEY_SIZE, KEY_SIZE);
    LLVMFuzzerMutate(fuzz_data + PUBLIC_KEY_OFFSET, PUBLIC_KEY_SIZE,
                     PUBLIC_KEY_SIZE);
  }

  // Step 1: Compute shared secret via ECDH
  uint8_t shared_secret[KEY_SIZE];
  if (!compute_shared_secret(fuzz_data + PRIVATE_KEY_OFFSET,
                             fuzz_data + PUBLIC_KEY_OFFSET, shared_secret))
    return size;

  // Step 2: Derive encryption and authentication keys
  DerivedKeys keys;
  derive_all_keys(shared_secret, &keys);

  // Step 3: Generate ChaCha20 keystream
  uint8_t keystream[HOP_PAYLOADS_SIZE];
  generate_keystream(keys.rho, keystream);

  // Step 4: Decrypt hop payloads
  uint8_t decrypted_payload[HOP_PAYLOADS_SIZE] = {0};
  xor_buffers(decrypted_payload, fuzz_data + HOP_PAYLOADS_OFFSET, keystream,
              HOP_PAYLOADS_SIZE);

  // Step 5: Choose mutation strategy
  unsigned int mutation_choice = rand() % 100;

  if (mutation_choice < STANDARD_THRESHOLD) {
    // Strategy 1: Standard raw mutation (40%)
    LLVMFuzzerMutate(decrypted_payload, HOP_PAYLOADS_SIZE, HOP_PAYLOADS_SIZE);

  } else if (mutation_choice < TLV_STRUCTURE_THRESHOLD) {
    // Strategy 2: Structure-aware outer TLV mutation (40%)
    TLVHopPayload parsed =
        parse_tlv_hop_payload(decrypted_payload, HOP_PAYLOADS_SIZE);

    if (parsed.valid && !parsed.records.empty()) {
      mutate_tlv_structure(parsed);
      size_t serialized_size = serialize_tlv_hop_payload(
          parsed, decrypted_payload, HOP_PAYLOADS_SIZE);
      if (serialized_size < HOP_PAYLOADS_SIZE)
        memset(decrypted_payload + serialized_size, 0,
               HOP_PAYLOADS_SIZE - serialized_size);
    } else {
      TLVHopPayload new_payload = generate_new_tlv_payload();
      size_t serialized_size = serialize_tlv_hop_payload(
          new_payload, decrypted_payload, HOP_PAYLOADS_SIZE);
      if (serialized_size < HOP_PAYLOADS_SIZE)
        memset(decrypted_payload + serialized_size, 0,
               HOP_PAYLOADS_SIZE - serialized_size);
    }

  } else {
    // Strategy 3: Blinded payload mutation (20%)
    // Sub-strategies: generate fresh (40%) or mutate existing (60%)
    TLVHopPayload blinded_payload;

    bool try_mutate_existing = (rand() % 5) >= 2; // 60% mutate existing

    if (try_mutate_existing) {
      TLVHopPayload parsed =
          parse_tlv_hop_payload(decrypted_payload, HOP_PAYLOADS_SIZE);
      if (parsed.valid && !parsed.records.empty()) {
        blinded_payload = mutate_blinded_tlv_payload(
            fuzz_data + PRIVATE_KEY_OFFSET, parsed);
      } else {
        blinded_payload =
            generate_blinded_tlv_payload(fuzz_data + PRIVATE_KEY_OFFSET);
      }
    } else {
      blinded_payload =
          generate_blinded_tlv_payload(fuzz_data + PRIVATE_KEY_OFFSET);
    }

    size_t serialized_size = serialize_tlv_hop_payload(
        blinded_payload, decrypted_payload, HOP_PAYLOADS_SIZE);
    if (serialized_size < HOP_PAYLOADS_SIZE)
      memset(decrypted_payload + serialized_size, 0,
             HOP_PAYLOADS_SIZE - serialized_size);
  }

  // Step 6: Re-encrypt
  uint8_t encrypted_payload[HOP_PAYLOADS_SIZE] = {0};
  xor_buffers(encrypted_payload, decrypted_payload, keystream,
              HOP_PAYLOADS_SIZE);

  // Step 7: Calculate HMAC
  uint8_t hmac[HMAC_SIZE];
  calculate_hmac(keys.mu, encrypted_payload, HOP_PAYLOADS_SIZE, hmac);

  // Step 8: Reconstruct packet
  memcpy(fuzz_data + HOP_PAYLOADS_OFFSET, encrypted_payload, HOP_PAYLOADS_SIZE);
  memcpy(fuzz_data + HMAC_OFFSET, hmac, HMAC_SIZE);
  return PACKET_SIZE;
}