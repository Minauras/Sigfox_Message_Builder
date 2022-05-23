# Sigfox_Message_Builder

This C library allows the user to write a Sigfox message while controlling the space each variable takes in the payload on a bit level. It is designed to work with AT commands, which LiteOn Sigfox modules (f.i. WSG309S) use to send messages.

## Getting Started

Clone this repository or directly download it, and copy the files into your project workspace to use it.

## Example code

```
//initialize new message
SMB_new_message();

//add your data to the message, all data must be typecast to unsigned long
//specify the number of bits each variable must take up in the payload
SMB_add_variable((unsigned long) var1, 7);
SMB_add_variable((unsigned long) var2, 6);
SMB_add_variable((unsigned long) var3, 13);

//print your AT command with the payload using %s
printf("Send_MSG %s\r\n", SMB_get_message());

//reinitalize before writing new message
SMG_new_message();

...
```

## Author

* **Nara Clerc** alias [Minauras](https://github.com/Minauras)

## Acknowledgments

* **Billie Thompson** - *Readme template* - [PurpleBooth](https://github.com/PurpleBooth)
