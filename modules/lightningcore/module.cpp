#include <span>

#include "module.h"
#include "lightningcore_wrapper/lightningcore_lib.h"

namespace bitcoinfuzz
{
    namespace module
    {
        LightningCore::LightningCore(void) : BaseModule("LightningCore") {}

        std::optional<bool> LightningCore::deserialize_invoice(std::string str) const
        {
            bool result = lightningcore_des_invoice(str.c_str());
            return result;
        }

    }
}
