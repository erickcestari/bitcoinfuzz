package main

/*
#include <stdint.h>
#include <stdlib.h>
*/
import "C"

import (
	"fmt"
	"runtime"
	"unsafe"

	"github.com/btcsuite/btcd/chaincfg"
	"github.com/lightningnetwork/lnd/zpay32"
)

//export LndDeserializeInvoice
func LndDeserializeInvoice(cInvoiceStr *C.char) *C.char {
	if cInvoiceStr == nil {
		return C.CString("0")
	}

	runtime.GC()

	// Convert C string to Go string
	invoiceStr := C.GoString(cInvoiceStr)

	network := &chaincfg.MainNetParams

	invoice, err := zpay32.Decode(invoiceStr, network)
	if err != nil {
		return C.CString("0")
	}

	var result string

	result += "HASH="
	if invoice.PaymentHash != nil {
		result += fmt.Sprintf("%x", *invoice.PaymentHash)
	}
	result += ";AMOUNT="
	if invoice.MilliSat != nil {
		result += fmt.Sprintf("%d", *invoice.MilliSat)
	}
	result += ";DESCRIPTION="
	if invoice.Description != nil {
		result += fmt.Sprintf("%s", *invoice.Description)
	}
	result += ";RECIPIENT="
	if invoice.Destination != nil {
		result += fmt.Sprintf("%x", invoice.Destination.SerializeCompressed())
	}
	result += ";EXPIRY="
	if invoice.Expiry() > 0 {
		result += fmt.Sprintf("%d", int64(invoice.Expiry().Seconds()))
	}
	result += ";TIMESTAMP="
	result += fmt.Sprintf("%d", invoice.Timestamp.Unix())

	result += fmt.Sprintf(";ROUTING_HINTS=%d", len(invoice.RouteHints))

	result += ";MIN_CLTV="
	if invoice.MinFinalCLTVExpiry() > 0 {
		result += fmt.Sprintf("%d", invoice.MinFinalCLTVExpiry())
	}

	return C.CString(result)
}

//export LndFreeString
func LndFreeString(ptr *C.char) {
	if ptr != nil {
		C.free(unsafe.Pointer(ptr))
	}
}

func main() {}
