#include "addpeers.h"

// MAC címek definiálása
uint8_t receiver1[6] = { 0x08, 0x3A, 0x8D, 0x96, 0x40, 0x58 }; //R1 - peers[0]
uint8_t receiver2[6] = { 0xB0, 0xB2, 0x1C, 0xF8, 0xB5, 0xC4 }; //R3 - peers[1]
uint8_t receiver3[6] = { 0xB0, 0xB2, 0x1C, 0xF8, 0xBC, 0x48 }; //R6 -peers[2]
uint8_t receiver4[6] = { 0xB0, 0xB2, 0x1C, 0xF8, 0xAE, 0x88 }; //R7 -peers[3]
uint8_t receiver5[6] = { 0xEC, 0xDA, 0x3B, 0xBF, 0xE9, 0xA8 }; // pedál 1-2 peers[4]
uint8_t receiver6[6] = { 0xEC, 0xDA, 0x3B, 0xBF, 0xC6, 0xB8 }; // pedál 3-4 peers[5]
uint8_t receiver7[6] = { 0xEC, 0xDA, 0x3B, 0xBF, 0xE6, 0x44 }; // Start pad, LEDek peers[6]

// Tömb, ami a címekre mutat
uint8_t* peers[] = {
    receiver1,
    receiver2,
    receiver3,
    receiver4,
    receiver5,
    receiver6,
    receiver7
};

// Peerek száma
const int numPeers = sizeof(peers) / sizeof(peers[0]);

void addPeers() {
    for (int i = 0; i < numPeers; i++) {
        esp_now_peer_info_t peerInfo = {};
        memcpy(peerInfo.peer_addr, peers[i], 6);
        peerInfo.channel = 0;
        peerInfo.encrypt = false;
        if (esp_now_add_peer(&peerInfo) == ESP_OK) {
            Serial.printf("Peer %d added\n", i + 1);
        } else {
            Serial.printf("❌ Peer %d add failed!\n", i + 1);
        }
    }
}
