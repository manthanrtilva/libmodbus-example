// gcc master.c -o master -lmodbus

#include <errno.h>
#include <modbus/modbus.h>
#include <stdio.h>

#include "common.h"

int main(int argc, char const *argv[]) {
  modbus_t *ctx =
      modbus_new_rtu(MASTER_DEV, BAUD, PARITY, DATA_BITS, STOP_BITS);
  if (ctx) {
    modbus_set_slave(ctx, SLAVE_ID);
    modbus_set_debug(ctx, DEBUG);
    if (modbus_connect(ctx) == 0) {
      uint8_t read_bits[BITS_NB];
      if (modbus_read_bits(ctx, BITS_ADDRESS, BITS_NB, read_bits) == BITS_NB) {
      } else {
        printf("Error : modbus_read_bits : %s \n", modbus_strerror(errno));
      }
      for (int i = 0; i < BITS_NB; ++i) {
        if (i % 2 == 0) {
          read_bits[i] = 1;
        } else {
          read_bits[i] = 0;
        }
      }
      if (modbus_read_input_bits(ctx, INPUT_BITS_ADDRESS, INPUT_BITS_NB,
                                 read_bits) == INPUT_BITS_NB) {
      } else {
        printf("Error : modbus_read_input_bits : %s \n",
               modbus_strerror(errno));
      }
      uint16_t read_registers[REGISTERS_NB];
      if (modbus_read_registers(ctx, REGISTERS_ADDRESS, REGISTERS_NB,
                                read_registers) == REGISTERS_NB) {
      } else {
        printf("Error : modbus_read_registers : %s \n", modbus_strerror(errno));
      }
      uint16_t read_input_registers[INPUT_REGISTERS_NB];
      if (modbus_read_input_registers(
              ctx, INPUT_REGISTERS_ADDRESS, INPUT_REGISTERS_NB,
              read_input_registers) == INPUT_REGISTERS_NB) {
      } else {
        printf("Error : modbus_read_input_registers : %s \n",
               modbus_strerror(errno));
      }
      for (int i = 0; i < BITS_NB; ++i) {
        int value = 0;
        if (i % 2 == 0) {
          value = 1;
        }
        if (modbus_write_bit(ctx, BITS_ADDRESS + i, value) == 1) {
        } else {
          printf("Error : modbus_write_bit : %s\n", modbus_strerror(errno));
        }
      }
      for (int i = 0; i < REGISTERS_NB; ++i) {
        int value = 0;
        if (i % 2 == 0) {
          value = 1;
        }
        if (modbus_write_register(ctx, REGISTERS_ADDRESS + i, value) == 1) {
        } else {
          printf("Error : modbus_write_register : %s\n",
                 modbus_strerror(errno));
        }
      }
      if (modbus_write_bits(ctx, BITS_ADDRESS, BITS_NB, read_bits) == BITS_NB) {
      } else {
        printf("Error : modbus_write_bits : %s \n", modbus_strerror(errno));
      }
      if (modbus_write_registers(ctx, REGISTERS_ADDRESS, REGISTERS_NB,
                                 read_registers) == REGISTERS_NB) {
      } else {
        printf("Error : modbus_write_registers : %s \n",
               modbus_strerror(errno));
      }
      for (int i = 0; i < REGISTERS_NB; ++i) {
        int value = 0;
        if (i & 0x01) {
          read_registers[i] = 0xffff;
        } else {
          read_registers[i] = 0;
        }
      }
      if (modbus_write_and_read_registers(ctx, REGISTERS_ADDRESS, REGISTERS_NB + 1,
                                          read_registers, REGISTERS_ADDRESS,
                                          REGISTERS_NB + 1,
                                          read_registers) == REGISTERS_NB + 1) {
      } else {
        printf("Error : modbus_write_and_read_registers : %s \n",
               modbus_strerror(errno));
      }
      modbus_close(ctx);
    } else {
      printf("Error : modbus_connect : %s \n", modbus_strerror(errno));
    }
    modbus_free(ctx);
  } else {
    printf("Error : modbus_new_rtu : %s \n", modbus_strerror(errno));
  }
  return 0;
}
