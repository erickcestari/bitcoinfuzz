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
        class NBitcoin : public BaseModule
        {
        public:
            NBitcoin(void);
            std::optional<bool> miniscript_parse(std::string str) const override;
            std::optional<bool> descriptor_parse(std::string str) const override;
            std::optional<std::vector<bool>> deserialize_block(std::span<const uint8_t> buffer)const override;
            ~NBitcoin() noexcept override = default;
        };
    }
}