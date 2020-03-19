/* This Library provides a builder to create a Sigfox Message payload variable by variable,
 * while granting the ability to control how much space each variable takes (bit-wise).
 * unfortunately, our project is in c, so we cannot benefit from OOP
 * @file	SigfoxMessageBuilder.h
 * @date	19-03-2020
 * @version	v1.0.0
 */


#ifndef SIGFOXMESSAGEBUILDER_H_
#define SIGFOXMESSAGEBUILDER_H_

#define SIGFOX_MESSAGE_SIZE 12 //bytes

/*!
 *  @brief This API must be called each time before writing a new message.
 *  Otherwise values may either be uninitialized or from previous message
 */
void SMB_new_message(void);

/*!
 *  @brief This API writes a value in the message with the specified number of bits
 *
 *  @param[in] 	data: value to be written (any data type must be cast as unsigned long)
 *  @param[in]	bit_size: number of bits the data must take inside the message. if not enough data to fill those bits, zero padding is used
 */
void SMB_add_variable(unsigned long data, unsigned int bit_size);

/*!
 *  @brief This API is called after message is done being written to get its string value as hexadecimal
 *
 *  @return null-terminated string containing hex representation of sigfox message (always 24 hex symbols long, zero padding if msg not full)
 */
char* SMB_get_message(void);

#endif
