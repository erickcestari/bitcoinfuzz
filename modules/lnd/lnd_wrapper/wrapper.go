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
	// "log"
	"runtime"
	"unsafe"

	"github.com/btcsuite/btcd/chaincfg"
	"github.com/lightningnetwork/lnd/zpay32"
)


//export LndDeserializeInvoice
func LndDeserializeInvoice(data *C.uint8_t, length C.size_t) C.int {
	if data == nil || length == 0 {
		return 0
	}

	runtime.GC()

	invoiceBytes := C.GoBytes(unsafe.Pointer(data), C.int(length))
	invoiceStr := string(invoiceBytes)

	network := &chaincfg.MainNetParams

	_, err := zpay32.Decode(invoiceStr, network)
	if err != nil {
		return 0
	}

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
