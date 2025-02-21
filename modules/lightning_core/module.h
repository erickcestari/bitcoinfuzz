#include <optional>
#include <span>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <bitcoinfuzz/basemodule.h>

namespace bitcoinfuzz
{
    namespace module
    {
        class LightningCore : public BaseModule
        {
        public:
            LightningCore(void);
            std::optional<std::string> deserialize_invoice(std::span<const uint8_t> buffer) const override;
            ~LightningCore() noexcept override = default;
        };
    }
}