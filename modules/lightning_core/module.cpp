#include <span>
#include "module.h"

extern "C" char *lightning_core_des_invoice(const uint8_t *data, size_t len);

namespace bitcoinfuzz
{
    namespace module
    {
        LightningCore::LightningCore(void) : BaseModule("LightningCore") {}

        std::optional<std::string> LightningCore::deserialize_invoice(std::span<const uint8_t> buffer) const
        {
            char *result = lightning_core_des_invoice(buffer.data(), buffer.size());
            if (result == nullptr)
            {
                return std::nullopt;
            }
            std::string invoice_str{result};
            free(result); // Free the C string
            return invoice_str;
        }
    }
}