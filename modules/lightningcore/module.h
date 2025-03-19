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
            std::optional<bool> deserialize_invoice(std::string str) const override;
            ~LightningCore() noexcept override = default;
        };

    }
}