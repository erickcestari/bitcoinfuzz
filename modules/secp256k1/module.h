#include <optional>
#include <span>
#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <bitcoinfuzz/basemodule.h>

namespace bitcoinfuzz
{
    namespace module
    {
        class Secp256k1 : public BaseModule
        {
        public:
            Secp256k1(void);
            std::optional<std::string> fuzz_secp256k1(std::span<const uint8_t> buffer) const override;
            ~Secp256k1() noexcept override = default;
        };

    }
}
