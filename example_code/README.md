# Example code for the Sigfox Message Builder Library

Contents:
- [main.c](./main.c): c code that uses the libary to send a Sigfox message
- [parser.js](./parser.js): javascript parser (designed for iotagency) to decode the payload accordingly

## What the code does

We want to send four variables to the cloud using Sigfox. Those four variables take a constant space in the payload of 5, 6, 7 and 1 bits respectively.

The libary is used in [main.c](./main.c) to easily encode those variables with the required space, then the AT command is sent through the UART channel using printf.

When the message is received on the cloud, the [parser](./parser.js) will decode it and parse it to retrieve the initial values correctly.

The parsed data can then be used to build a dashboard, for instance on iotagency.

## Author

* **Rémi Clerc** alias [Minauras](https://github.com/Minauras)
