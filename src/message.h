#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>

//struct struct_message {
//  char id[32];
//  int value;
//  uint32_t timestamp;  // például millis()
//} struct_message;

//  Message msg;
//  msg.type = 1;       // pedál
//  msg.index = 2;      // PEDAL3
//  msg.value = 1;      // ready

struct Message {
  uint8_t type;   // 1: Pedál, 2: Fényerő stb.
  uint8_t index;  // Melyik pedál/LED
  uint8_t value;  // Pl. 0/1 vagy fényerő érték 0..255
};

#endif