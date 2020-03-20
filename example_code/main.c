#include <stdio.h>
#include "Sigfox_Message_Builder.h"

int main(void){
	unsigned var1 = 23;
	unsigned var2 = 44;
	unsigned var3 = 125;
	unsigned var4 = 1;
	
	//initialize new message
	SMB_new_message();
	
	//fill message with values, each value will take minimal number of bits to be represented
	SMB_add_variable((unsigned long) var1, 5); // represent 23 on 5 bits
	SMB_add_variable((unsigned long) var2, 6); // represent 44 on 6 bits
	SMB_add_variable((unsigned long) var3, 7); // represent 125 on 7 bits
	SMB_add_variable((unsigned long) var4, 1); // represent 1 on 1 bit
	
	//send message through UART channel using printf
	printf("Send_MSG %s\r\n", SMB_get_message());
	
	return 1;
}