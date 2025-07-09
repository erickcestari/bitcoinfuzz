import fr.acinq.eclair.payment.Bolt11Invoice;
import scala.util.Try;
import scala.util.Success;
import scala.util.Failure;
import scala.Option;
import scala.collection.immutable.List;
import fr.acinq.eclair.MilliSatoshi;
import fr.acinq.bitcoin.scalacompat.ByteVector32;

public class Bolt11InvoiceWrapper {

  /**
   * Main method for testing
   */
  public static void main(String[] args) {
    String invoiceString = "lnbc1p5xulcdpp5ykra0q8k8trc7z6dyvwmw9j27rqcrx7r88sazf7nmvcq08q7756qdqqcqzzsxqrrs0fppq0r4w9z7gejeza9uu64928404y4dzumuksp57z2v4dxxt90k6533v9mqf4k7r2mkkcmvzz34zlv7k8vcj4nvkr5q9qxpqysgqtgaapt0dqcj7h4pswafftwwleu8t3x888rw9x4d6x49w03cqk4wjqax9pw5r0m0ptqx44yrqqh4nlgmduzlem8c7mzlp7vh8sluuctcpgszzer";

    String result = decodeBolt11Invoice(invoiceString);

    if (!result.isEmpty()) {
      System.out.println("Decoded invoice:");
      System.out.println(result);
    } else {
      System.out.println("Failed to decode invoice");
    }
  }

  /**
   * Decodes a BOLT11 invoice and returns all values in a formatted string.
   * This method is designed to be called from other languages via JNI or direct
   * Java calls.
   * 
   * @param invoiceString The BOLT11 invoice string to decode
   * @return Formatted string with all invoice values, or empty string if parsing
   *         fails
   */
  public static String decodeBolt11Invoice(String invoiceString) {
    try {
      Try<Bolt11Invoice> result = Bolt11Invoice.fromString(invoiceString);

      if (!result.isSuccess()) {
        System.out.println("Failed to parse invoice");
        return "";
      }

      Bolt11Invoice invoice = result.get();

      StringBuilder sb = new StringBuilder();

      sb.append("HASH=").append(invoice.paymentHash());

      sb.append(";AMOUNT=");
      Option<MilliSatoshi> amountOpt = invoice.amount_opt();
      if (amountOpt.isDefined()) {
        sb.append(amountOpt.get());
      } else {
        sb.append("0");
      }

      sb.append(";DESCRIPTION=");
      Object desc = invoice.description(); // returns scala.Either<String, ByteVector32>

      if (desc instanceof scala.util.Left) {
        String text = (String) ((scala.util.Left<?, ?>) desc).value();
        sb.append(text);
      } else if (desc instanceof scala.util.Right) {
        ByteVector32 hash = (ByteVector32) ((scala.util.Right<?, ?>) desc).value();
        sb.append("HASH:").append(hash);
      } else {
        sb.append("INVALID_DESCRIPTION");
      }

      sb.append(";RECIPIENT=").append(invoice.nodeId().toString());

      sb.append(";EXPIRY=").append(invoice.relativeExpiry().toSeconds());

      sb.append(";TIMESTAMP=").append(invoice.createdAt());

      sb.append(";PAYMENT_SECRET=").append(invoice.paymentSecret());

      sb.append(";ROUTING_HINTS=").append(invoice.routingInfo().size());

      sb.append(";MIN_CLTV=").append(invoice.minFinalCltvExpiryDelta());

      Option<String> fallbackAddr = invoice.fallbackAddress();
      sb.append(";FALLBACK_ADDRESS=");
      if (fallbackAddr.isDefined()) {
        sb.append(fallbackAddr.get());
      } else {
        sb.append("");
      }

      sb.append(";PAYMENT_METADATA=");
      Option<scodec.bits.ByteVector> metadata = invoice.paymentMetadata();
      if (metadata.isDefined()) {
        sb.append(metadata.get().toHex());
      } else {
        sb.append("");
      }

      sb.append(";FEATURES=").append(invoice.features().toByteVector().toHex());

      return sb.toString();

    } catch (Exception e) {
      System.err.println("Error decoding invoice: " + e.getMessage());
      return "";
    }
  }
}