#ifndef ADDPEERS_H
#define ADDPEERS_H

#include <esp_now.h>
#include <Arduino.h>  // Serial miatt

// MAC címek deklarálása és inicializálása itt:
uint8_t peers[][6] = {
    { 0x08, 0x3A, 0x8D, 0x96, 0x40, 0x58 }, //R1 - peers[0]
    { 0xB0, 0xB2, 0x1C, 0xF8, 0xB5, 0xC4 }, //R3 - peers[1]
    { 0xB0, 0xB2, 0x1C, 0xF8, 0xBC, 0x48 }, //R6 -peers[2]
    { 0xB0, 0xB2, 0x1C, 0xF8, 0xAE, 0x88 }, //R7 -peers[3]
    { 0xEC, 0xDA, 0x3B, 0xBF, 0xE9, 0xA8 }, // pedál 1-2 peers[4]
    { 0xEC, 0xDA, 0x3B, 0xBF, 0xC6, 0xB8 }, // pedál 3-4 peers[5]
    { 0xEC, 0xDA, 0x3B, 0xBF, 0xE6, 0x44 }  // Start pad, LEDek peers[6]
};

void addPeers() {
    int i = 0;
    while (i < sizeof(peers) / sizeof(peers[0])) {
        esp_now_peer_info_t peer = {};
        memcpy(peer.peer_addr, peers[i], 6);
        peer.channel = 0;
        peer.encrypt = false;

        if (esp_now_add_peer(&peer) == ESP_OK) {
            Serial.printf("Peer %d added\n", i + 1);
        } else {
            Serial.printf("Failed to add Peer %d\n", i + 1);
        }
        i++;
    }
}

#endif
