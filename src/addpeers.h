#ifndef ADDPEERS_H
#define ADDPEERS_H

#include <esp_now.h>
#include <Arduino.h>  // Serial miatt

// MAC címek deklarálása és inicializálása itt:
// Vevők MAC címei

uint8_t receiver1[] = { 0xEC, 0xDA, 0x3B, 0xBF, 0xE6, 0x44 };  // Start pad, LEDek
uint8_t receiver2[] = { 0xEC, 0xDA, 0x3B, 0xBF, 0xE9, 0xA8 };  // pedál 1-2 EC:DA:3B:BF:E9:A8
uint8_t receiver3[] = { 0xEC, 0xDA, 0x3B, 0xBF, 0xC6, 0xB8 };  // pedál 3-4 EC:DA:3B:BF:C6:B8

void addPeers() {
  // Első peer
  esp_now_peer_info_t peer1 = {};
  memcpy(peer1.peer_addr, receiver1, 6);
  peer1.channel = 0;
  peer1.encrypt = false;
  if (!esp_now_add_peer(&peer1)) {
    Serial.println("Peer1 added");
  }

  // 2. peer
  esp_now_peer_info_t peer2 = {};
  memcpy(peer2.peer_addr, receiver2, 6);
  peer2.channel = 0;
  peer2.encrypt = false;
  if (!esp_now_add_peer(&peer2)) {
    Serial.println("Peer2 added");
  }

    // 3. peer
  esp_now_peer_info_t peer3 = {};
  memcpy(peer3.peer_addr, receiver3, 6);
  peer3.channel = 0;
  peer3.encrypt = false;
  if (!esp_now_add_peer(&peer3)) {
    Serial.println("Peer3 added");
  }

}

#endif
