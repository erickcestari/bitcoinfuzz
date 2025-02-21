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
	"unsafe"

	"github.com/lightningnetwork/lnd/channeldb"
)

//export LndDeserializeInvoice
func LndDeserializeInvoice(invoiceData C.ByteArray) C.int {
	if invoiceData.length <= 0 {
		return 0
	}

	invoiceBytes := C.GoBytes(unsafe.Pointer(invoiceData.data), invoiceData.length)
	if len(invoiceBytes) == 0 {
		return 0
	}

	invoiceReader := bytes.NewReader(invoiceBytes)

	_, err := channeldb.DeserializeInvoice(invoiceReader)
	if err != nil {
		return 0
	}

	return 1
}

func main() {}
