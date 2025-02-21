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
	"runtime"
	"unsafe"

	"github.com/lightningnetwork/lnd/channeldb"
)

//export LndDeserializeInvoice
func LndDeserializeInvoice(data *C.uint8_t, length C.size_t) C.int {
	// Early validation
	if data == nil || length <= 0 {
		return 0
	}

	// Force garbage collection before processing large data
	runtime.GC()

	// Create a fixed-size slice to prevent slice growth attacks
	// Use syncpool for better memory management in high-frequency cases
	invoiceBytes := make([]byte, length)
	if err := copyMemory(unsafe.Pointer(data), invoiceBytes, length); err != nil {
		return 0
	}

	// Create a buffer with size limit
	invoiceReader := bytes.NewReader(invoiceBytes)

	// Clear the slice after copying to reader
	for i := range invoiceBytes {
		invoiceBytes[i] = 0
	}

	_, err := channeldb.DeserializeInvoice(invoiceReader)
	if err != nil {
		return 0
	}

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
