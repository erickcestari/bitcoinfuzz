#include <optional>
#include <span>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <bitcoinfuzz/basemodule.h>

namespace bitcoinfuzz
{
    namespace module
    {
        typedef bool (*DecodeInvoiceFunc)(void *);

        class NLightning : public BaseModule
        {
        public:
            NLightning(void);
            std::optional<bool> deserialize_invoice(std::span<const uint8_t> buffer) const override;
            ~NLightning() noexcept override = default;

        private:
            static DecodeInvoiceFunc decodeInvoice;
        };

    }
}