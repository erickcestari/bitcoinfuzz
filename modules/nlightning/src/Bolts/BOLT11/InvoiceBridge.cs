using System.Runtime.InteropServices;

namespace NLightning.CppBridge.Bolts.BOLT11;

using System.Text;
using NLightning.Bolts.BOLT11;
public static class InvoiceBridge
{
    [UnmanagedCallersOnly(EntryPoint = "DecodeInvoice")]
    public static IntPtr DecodeInvoice(IntPtr invoiceStringPtr)
    {
        try
        {
            string? invoiceString = Marshal.PtrToStringUTF8(invoiceStringPtr);
            if (string.IsNullOrEmpty(invoiceString))
            {
                return IntPtr.Zero;
            }

            string result = string.Empty;
            Invoice invoice = Invoice.Decode(invoiceString);

            result += "HASH=" + invoice.PaymentHash;

            result += ";AMOUNT=" + invoice.AmountMilliSats;

            result += ";DESCRIPTION=" + invoice.Description;

            result += ";RECIPIENT=" + invoice.PayeePubKey;

            result += ";EXPIRY=" + (int)(invoice.ExpiryDate - DateTimeOffset.FromUnixTimeSeconds(invoice.Timestamp)).TotalSeconds;

            result += ";TIMESTAMP=" + invoice.Timestamp;

            result += ";ROUTING_HINTS=" + (invoice.RoutingInfos?.Count ?? 0);

            result += ";MIN_CLTV=" + invoice.MinFinalCltvExpiry;

            // Manually allocate unmanaged memory for the UTF-8 string
            byte[] resultBytes = Encoding.UTF8.GetBytes(result);
            IntPtr resultPtr = Marshal.AllocHGlobal(resultBytes.Length + 1); // +1 for null terminator

            // Copy the UTF-8 bytes to unmanaged memory
            Marshal.Copy(resultBytes, 0, resultPtr, resultBytes.Length);

            // Null-terminate the string
            Marshal.WriteByte(resultPtr + resultBytes.Length, 0);

            return resultPtr;
        }
        catch
        {
            return IntPtr.Zero;
        }
    }

    [UnmanagedCallersOnly(EntryPoint = "FreeString")]
    public static void FreeString(IntPtr stringPtr)
    {
        if (stringPtr != IntPtr.Zero)
        {
            Marshal.FreeHGlobal(stringPtr);
        }
    }

    [UnmanagedCallersOnly(EntryPoint = "CleanupResources")]
    public static void CleanupResources()
    {
        // Force garbage collection to clean up any managed resources
        GC.Collect(GC.MaxGeneration, GCCollectionMode.Forced, true, true);
        GC.WaitForPendingFinalizers();

        // Run a second collection to clean up finalizers
        GC.Collect(GC.MaxGeneration, GCCollectionMode.Forced, true, true);
        GC.WaitForPendingFinalizers();
    }
}