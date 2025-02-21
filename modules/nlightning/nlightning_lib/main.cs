using System;
using System.Runtime.InteropServices;
using System.Text;
using NLightning.Bolts.BOLT11;

public static class NativeMethods
{
    [UnmanagedCallersOnly(EntryPoint = "nlightning_des_invoice")]
    public static IntPtr deserialize_invoice(IntPtr data, UIntPtr len)
    {
        if (data == IntPtr.Zero || len == UIntPtr.Zero)
        {
            return IntPtr.Zero;
        }

        try
        {
            // Converter ponteiro de dados para string UTF-8
            byte[] dataSlice = new byte[(int)len];
            Marshal.Copy(data, dataSlice, 0, (int)len);
            string invoiceStr = Encoding.UTF8.GetString(dataSlice);

            // Decodificar a invoice usando NLightning.Bolt11
            var invoice = Invoice.Decode(invoiceStr);
            string res = $"{invoice.Encode()}";

            // Retorna a string alocada na heap (precisa ser liberada pelo chamador)
            return StringToCString(res);
        }
        catch
        {
            return IntPtr.Zero;
        }
    }

    private static IntPtr StringToCString(string input)
    {
        byte[] bytes = Encoding.UTF8.GetBytes(input + '\0'); // Adiciona o terminador null
        IntPtr ptr = Marshal.AllocHGlobal(bytes.Length);
        Marshal.Copy(bytes, 0, ptr, bytes.Length);
        return ptr;
    }
}
