#ifndef BKP_INTERFACE_H
#define BKP_INTERFACE_H

#include <stdint.h>

int BKP_read_data(uint8_t indx, uint16_t* buff);
int BKP_write_data(uint8_t indx, uint16_t data);
void BKP_enable_cco(void);

#endif
