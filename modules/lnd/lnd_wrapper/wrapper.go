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
	"io"
	"unsafe"
	"bytes"
	_ "unsafe" // Required for go:linkname
	_ "github.com/lightningnetwork/lnd/channeldb" // Ensure it's linked	
	_ "github.com/lightningnetwork/lnd/invoices"
)

//go:linkname deserializeInvoice github.com/lightningnetwork/lnd/channeldb.deserializeInvoice
func deserializeInvoice(r io.Reader)


//go:linkname serializeInvoice github.com/lightningnetwork/lnd/channeldb.serializeInvoice
func serializeInvoice(r io.Reader)

//export LndDeserializeInvoice	
func LndDeserializeInvoice(invoiceData C.ByteArray) C.char {
	invoiceBytes := C.GoBytes(unsafe.Pointer(invoiceData.data), invoiceData.length)
	invoiceReader := bytes.NewReader(invoiceBytes)

	deserializeInvoice(invoiceReader)
	// if err != nil {
	// 	return nil
	// }

	// writter := new(bytes.Buffer)
	// serializeInvoice(writter, &invoice)

	// if err != nil {
	// 	return nil
	// }

	return 1
}


func main() {}
