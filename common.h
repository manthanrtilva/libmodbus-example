#ifndef __common__h__
#define __common__h__

#define SLAVE_ID 11
#define SLAVE_DEV "/dev/ttyUSB0"
#define MASTER_DEV "/dev/ttyUSB1"
#define BAUD 19200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY 'N'
#define DEBUG TRUE

#define BITS_ADDRESS 0
#define BITS_NB 10
#define INPUT_BITS_ADDRESS BITS_ADDRESS+BITS_NB
#define INPUT_BITS_NB 10 
#define REGISTERS_ADDRESS INPUT_BITS_ADDRESS+INPUT_BITS_NB
#define REGISTERS_NB 10
#define INPUT_REGISTERS_ADDRESS REGISTERS_ADDRESS+REGISTERS_NB
#define INPUT_REGISTERS_NB 10


#endif // __common__h__