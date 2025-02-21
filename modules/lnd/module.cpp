#include <span>

#include "module.h"
#include "lnd_wrapper/libscript.h"

namespace bitcoinfuzz
{
    namespace module
    {
        Lnd::Lnd(void) : BaseModule("Lnd") {}

        std::optional<std::string> Lnd::deserialize_invoice(std::span<const uint8_t> buffer) const
        {
            // TBD
            return std::nullopt;
        }

    } // namespace module
} // namespace bitcoinfuzz  
