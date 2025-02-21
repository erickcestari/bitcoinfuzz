#include <span>

#include "module.h"

extern "C" char *nlightning_des_invoice(const uint8_t *data, size_t len);

namespace bitcoinfuzz
{
    namespace module
    {
        NLightning::NLightning(void) : BaseModule("NLightning") {}

        std::optional<std::string> NLightning::deserialize_invoice(std::span<const uint8_t> buffer) const
        {
            char *result = nlightning_des_invoice(buffer.data(), buffer.size());
            if (result == nullptr)
            {
                return std::nullopt;
            }
            std::string invoice_str{result};
            free(result);
            return invoice_str;
        }

    }
}
