#include <span>

#include "module.h"
#include "lnd_wrapper/libscript.h"

namespace bitcoinfuzz
{
    namespace module
    {
        Lnd::Lnd(void) : BaseModule("Lnd") {}

        std::optional<std::string> Lnd::deserialize_invoice(std::string str) const
        {
            auto result = LndDeserializeInvoice(str.c_str());
            std::string result_str(result);
            free(result);
            return result_str;
        }

        std::optional<std::string> Lnd::parse_gossip_message(std::span<const uint8_t> buffer) const
        {
            ByteArray message;
            message.data = (char*)buffer.data();
            message.length = buffer.size();
            auto result = LndDeserializeGossip(message);
            if (result == nullptr) {
                return std::nullopt;
            }
            std::string result_str(result);
            free(result);
            return result_str;
        }
    }
}
