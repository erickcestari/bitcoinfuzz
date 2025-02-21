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
	"log"
	"unsafe"

	"github.com/lightningnetwork/lnd/channeldb"
)

//export LndDeserializeInvoice
func LndDeserializeInvoice(invoiceData C.ByteArray) C.int {
	invoice := C.GoBytes(unsafe.Pointer(invoiceData.data), invoiceData.length)


	log.Printf("Deserializing invoice: %v", invoice)

	_, err := channeldb.DeserializeInvoice(invoice)
	if err != nil {
		log.Printf("Error deserializing invoice: %v", err)
		return 0
	}

	return 1
}


func main() {}
