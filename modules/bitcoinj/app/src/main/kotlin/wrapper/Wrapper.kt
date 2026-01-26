package wrapper

import org.bitcoinj.base.BitcoinNetwork
import org.bitcoinj.crypto.HDKeyDerivation
import org.bitcoinj.crypto.MnemonicCode

object Wrapper {
    @JvmStatic external fun init(): Unit

    /**
     * JNI entry point. Takes raw entropy bytes and returns a serialized master private key (Base58).
     * If the seed is too short, we return an empty string so C++ can treat it as "skip".
     */
    @JvmStatic
    fun createMasterKey(seed: ByteArray): String {
        return try {
            // Derive master private key
            val key = HDKeyDerivation.createMasterPrivateKey(seed)

            // Serialize using BitcoinJ logic
            key.serializePrivB58(BitcoinNetwork.MAINNET)
        } catch (e: Exception) {
            // BitcoinJ throws for seeds shorter than 16 bytes
            if (e.message?.contains("seed is too short and could be brute forced") == true) {
                "skip error"
            } else {
                ""
            }
        }
    }

    /**
     * JNI entry point. Takes a mnemonic string and returns the derived seed as hex.
     * Returns "INVALID" if the mnemonic is not valid.
     */
    @JvmStatic
    fun mnemonicToSeed(mnemonic: String): String {
        return try {
            val words = mnemonic.trim().split("\\s+".toRegex())
            MnemonicCode.INSTANCE.check(words)
            val seed = MnemonicCode.toSeed(words, "")
            seed.joinToString("") { "%02x".format(it) }
        } catch (e: Exception) {
            "INVALID"
        }
    }
}
