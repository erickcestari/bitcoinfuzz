package main

/*
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    char* data;
    int length;
} ByteArray;
*/
import "C"

import (
	"bytes"
	"encoding/binary"
	"fmt"
	"runtime"
	"strings"
	"unsafe"

	"github.com/btcsuite/btcd/chaincfg"
	"github.com/lightningnetwork/lnd/lnwire"
	"github.com/lightningnetwork/lnd/netann"
	"github.com/lightningnetwork/lnd/zpay32"
)

//export LndDeserializeInvoice
func LndDeserializeInvoice(cInvoiceStr *C.char) *C.char {
	if cInvoiceStr == nil {
		return C.CString("")
	}

	runtime.GC()

	// Convert C string to Go string
	invoiceStr := C.GoString(cInvoiceStr)

	network := &chaincfg.MainNetParams

	invoice, err := zpay32.Decode(invoiceStr, network)
	if err != nil {
		return C.CString("")
	}

	var sb strings.Builder

	sb.WriteString("HASH=")
	if invoice.PaymentHash != nil {
		sb.WriteString(fmt.Sprintf("%x", *invoice.PaymentHash))
	}

	sb.WriteString(";PAYMENT_SECRET=")
	invoice.PaymentAddr.WhenSome(func(paymentAddr [32]byte) {
		sb.WriteString(fmt.Sprintf("%x", paymentAddr))
	})

	sb.WriteString(";AMOUNT=")
	if invoice.MilliSat != nil {
		// Simulate uint64 overflow behavior for compatibility with all implementations.
		// LND uses milliSatoshis (10^-11 BTC) and does not overflow when handling very large values.
		// However, other implementations like LDK, which use picoBTC (10^-12 BTC), may overflow when parsing
		// extremely large amounts (e.g., >95M BTC). To simulate this behavior, we multiply and divide by 10.
		// This cancels out the value mathematically but mimics the overflow behavior that would occur in those
		// implementations. This is especially relevant for values exceeding Bitcoin’s 21M BTC cap—
		// which should be considered invalid—but must be handled in a consistent way across implementations
		// to avoid parsing errors.
		amountOverflow := (*invoice.MilliSat * 10) / 10
		sb.WriteString(fmt.Sprintf("%d", amountOverflow))
	} else {
		sb.WriteString("0")
	}
	sb.WriteString(";DESCRIPTION=")
	if invoice.Description != nil {
		sb.WriteString(*invoice.Description)
	}

	sb.WriteString(";METADATA=")
	if invoice.Metadata != nil {
		sb.WriteString(fmt.Sprintf("%x", invoice.Metadata))
	}

	sb.WriteString(";RECIPIENT=")
	if invoice.Destination != nil {
		sb.WriteString(fmt.Sprintf("%x", invoice.Destination.SerializeCompressed()))
	}

	sb.WriteString(";DESCRIPTION_HASH=")
	if invoice.DescriptionHash != nil {
		sb.WriteString(fmt.Sprintf("%x", *invoice.DescriptionHash))
	}

	// Convert expiry from time.Duration to seconds as uint64 to ensure consistent
	// overflow behavior across implementations. LND uses signed int64 for expiry in
	// nanoseconds, while other implementations use uint64.
	sb.WriteString(";EXPIRY=")
	sb.WriteString(fmt.Sprintf("%d", uint64(invoice.Expiry().Nanoseconds())/1000000000))

	sb.WriteString(";TIMESTAMP=")
	sb.WriteString(fmt.Sprintf("%d", invoice.Timestamp.Unix()))

	sb.WriteString(";FALLBACK_ADDRESS=")
	if invoice.FallbackAddr != nil {
		sb.WriteString(invoice.FallbackAddr.String())
	}

	for _, routeHint := range invoice.RouteHints {
		sb.WriteString(";PRIVATE_ROUTE=[")
		for i, hopHint := range routeHint {
			if i == 0 {
				sb.WriteString("(")
			} else {
				sb.WriteString(",(")
			}
			sb.WriteString("NODE_ID=")
			sb.WriteString(fmt.Sprintf("%x", hopHint.NodeID.SerializeCompressed()))
			sb.WriteString(",SHORT_CHANNEL_ID=")
			sb.WriteString(fmt.Sprintf("%d", hopHint.ChannelID))
			sb.WriteString(",FEES=")
			sb.WriteString(fmt.Sprintf("%d", hopHint.FeeBaseMSat))
			sb.WriteString(",CLTV_EXPIRY_DELTA=")
			sb.WriteString(fmt.Sprintf("%d", hopHint.CLTVExpiryDelta))
			sb.WriteString(",PROPORTIONAL_MILLIONTHS=")
			sb.WriteString(fmt.Sprintf("%d", hopHint.FeeProportionalMillionths))
			sb.WriteString(")")
		}
		sb.WriteString("]")
	}

	sb.WriteString(";MIN_CLTV=")
	sb.WriteString(fmt.Sprintf("%d", invoice.MinFinalCLTVExpiry()))

	sb.WriteString(";FEATURES=")
	var buf bytes.Buffer
	if err := invoice.Features.RawFeatureVector.EncodeBase256(&buf); err == nil {
		sb.WriteString(fmt.Sprintf("%x", buf.Bytes()))
	}

	return C.CString(sb.String())
}

//export LndDeserializeGossip
func LndDeserializeGossip(data C.ByteArray) *C.char {
	buffer := C.GoBytes(unsafe.Pointer(data.data), data.length)
	r := bytes.NewReader(buffer)

	var mType [2]byte
	if _, err := r.ReadAt(mType[:], 0); err != nil {
		return C.CString("")
	}

	// Routing (types 256-511): messages containing node and channel announcements,
	// as well as any active route exploration (described in BOLT #7)
	// https://github.com/lightning/bolts/blob/master/01-messaging.md#lightning-message-format
	msgType := binary.BigEndian.Uint16(mType[:])
	if msgType < 256 || msgType > 511 {
		return C.CString("")
	}

	message, err := lnwire.ReadMessage(r, 0)
	if err != nil {
		// Others implementations (like LDK and C-lightning) don't require the
		// short channel IDs to be sorted, so we'll return null if we get this error.
		if strings.Contains(err.Error(), "isn't greater than last sid") {
			return (*C.char)(unsafe.Pointer(nil))
		}

		if msgType == 264 && strings.Contains(err.Error(), "unexpected EOF") {
			return (*C.char)(unsafe.Pointer(nil))
		}

		if msgType == 264 && strings.Contains(err.Error(), "tlv stream is not canonical") {
			return (*C.char)(unsafe.Pointer(nil))
		}

		if msgType == 264 && strings.Contains(err.Error(), "decoded varint is not canonical") {
			return (*C.char)(unsafe.Pointer(nil))
		}

		if msgType == 264 && strings.Contains(err.Error(), "unsupported encoding:") {
			return (*C.char)(unsafe.Pointer(nil))
		}

		if msgType == 264 && strings.Contains(err.Error(), "record is too large") {
			return (*C.char)(unsafe.Pointer(nil))
		}

		fmt.Println("error reading message")
		fmt.Println(err.Error())
		return C.CString("")
	}

	switch message.MsgType() {
	case 256:
	case 257:
	case 258:
	case 261:
	case 262:
	case 263:
	case 264:
	case 265:
		break
	default:
		return (*C.char)(unsafe.Pointer(nil))
	}

	if message.MsgType() == 256 {
		err := netann.ValidateChannelAnn(message.(*lnwire.ChannelAnnouncement1), nil)
		if err != nil {
			return C.CString("")
		}
	}

	if message.MsgType() == 257 {
		err := netann.ValidateNodeAnn(message.(*lnwire.NodeAnnouncement))
		if err != nil {
			return C.CString("")
		}
	}

	if message.MsgType() == 258 {
		if !message.(*lnwire.ChannelUpdate1).MessageFlags.HasMaxHtlc() {
			return C.CString("")
		}

		// Validate signature, but LND has a more strict check so skip it.
		_, err := message.(*lnwire.ChannelUpdate1).Signature.ToSignature()
		if err != nil {
			return (*C.char)(unsafe.Pointer(nil))
		}
	}

	if message.MsgType() == 261 {
		if len(message.(*lnwire.QueryShortChanIDs).ExtraData) != 0 {
			return (*C.char)(unsafe.Pointer(nil))
		}

		if len(message.(*lnwire.QueryShortChanIDs).ShortChanIDs) == 0 {
			return (*C.char)(unsafe.Pointer(nil))
		}

		// LND supports Zlib compression (which is deprecated), so let's skip this case
		if message.(*lnwire.QueryShortChanIDs).EncodingType != lnwire.EncodingSortedPlain {
			return (*C.char)(unsafe.Pointer(nil))
		}
	}

	if message.MsgType() == 262 {
		if len(message.(*lnwire.ReplyShortChanIDsEnd).ExtraData) != 0 {
			return (*C.char)(unsafe.Pointer(nil))
		}

		// LDK returns error when complete > 1
		if message.(*lnwire.ReplyShortChanIDsEnd).Complete > 1 {
			return (*C.char)(unsafe.Pointer(nil))
		}
	}

	if message.MsgType() == 263 {
		// LND accepts non-tlv extra data.
		// C-lightning accpets only tlv extra data.
		// rust-lightning does not accept extra data.
		if len(message.(*lnwire.QueryChannelRange).ExtraData) != 0 {
			return (*C.char)(unsafe.Pointer(nil))
		}
	}

	if message.MsgType() == 264 {
		if len(message.(*lnwire.ReplyChannelRange).ExtraData) != 0 {
			return (*C.char)(unsafe.Pointer(nil))
		}

		if len(message.(*lnwire.ReplyChannelRange).ShortChanIDs) == 0 {
			return (*C.char)(unsafe.Pointer(nil))
		}

		// LND supports Zlib compression (which is deprecated), so let's skip this case
		if message.(*lnwire.ReplyChannelRange).EncodingType != lnwire.EncodingSortedPlain {
			return (*C.char)(unsafe.Pointer(nil))
		}

	}

	if message.MsgType() == 265 {
		if len(message.(*lnwire.GossipTimestampRange).ExtraData) != 0 {
			return (*C.char)(unsafe.Pointer(nil))
		}
	}

	if message.MsgType() == 259 {
		if len(message.(*lnwire.AnnounceSignatures1).ExtraOpaqueData) != 0 {
			return (*C.char)(unsafe.Pointer(nil))
		}
	}

	var sb strings.Builder
	sb.WriteString(fmt.Sprintf("%d", message.MsgType()))

	return C.CString(sb.String())
}

func main() {}
