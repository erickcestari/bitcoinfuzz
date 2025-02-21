using System.Runtime.InteropServices;

namespace NLightning.CppBridge.Bolts.BOLT11;

using NLightning.Bolts.BOLT11;
using Common.Managers;
using Common.Types;

public static class InvoiceBridge
{
    [UnmanagedCallersOnly(EntryPoint = "DecodeInvoice")]
    public static bool DecodeInvoice(IntPtr utf8StringPtr)
    {
        try
        {
            var invoiceString = Marshal.PtrToStringUTF8(utf8StringPtr);
            if (invoiceString is null)
            {
                Console.WriteLine("invoiceString is null");
                return false;
            }
            // Console.WriteLine($"invoiceString is {invoiceString}");

            var invoice = Invoice.Decode(invoiceString);
            Console.WriteLine($"Invoice is real: {invoice.AmountMilliSats}");
            return true;
        }
        catch
        {
            return false;
        }
    }
}