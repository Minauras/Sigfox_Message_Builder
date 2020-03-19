/* This Library provides a builder to create a Sigfox Message payload variable by variable,
 * while granting the ability to control how much space each variable takes (bit-wise).
 * unfortunately, our project is in c, so we cannot benefit from OOP
 *
 * @file	SigfoxMessageBuilder.c
 * @date	19-03-2020
 * @version	v1.0.0
 */

#include "SigfoxMessageBuilder.h"
#include <stdio.h>
#include <math.h>

typedef struct
{
	int bit_message[8*SIGFOX_MESSAGE_SIZE]; //bit sequence (96 bits)
	char char_message[2*SIGFOX_MESSAGE_SIZE + 1]; //compiled char sequence (twice because a byte is two hex symbols so two chars) +1 for null-terminating character
	int cursor; //cursor to next bit to write

}
Sigfox_Message;

static Sigfox_Message sigfox_message;

void SMB_new_message(void){
	//reinitialize array with only zeros
	for(int i = 0; i < 8*SIGFOX_MESSAGE_SIZE; i++) sigfox_message.bit_message[i] = 0;
	sigfox_message.cursor = 0;
}


/* ADD_VARIABLE
 *
 * parameters:
 * - data (unsigned long)
 * 		data to be written in the message, must be type cast to unsigned long
 * - bit_size (unsigned int)
 * 		size in bits that data must take in the message
 *
 * if data < 2^(bit_size - 1), zero padding is used
 *
 * in case of invalid argument, function will return without modifying any data
 */
void SMB_add_variable(unsigned long data, unsigned int bit_size){

	/* input verification */
	if(data > pow(2, bit_size)){
		printf("Error building Sigfox Message: data %lu cannot fit in %d bits\r\n", data, bit_size);
		return;
	}
	if(bit_size > 8*SIGFOX_MESSAGE_SIZE - sigfox_message.cursor){
		printf("Error building Sigfox Message: not enough space remaining in message to fit %d bits\r\n", bit_size);
		return;
	}
	/**********************/


	/* binary decomposition
	 * decrementing loop because we get LSB first
	 */
	unsigned long remaining_data = data;
	for(int i = bit_size - 1; i >= 0; i--){

		int bit = remaining_data % 2;

		//store binary decomposition starting from LSB
		sigfox_message.bit_message[sigfox_message.cursor + i] = bit;

		remaining_data = (remaining_data - bit)/2;
	}
	//update cursor position
	sigfox_message.cursor = sigfox_message.cursor + bit_size;
}


char* SMB_get_message(void){
	//convert bit message to char message for AT command
	for(int i = 0; i < SIGFOX_MESSAGE_SIZE; i++){
		// most significant nibble
		int MSN = 	(sigfox_message.bit_message[8*i] << 3) +
					(sigfox_message.bit_message[8*i+1] << 2) +
					(sigfox_message.bit_message[8*i+2] << 1) +
					(sigfox_message.bit_message[8*i+3]);

		// least significant nibble
		int LSN =	(sigfox_message.bit_message[8*i+4] << 3) +
					(sigfox_message.bit_message[8*i+5] << 2) +
					(sigfox_message.bit_message[8*i+6] << 1) +
					(sigfox_message.bit_message[8*i+7]);

		sprintf(&sigfox_message.char_message[2*i], "%X", MSN);
		sprintf(&sigfox_message.char_message[2*i + 1], "%X", LSN);

	}
	sigfox_message.char_message[2*SIGFOX_MESSAGE_SIZE] = '\0'; //null terminator

	return sigfox_message.char_message;
}
