using System.Runtime.InteropServices;
using System.Text;

namespace NLightning.CppBridge.Bolts.BOLT11;

using NLightning.Bolts.BOLT11;
using Common.Managers;
using Common.Types;

public static class InvoiceBridge
{
    [UnmanagedCallersOnly(EntryPoint = "DecodeInvoice")]
    public static bool DecodeInvoice(IntPtr utf8StringPtr, int length)
    {
        try
        {
            unsafe
            {
                Span<byte> managedBytes = new Span<byte>((void*)utf8StringPtr, length);
                var invoiceString = Encoding.UTF8.GetString(managedBytes);
                if (invoiceString is null)
                {
                    return false;
                }

                var invoice = Invoice.Decode(invoiceString);
                Console.WriteLine($"Invoice is real: {invoice.AmountMilliSats}");
                return true;
            }
        }
        catch
        {
            return false;
        }
    }
}