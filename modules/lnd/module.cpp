#include <span>

#include "module.h"
#include "lnd_wrapper/libscript.h"

namespace bitcoinfuzz
{
    namespace module
    {
        Lnd::Lnd(void) : BaseModule("Lnd") {}

        std::optional<std::string> deserialize_invoice(std::span<const uint8_t> buffer)
        {
            // Print the buffer
            for (auto byte : buffer)
            {
                std::cout << byte;
            }
            std::cout << std::endl;
            

            // TBD
            return std::nullopt;
        }

    } // namespace module
} // namespace bitcoinfuzz  
