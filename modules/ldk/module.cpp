#include <span>

#include "module.h"

extern "C" bool ldk_des_invoice(const uint8_t *data, size_t len);

namespace bitcoinfuzz
{
    namespace module
    {
        Ldk::Ldk(void) : BaseModule("Ldk") {}

        std::optional<bool> Ldk::deserialize_invoice(std::span<const uint8_t> buffer) const
        {
            bool result = ldk_des_invoice(buffer.data(), buffer.size());
            return result;
        }

    }
}
