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
	// "fmt"
	"log"
	"runtime"
	"unsafe"

	"github.com/btcsuite/btcd/chaincfg"
	"github.com/lightningnetwork/lnd/zpay32"
)


//export LndDeserializeInvoice
func LndDeserializeInvoice(data *C.uint8_t, length C.size_t) C.int {
	// Early validation
	if data == nil || length == 0 {
		return 0
	}

	// Force garbage collection before processing
	runtime.GC()

	// Convert C data to Go slice
	invoiceBytes := C.GoBytes(unsafe.Pointer(data), C.int(length))
	invoiceStr := string(invoiceBytes)

	// Specify the Bitcoin network (e.g., mainnet, testnet, regtest)
	network := &chaincfg.MainNetParams

	// Decode the invoice with the correct network parameters
	_/*invoice*/, err := zpay32.Decode(invoiceStr, network)
	if err != nil {
		log.Printf("Invoice decoding failed: %v\n", err)
		return 0
	}

	// Print decoded details
	// fmt.Println("Invoice Details:")
	// fmt.Println("Amount (msat):", invoice.MilliSat)
	// fmt.Println("Description:", invoice.Description)
	// fmt.Println("Expiry:", invoice.Expiry())
	// fmt.Println("Destination Public Key:", invoice.Destination.SerializeCompressed())

	// Force cleanup
	runtime.GC()

	return 1
}

// copyMemory safely copies memory from a C pointer to a Go slice
func copyMemory(src unsafe.Pointer, dest []byte, length C.size_t) error {
	if int(length) > len(dest) {
		return error(nil) // Return generic error
	}

	// Copy memory safely
	for i := 0; i < int(length); i++ {
		ptr := unsafe.Pointer(uintptr(src) + uintptr(i))
		dest[i] = *(*byte)(ptr)
	}

	return nil
}

func main() {}
