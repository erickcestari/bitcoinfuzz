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
func LndDeserializeInvoice(invoiceData C.ByteArray) *C.char {
	if invoiceData.length <= 0 {
		return nil
	}

	invoiceBytes := C.GoBytes(unsafe.Pointer(invoiceData.data), invoiceData.length)
	if len(invoiceBytes) == 0 {
		return nil
	}

	invoiceReader := bytes.NewReader(invoiceBytes)

	invoice, err := channeldb.DeserializeInvoice(invoiceReader)
	if err != nil {
		return nil
	}

	writter := new(bytes.Buffer)
	err = channeldb.SerializeInvoice(writter, &invoice)
	if err != nil {
		return nil
	}

	result := C.CString(writter.String())
	return result
}

func main() {}
