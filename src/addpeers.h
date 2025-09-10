#ifndef ADDPEERS_H
#define ADDPEERS_H

#include <esp_now.h>
#include <Arduino.h>  // Serial miatt

// Peerek száma
extern const int numPeers;

// Peerek MAC címei (külső definíció)
extern uint8_t receiver1[6];
extern uint8_t receiver2[6];
extern uint8_t receiver3[6];
extern uint8_t receiver4[6];
extern uint8_t receiver5[6];
extern uint8_t receiver6[6];
extern uint8_t receiver7[6];

// Peerek tömbje
extern uint8_t* peers[];

// Függvény prototípus
void addPeers();


#endif
