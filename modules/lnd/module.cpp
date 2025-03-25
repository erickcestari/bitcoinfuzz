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
            LndFreeString(result);
            return result_str;
        }
    }
}
