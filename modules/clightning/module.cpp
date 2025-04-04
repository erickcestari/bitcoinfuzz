#include <span>

#include "module.h"
#include "clightning_lib.h"

namespace bitcoinfuzz
{
    namespace module
    {
        CLightning::CLightning(void) : BaseModule("CLightning") {}

        std::optional<std::string> CLightning::deserialize_invoice(std::string str) const
        {
            bool result = clightning_des_invoice(str.c_str());
            return result ? "true" : "false";
        }

    }
}