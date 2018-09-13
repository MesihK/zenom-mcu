#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "var.pb.h"

void dump_byte_array(uint8_t *data, uint8_t size){
	for(int i=0; i < size; i++){
		printf("%02x", data[i]);
	}
}

int main()
{
    /* This is the buffer where we will store our message. */
    uint8_t buffer[128];
    size_t message_length;
    bool status;
    
    /* Encode our message */
    {
        /* Allocate space on the stack to store the message data.
         *
         * Nanopb generates simple struct definitions for all the messages.
         * - check out the contents of simple.pb.h!
         * It is a good idea to always initialize your structures
         * so that you do not have garbage data from RAM in there.
         */
        VarMsg message = VarMsg_init_zero;
        VarMsgs msgs = VarMsgs_init_zero;
        
        /* Create a stream that will write to our buffer. */
        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));
        
        /* Fill in the lucky number */
		memcpy(message.name, "Mesih", sizeof("Mesih"));
		message.data.size = 1;
		message.data.bytes[0] = 13;

		msgs.msg_count = 2;
		msgs.msg[0] = message;
		msgs.msg[1] = message;
        
        /* Now we are ready to encode the message! */
        //status = pb_encode(&stream, VarMsg_fields, &message);
        status = pb_encode(&stream, VarMsgs_fields, &msgs);
        message_length = stream.bytes_written;
        
        /* Then just check for any errors.. */
        if (!status){
            printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }

		printf("Data: ");
		dump_byte_array(buffer, message_length);
		printf("\n");

    }
    
    /* Now we could transmit the message over network, store it in a file or
     * wrap it to a pigeon's leg.
     */

    /* But because we are lazy, we will just decode it immediately. */
    
    {
        /* Allocate space for the decoded message. */
        VarMsg message = VarMsg_init_zero;
        VarMsgs msgs = VarMsgs_init_zero;
        
        /* Create a stream that reads from the buffer. */
        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);
        
        /* Now we are ready to decode the message. */
        //status = pb_decode(&stream, VarMsg_fields, &message);
        status = pb_decode(&stream, VarMsgs_fields, &msgs);
        
        /* Check for errors... */
        if (!status){
            printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }
        
        /* Print the data contained in the message. */
        printf("Your var name: %s, data: %d!\n", message.name, (int)message.data.bytes[0]);
        printf("Your var count: %d, data: %d!\n", msgs.msg_count, (int)msgs.msg[0].data.bytes[0]);
    }
    
    return 0;
}

