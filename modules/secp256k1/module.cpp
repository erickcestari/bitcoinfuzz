#include <span>
#include "module.h"
#include <secp256k1.h>
#include <secp256k1_recovery.h>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <cassert>

namespace bitcoinfuzz
{
    namespace module
    {
        Secp256k1::Secp256k1(void) : BaseModule("Secp256k1") {}

        std::optional<std::string> Secp256k1::fuzz_secp256k1(std::span<const uint8_t> buffer) const
        {
            if (buffer.size() < 97) {
                return std::nullopt;
            }

            secp256k1_context* ctx = secp256k1_context_create(SECP256K1_CONTEXT_VERIFY);
            if (!ctx) {
                return std::nullopt;
            }

            unsigned char message[32];
            unsigned char sig[64];
            int recid;

            std::memcpy(message, buffer.data(), 32);
            std::memcpy(sig, buffer.data() + 32, 64);
            recid = buffer[96] % 4;

            std::stringstream result;
            
            result << "Hash: ";
            for (int i = 0; i < 32; i++) {
                result << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)message[i];
            }
            result << "\n";

            result << "Signature: ";
            for (int i = 0; i < 64; i++) {
                result << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)sig[i];
            }
            result << "\n";

            result << "r value: ";
            for (int i = 0; i < 32; i++) {
                result << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)sig[i];
            }
            result << "\n";
            
            result << "s value: ";
            for (int i = 32; i < 64; i++) {
                result << std::hex << std::setfill('0') << std::setw(2) << (unsigned int)sig[i];
            }
            result << "\n";
            
            result << std::dec << "Recovery ID: " << recid << "\n";

            secp256k1_ecdsa_signature signature;
            secp256k1_ecdsa_recoverable_signature rsignature;
            secp256k1_pubkey recpubkey;

            int parse_result = secp256k1_ecdsa_recoverable_signature_parse_compact(ctx, &rsignature, sig, recid);
            result << "Parse result: " << parse_result << "\n";
            
            if (parse_result != 1) {
                secp256k1_context_destroy(ctx);
                return result.str();
            }

            int recovery_result = secp256k1_ecdsa_recover(ctx, &recpubkey, &rsignature, message);
            result << "Recovery result: " << recovery_result << "\n";
            if (recovery_result == 1) {
                int convert_result = secp256k1_ecdsa_recoverable_signature_convert(ctx, &signature, &rsignature);
                result << "Convert result: " << convert_result << "\n";
                if (convert_result == 1) {
                    int verification_result = secp256k1_ecdsa_verify(ctx, &signature, message, &recpubkey);
                    result << "Verification result: " << verification_result << "\n";
                    
                    // Panic if recovery succeeded but verification failed
                    if (verification_result != 1) {
                        result << "WARNING: Recovery succeeded but verification failed!\n";
                        std::cout << result.str();
                        assert(false);
                    }
                }
            }

            secp256k1_context_destroy(ctx);
            return result.str();
        }
    }
}