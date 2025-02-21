#include <span>

#include "module.h"
#include "lnd_wrapper/libscript.h"

namespace bitcoinfuzz
{
    namespace module
    {
        Lnd::Lnd(void) : BaseModule("Lnd") {}

        std::optional<bool> Lnd::deserialize_invoice(std::span<const uint8_t> buffer) const
        {
            bool result = LndDeserializeInvoice(buffer.data(), buffer.size());
            return result;
        }

    }
}
