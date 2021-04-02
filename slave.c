// gcc slave.c -o slave -lmodbus

#include <errno.h>
#include <modbus/modbus.h>
#include <stdio.h>

#include "common.h"
void printQuery(uint8_t *query, int len) {
  for (int i = 0; i < len; ++i) {
    printf("[%02X]", query[i]);
  }
  printf("\n");
}
int main(int argc, char const *argv[]) {
  modbus_t *ctx = modbus_new_rtu(SLAVE_DEV, BAUD, PARITY, DATA_BITS, STOP_BITS);
  if (ctx) {
    modbus_set_slave(ctx, SLAVE_ID);
    modbus_set_debug(ctx, DEBUG);
    modbus_mapping_t *mb_mapping = modbus_mapping_new(
        BITS_ADDRESS + BITS_NB, INPUT_BITS_ADDRESS + INPUT_BITS_NB,
        REGISTERS_ADDRESS + REGISTERS_NB,
        INPUT_REGISTERS_ADDRESS + INPUT_REGISTERS_NB);
    if (mb_mapping) {
      if (modbus_connect(ctx) == 0) {
        for (;;) {
          uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
          int rc;
          rc = modbus_receive(ctx, query);
          if (rc > 0) {
            // printQuery(query, rc);
            uint16_t address = 0, len = 0;
            address = query[2] << 8 | query[3];
            len = query[4] << 8 | query[5];
            // bussiness logic on read/write operation can be implemented here.
            switch (query[1]) {
            case 0x01: // read_bits
              break;
            case 0x02: // read input bits
              break;
            case 0x03: // read registers
              break;
            case 0x04: // read input registers
              break;
            case 0x05: // write bit
              break;
            case 0x06: // write register
              break;
            case 0x0F: // write bits
              break;
            case 0x10: // write registers
              break;
            case 0x17: // write read registers
              break;
            }
            modbus_reply(ctx, query, rc, mb_mapping);
          } else if (rc == -1) {
            /* Connection closed by the client or error */
            break;
          }
        }
      } else {
        printf("Error : modbus_connect : %s \n", modbus_strerror(errno));
      }
      modbus_free(ctx);
    } else {
      printf("Error : modbus_mapping_new : %s \n", modbus_strerror(errno));
    }
    modbus_mapping_free(mb_mapping);
  } else {
    printf("Error : modbus_new_rtu : %s \n", modbus_strerror(errno));
  }
  return 0;
}
