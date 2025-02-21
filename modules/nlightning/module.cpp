#include <span>
#include <iostream>
#include <cstring>
#include <dlfcn.h>
#include <cstdlib>

#include "module.h"

namespace bitcoinfuzz
{
    namespace module
    {
        DecodeInvoiceFunc NLightning::decodeInvoice = nullptr;

        NLightning::NLightning(void) : BaseModule("NLightning")
        {
            void *libHandle = dlopen("./modules/nlightning/src/bin/NLightning.CppBridge.dylib", RTLD_NOW);
            if (!libHandle)
            {
                std::cerr << "Failed to load NLightning.Bolts.dylib: " << dlerror() << std::endl;
                return;
            }

            if (decodeInvoice == nullptr)
                decodeInvoice = (DecodeInvoiceFunc)dlsym(libHandle, "DecodeInvoice");

            if (!decodeInvoice)
            {
                std::cerr << "Failed to find one or more symbols: " << dlerror() << std::endl;
                dlclose(libHandle);
                return;
            }
        }

        std::optional<bool> NLightning::deserialize_invoice(std::span<const uint8_t> buffer) const
        {
            return decodeInvoice(buffer.data(), (int)buffer.size());
        }
    }
}
