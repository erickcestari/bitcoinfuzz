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
            ByteArray data{
                .data = reinterpret_cast<char *>(const_cast<uint8_t *>(buffer.data())),
                .length = static_cast<int>(buffer.size())};
            char *result = LndDeserializeInvoice(data);
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
