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
            ByteArray data{
                .data = reinterpret_cast<char *>(const_cast<uint8_t *>(buffer.data())),
                .length = static_cast<int>(buffer.size())};
            bool result = LndDeserializeInvoice(data);
            printf("LndDeserializeInvoice: %d\n", result);
            return result;
        }

    }
}
