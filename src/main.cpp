#include <queue>
#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include "addpeers.h"
#include "message.h"
#include <esp32_smartdisplay.h>
#include <ui/ui.h>
#include <ui/screens.h>
#include "ui/actions.h"
#include <esp_now.h>
#include <WiFi.h>
//#include <WiFiUdp.h>
//#include <udpconfig.h>
#include <ArduinoJson.h>

String fwversion = "1.0.7";

//LAN MAC: DE-AD-BE-EF-FE-ED
//WIZnetEFFEED

std::queue<Message> msgQueue;
portMUX_TYPE queueMux = portMUX_INITIALIZER_UNLOCKED; // FreeRTOS lock

MessageLong outgoingMessage;

struct TxMessage {
  uint8_t mac[6];
  size_t size;
  uint8_t data[sizeof(MessageLong)];
  uint8_t retries;
  unsigned long nextSendTime;  // mikor küldhető legközelebb
};

std::queue<TxMessage> txQueue;
portMUX_TYPE txMux = portMUX_INITIALIZER_UNLOCKED;

const size_t MAX_QUEUE_SIZE = 30;
const uint8_t MAX_RETRIES = 5;
const unsigned long SEND_INTERVAL = 5;   // min. 5 ms két küldés között
const unsigned long RETRY_DELAY   = 20;  // újrapróbálkozás késleltetése (ms)

void QueueSend(const uint8_t *mac, const void *data, size_t size) {
  portENTER_CRITICAL(&txMux);
  if (txQueue.size() >= MAX_QUEUE_SIZE) {
    txQueue.pop();
    Serial.println("⚠️ TX queue full, dropping oldest!");
  }

  TxMessage tx;
  memcpy(tx.mac, mac, 6);
  memcpy(tx.data, data, size);
  tx.size = size;
  tx.retries = MAX_RETRIES;
  tx.nextSendTime = millis();  // azonnal küldhető

  txQueue.push(tx);
  portEXIT_CRITICAL(&txMux);
}

void HandleOutgoingMessages() {
  static unsigned long lastSendTime = 0;
  if (millis() - lastSendTime < SEND_INTERVAL) return;  // globális sebességkorlát

  portENTER_CRITICAL(&txMux);
  if (txQueue.empty()) {
    portEXIT_CRITICAL(&txMux);
    return;
  }
  TxMessage tx = txQueue.front();

  // Ha még nem jött el az ideje, ne küldjük ki
  if (millis() < tx.nextSendTime) {
    portEXIT_CRITICAL(&txMux);
    return;
  }

  txQueue.pop();  // kivesszük a sorból
  portEXIT_CRITICAL(&txMux);

  esp_err_t result = esp_now_send(tx.mac, tx.data, tx.size);
  if (result == ESP_OK) {
    Serial.println("✅ Message sent");
  } else {
    Serial.printf("❌ Send error (%d), retries left: %d\n", result, tx.retries - 1);
    if (tx.retries > 1) {
      tx.retries--;
      tx.nextSendTime = millis() + RETRY_DELAY;  // késleltetett újrapróbálkozás
      portENTER_CRITICAL(&txMux);
      txQueue.push(tx);  // visszatesszük a sor végére
      portEXIT_CRITICAL(&txMux);
    } else {
      Serial.println("❌ Giving up on message after max retries!");
    }
  }

  lastSendTime = millis();
}




//LAN
#define W5500_SCLK   12    // Zöld
#define W5500_MISO   13    // Kék
#define W5500_MOSI   11    // Fehér
#define W5500_CS     17    // Sárga

//UDP Config
//#include <WiFiUdp.h>
//WiFiUDP udp;  // tényleges definíció


EthernetUDP udp;
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
unsigned int localPort = 100; // helyi UDP port
char incomingPacket[255];

#define MAX_RACERS 4
//változók
bool finished[4] = {false, false, false, false};  // versenyzők célba értek-e
int SpotterCounts[4] = {0, 0, 0, 0};              // célba érkező üzenetek számlálója
int finishOrder = 1;                              // hányadik helyen ért célba
String finishers[MAX_RACERS];
String pilot[MAX_RACERS];
int finishCount = 0;
bool resultBoxDrawn = false;
bool needReset = false;

const char* heatname = "-";
const char* P1 = "Racer_1";
const char* P2 = "Racer_2";
const char* P3 = "Racer_3";
const char* P4 = "Racer_4";

void drawpilots(){

  // FRISSÍTÉS a globális tömbhöz:
  pilot[0] = "R1  " + String(P1);
  pilot[1] = "R3  " + String(P2);
  pilot[2] = "R6  " + String(P3);
  pilot[3] = "R7  " + String(P4);

  // Példa kiírás a sorosra
  //Serial.print(F("Heatname: ")); Serial.println(heatname);
  //Serial.print(F("P1: ")); Serial.println(P1);
  //Serial.print(F("P2: ")); Serial.println(P2);
  //Serial.print(F("P3: ")); Serial.println(P3);
  //Serial.print(F("P4: ")); Serial.println(P4);

  lv_label_set_text(objects.heattitle_text, heatname);
  lv_obj_align(objects.heattitle_text, LV_ALIGN_CENTER, 0, 0);

    if (lv_obj_has_flag(objects.heattitle_panel, LV_OBJ_FLAG_HIDDEN)) {
    lv_obj_clear_flag(objects.heattitle_panel, LV_OBJ_FLAG_HIDDEN);
    }
  lv_label_set_text(objects.pilot1text, P1);
  lv_label_set_text(objects.pilot2text, P2);
  lv_label_set_text(objects.pilot3text, P3);
  lv_label_set_text(objects.pilot4text, P4);

  lv_obj_align(objects.pilot1text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(objects.pilot2text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(objects.pilot3text, LV_ALIGN_CENTER, 0, 0);
  lv_obj_align(objects.pilot4text, LV_ALIGN_CENTER, 0, 0);

    if (lv_obj_has_flag(objects.pilot1text, LV_OBJ_FLAG_HIDDEN)) {
    lv_obj_clear_flag(objects.pilot1text, LV_OBJ_FLAG_HIDDEN);
    }
    if (lv_obj_has_flag(objects.pilot2text, LV_OBJ_FLAG_HIDDEN)) {
    lv_obj_clear_flag(objects.pilot2text, LV_OBJ_FLAG_HIDDEN);
    }
    if (lv_obj_has_flag(objects.pilot3text, LV_OBJ_FLAG_HIDDEN)) {
    lv_obj_clear_flag(objects.pilot3text, LV_OBJ_FLAG_HIDDEN);
    }
    if (lv_obj_has_flag(objects.pilot4text, LV_OBJ_FLAG_HIDDEN)) {
    lv_obj_clear_flag(objects.pilot4text, LV_OBJ_FLAG_HIDDEN);
    }

}

int extractPosition(const char* s) {
  while (*s) {
    if (isdigit(*s)) return atoi(s);
    s++;
  }
  return -1;
}

void assignByPosition(int pos, char* name) {
  switch (pos) {
    case 1: P1 = name; break;
    case 3: P2 = name; break;
    case 6: P3 = name; break;
    case 7: P4 = name; break;
  }
}

void processJsonMessage(const char* jsonStr) {
  // Dinamikus Json dokumentum (méretet állítsd be a JSON mérete alapján)
  StaticJsonDocument<256> doc;

  // Parse-oljuk a json stringet
  DeserializationError error = deserializeJson(doc, jsonStr);
  if (error) {
    Serial.print(F("JSON parse error: "));
    Serial.println(error.f_str());
    return;
  }

  // Ez egy tömb, az első elem egy objektum
  JsonArray arr = doc.as<JsonArray>();
  if (arr.size() == 0) {
    Serial.println(F("Üres tömb!"));
    return;
  }

  JsonObject obj = arr[0];
  // Változókba szedjük ki az értékeket (ha léteznek) [{"heatname":"display_name","P1":"callsign","P2":"callsign","P3":"callsign","P4":"callsign"}]
  heatname = obj["heatname"] | "";
  P1 = obj["P1"] | "";
  P2 = obj["P2"] | "";
  P3 = obj["P3"] | "";
  P4 = obj["P4"] | "";

  drawpilots();

  // Itt beállíthatod a saját változóidat is, pl:
  // strncpy(heatnameVar, heatname, sizeof(heatnameVar));
  // stb.
}


void resetRaceStats() {
  for (int i = 0; i < MAX_RACERS; i++) {
    finished[i] = false;
    SpotterCounts[i] = 0;
    finishers[i] = "";
    Serial.print(finished[i]);
  }
  finishCount = 0;
  resultBoxDrawn = false;
  finishOrder = 1;
}

//SendNOW(cimzett mac cim, üzenet);
void SendNOW(const uint8_t *mac, const Message &msg) {
  esp_err_t result = esp_now_send(mac, (uint8_t *)&msg, sizeof(msg));
  (result == ESP_OK) ? Serial.println("✅ Message sent successfully") : Serial.printf("❌ Send error (%d)\n", result);
}

void SendLong(const uint8_t *mac, const MessageLong &msg) {
  esp_err_t result = esp_now_send(mac, (uint8_t *)&msg, sizeof(msg));
  (result == ESP_OK) ? Serial.println("✅ Message sent successfully") : Serial.printf("❌ Send error (%d)\n", result);
}

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Send status: OK, " + String(macStr) : "Send status: FAIL, " + String(macStr));
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
    if (len != sizeof(Message)) return;

    Message msg;
    memcpy(&msg, incomingData, sizeof(msg));

    portENTER_CRITICAL(&queueMux);
    msgQueue.push(msg);
    portEXIT_CRITICAL(&queueMux);
}

// Globális állapotok (kezdetben minden false, azaz nem kész)
bool racer_lap1[4] = { false, false, false, false };
bool racer_lap2[4] = { false, false, false, false };
bool racer_done[4] = { false, false, false, false };

void processIncomingMessages() {
    while (!msgQueue.empty()) {
        portENTER_CRITICAL(&queueMux);
        Message msg = msgQueue.front();
        msgQueue.pop();
        portEXIT_CRITICAL(&queueMux);

        switch (msg.type) {
            case 1: { // Verseny üzenet
                if (msg.index >= 1 && msg.index <= 4) {
                    int idx = msg.index - 1; // 0..3 index

                    lv_obj_t* panel = nullptr;
                    lv_obj_t* text = nullptr;
                    lv_obj_t* lapcounter = nullptr;

                    if (idx == 0) panel = objects.p1, text = objects.pilot1text, lapcounter = objects.lapcounter1;
                    else if (idx == 1) panel = objects.p2, text = objects.pilot2text, lapcounter = objects.lapcounter2;
                    else if (idx == 2) panel = objects.p3, text = objects.pilot3text, lapcounter = objects.lapcounter3;
                    else if (idx == 3) panel = objects.p4, text = objects.pilot4text, lapcounter = objects.lapcounter4;

                    if (msg.value == 0) {
                        lv_obj_set_style_bg_color(panel, lv_color_hex(0x00FF00), 0);
                        lv_obj_set_style_text_color(text, lv_color_hex(0x000000), 0);
                    }

                    else if (msg.value == 1) {
                        // Első kör teljesítve → sárga
                        racer_lap1[idx] = true; 
                        lv_obj_set_style_bg_color(panel, lv_color_hex(0xFFFF00), 0);
                        lv_obj_set_style_text_color(text, lv_color_hex(0x000000), 0);
                        lv_label_set_text(lapcounter, "1");
                    } 
                    else if (msg.value == 2) {
                        // Második kör teljesítve → narancs
                        racer_lap2[idx] = true;
                        lv_obj_set_style_bg_color(panel, lv_color_hex(0xFF8000), 0);
                        lv_obj_set_style_text_color(text, lv_color_hex(0x000000), 0);
                        lv_label_set_text(lapcounter, "2");
                    } 
                    else if (msg.value == 3) {
                        lv_label_set_text(lapcounter, "3");
                        // Célba érkezett → zöld + finishpanel frissítés
                        if (!racer_done[idx]) {
                            racer_done[idx] = true;

                            // Finish panel mutatása
                            if (lv_obj_has_flag(objects.finishpanel, LV_OBJ_FLAG_HIDDEN)) {
                                lv_obj_clear_flag(objects.finishpanel, LV_OBJ_FLAG_HIDDEN);
                            }
                            
                            // Helyezés hozzáadása (pilot neve)
                            finishers[finishCount] = pilot[idx];

                            lv_obj_t* finishlines[4] = {
                                objects.finishline0,
                                objects.finishline1,
                                objects.finishline2,
                                objects.finishline3
                            };

                            if (finishCount < 4) {
                                String textline = String(finishCount + 1) + ". " + finishers[finishCount];
                                lv_label_set_text(finishlines[finishCount], textline.c_str());
                                lv_obj_clear_flag(finishlines[finishCount], LV_OBJ_FLAG_HIDDEN);

                                /// helyezés kiküldése a spotternek
                                Serial.println("helyezés kiküldése a spotternek");
                                outgoingMessage.type = 6;
                                outgoingMessage.index = finishCount + 1;
                                strncpy(outgoingMessage.p, "", sizeof(outgoingMessage.p));
                                QueueSend(peers[idx], &outgoingMessage, sizeof(outgoingMessage));
                                Serial.println("helyezes: " + String(outgoingMessage.index));
                                Serial.println("ELKULDVE neki: " + String(msg.index));
                                finishCount++;
                            }
                        }
                    }
                }
                break;
            }

            case 2: { // Fényerő
                // analogWrite(LED_BUILTIN, msg.value);
                break;
            }

            default:
                break;
        }
    }
}

//// RESET START
void reset() {
    // Ellenőrizzük, van-e legalább egy true a racer_done-ban
    
    for (int i = 0; i < 4; i++) {
        if (racer_done[i] || racer_lap1) {
            needReset = true;
            break;
        }
    }

    if (!lv_obj_has_flag(objects.finishpanel, LV_OBJ_FLAG_HIDDEN)) {
    // Csak akkor fut le, ha NINCS elrejtve (tehát látszik)
    lv_obj_add_flag(objects.finishpanel, LV_OBJ_FLAG_HIDDEN);  // elrejti
    lv_obj_add_flag(objects.finishline0, LV_OBJ_FLAG_HIDDEN); 
    lv_obj_add_flag(objects.finishline1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.finishline2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.finishline3, LV_OBJ_FLAG_HIDDEN);
    }


    resetRaceStats();


    if (!needReset) {
        // Nincs mit resetelni → azonnal kilépünk
        return;
    }

    // Innentől biztosan van mit resetelni
    if (lv_obj_has_flag(objects.p1, LV_OBJ_FLAG_HIDDEN)) {
        lv_obj_clear_flag(objects.p1, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(objects.r1text, LV_OBJ_FLAG_HIDDEN);
    }

    if (lv_obj_has_flag(objects.p2, LV_OBJ_FLAG_HIDDEN)) {
        lv_obj_clear_flag(objects.p2, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(objects.r3text, LV_OBJ_FLAG_HIDDEN);
    }

    if (lv_obj_has_flag(objects.p3, LV_OBJ_FLAG_HIDDEN)) {
        lv_obj_clear_flag(objects.p3, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(objects.r6text, LV_OBJ_FLAG_HIDDEN);
    }

    if (lv_obj_has_flag(objects.p4, LV_OBJ_FLAG_HIDDEN)) {
        lv_obj_clear_flag(objects.p4, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(objects.r7text, LV_OBJ_FLAG_HIDDEN);
    }

    lv_obj_set_style_bg_color(objects.p1, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_color(objects.p2, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_color(objects.p3, lv_color_hex(0xFF0000), 0);
    lv_obj_set_style_bg_color(objects.p4, lv_color_hex(0xFF0000), 0);

    lv_obj_set_style_text_color(objects.pilot1text, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(objects.pilot2text, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(objects.pilot3text, lv_color_hex(0xFFFFFF), 0);
    lv_obj_set_style_text_color(objects.pilot4text, lv_color_hex(0xFFFFFF), 0);

    lv_obj_add_flag(objects.finishpanel, LV_OBJ_FLAG_HIDDEN);  
    lv_obj_add_flag(objects.finishline0, LV_OBJ_FLAG_HIDDEN);  
    lv_obj_add_flag(objects.finishline1, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.finishline2, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.finishline3, LV_OBJ_FLAG_HIDDEN);

    lv_label_set_text(objects.lapcounter1, "-");
    lv_label_set_text(objects.lapcounter2, "-");
    lv_label_set_text(objects.lapcounter3, "-");
    lv_label_set_text(objects.lapcounter4, "-");

    //SendNOW(peers[4], msg); 
    //SendNOW(peers[5], msg); 
    //SendNOW(peers[6], msg); 

// Race finisher reset
outgoingMessage.type = 9;
outgoingMessage.index = 0;

strncpy(outgoingMessage.p, P1, sizeof(outgoingMessage.p));
QueueSend(peers[0], &outgoingMessage, sizeof(outgoingMessage));

strncpy(outgoingMessage.p, P2, sizeof(outgoingMessage.p));
QueueSend(peers[1], &outgoingMessage, sizeof(outgoingMessage));

strncpy(outgoingMessage.p, P3, sizeof(outgoingMessage.p));
QueueSend(peers[2], &outgoingMessage, sizeof(outgoingMessage));

strncpy(outgoingMessage.p, P4, sizeof(outgoingMessage.p));
QueueSend(peers[3], &outgoingMessage, sizeof(outgoingMessage));

Message msg = {9, 0, 0};
for (int i = 4; i < 7; i++) {
  QueueSend(peers[i], &msg, sizeof(msg));
}


    for (int i = 0; i < 4; i++) {
        racer_done[i] = false;
        racer_lap1[i] = false;
        racer_lap2[i] = false;
    }
}
//// RESET END

void parseUDP(char* msg) {
  // A strlen() lekéri a string hosszát (a lezáró \0 karaktert nem számolja bele)
  if (strlen(msg) == 1) {
    // Megvizsgáljuk, hogy az első és egyetlen karakter egy '1'-es-e
    if (msg[0] == '1') {
      Serial.printf("RACE STARTED");
      needReset = true;
      // Race finisher timerstart ->
  outgoingMessage.type = 1;
  outgoingMessage.index = 2;
  strncpy(outgoingMessage.p, "", sizeof(outgoingMessage.p));

  QueueSend(peers[0], &outgoingMessage, sizeof(outgoingMessage));
  QueueSend(peers[1], &outgoingMessage, sizeof(outgoingMessage));
  QueueSend(peers[2], &outgoingMessage, sizeof(outgoingMessage));
  QueueSend(peers[3], &outgoingMessage, sizeof(outgoingMessage));

  //STARTPAD LED OFF
        Serial.println("Kapcsoló: KI");
        Message msg = {5, 1, 0};  // type, index, value  (type=9 reset, index mit reseteljen, value mire reseteljen 0 tehát pirosra
        SendNOW(peers[6], msg); //startpad ledek

    }
  } else {

  P1 = P2 = P3 = P4 = "-";
  heatname = "-";

  // Heatnév kinyerése
  char* sep = strstr(msg, " . ");
  if (!sep) {
    heatname = msg;
    return;
  }

  *sep = '\0';
  heatname = msg;
  char* rest = sep + 3;

  // Feldolgozás: "Név: R1 . Név: R3 ..."
  char* token = strtok(rest, ".");
  while (token) {
    // Szóközök eltávolítása az elejéről
    while (*token == ' ') token++;
    char* colon = strchr(token, ':');
    if (colon) {
      *colon = '\0';
      char* name = token;
      while (*name == ' ') name++; // trim eleje
      char* posStr = colon + 1;
      while (*posStr == ' ') posStr++;
      int pos = extractPosition(posStr);
      assignByPosition(pos, name);
    }
    token = strtok(NULL, ".");
  }
  drawpilots();
  reset();
  }
}



unsigned long lv_last_tick = 0;

void setup()
{
  Serial.begin(115200);
  //delay(1000);

  // Initialize display and UI
  smartdisplay_init();
  ui_init();

  lv_scr_load(objects.intro); // <- ez legyen az induló képernyő
  // Időzítő a képernyőváltáshoz (3.5 másodperc = 3500 ms)
  lv_timer_create([](lv_timer_t * t) {
      lv_scr_load(objects.main);  // <-- ide válts vissza a főképernyőre
      lv_timer_del(t);             // töröld az időzítőt, ne fusson tovább
  }, 3500, NULL);

  //Ethernet indítása...
  Serial.println("Ethernet indítása...");
  SPI.begin(W5500_SCLK, W5500_MISO, W5500_MOSI); // SCLK, MISO, MOSI
  Ethernet.init(W5500_CS); //CS (SCS)

  // DHCP gyors próba
  if (Ethernet.begin(mac, 10000) == 0) {  // max 10 sec várakozás
    Serial.println("DHCP hiba! Fix IP-t állítok be...");
    IPAddress ip(192, 168, 0, 177);
    IPAddress dns(192, 168, 0, 1);
    IPAddress gateway(192, 168, 0, 1);
    IPAddress subnet(255, 255, 255, 0);
    Ethernet.begin(mac, ip, dns, gateway, subnet);
  }
  Serial.print("IP cím: ");
  Serial.println(Ethernet.localIP());

  char ipBuf0[32];  // Bőven elég egy IPv4 címnek
  snprintf(ipBuf0, sizeof(ipBuf0), "IP: %s", Ethernet.localIP().toString().c_str());
  lv_label_set_text(objects.lan_current_ip, ipBuf0);

  // UDP indítása
  udp.begin(localPort);

  // Setup WiFi in STA mode for ESP-NOW
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }
  // Register receive callback
  esp_now_register_recv_cb(OnDataRecv);
  esp_now_register_send_cb(OnDataSent);
  addPeers();// <-- ide tedd be, hogy hozzáadja a peer-eket

  // Initialize LVGL ticker
  lv_last_tick = millis();

  lv_label_set_text(objects.version, fwversion.c_str());
  drawpilots();
  
}

void loop()
{
  HandleOutgoingMessages();
  auto const now = millis();

  // Update LVGL tick
  lv_tick_inc(now - lv_last_tick);
  lv_last_tick = now;

  // Handle LVGL and EEZ UI
  lv_timer_handler();
  ui_tick();
  
  processIncomingMessages(); // Queue feldolgozás

  static wl_status_t lastStatus = WL_DISCONNECTED;
    wl_status_t currentStatus = WiFi.status();

    if (currentStatus != lastStatus) {
        lastStatus = currentStatus;

        if (currentStatus == WL_CONNECTED) {
            Serial.println("\n✅ WiFi connected!");
            Serial.println(WiFi.localIP());
            lv_label_set_text(objects.connect_btn_label, "Disconnect");
            char ipBuf[32];  // Bőven elég egy IPv4 címnek
            snprintf(ipBuf, sizeof(ipBuf), "IP: %s", WiFi.localIP().toString().c_str());
            lv_label_set_text(objects.ip_addr_label, ipBuf);

        } else if (currentStatus == WL_DISCONNECTED) {
            Serial.println("\n❌ WiFi disconnected or connection failed.");
            lv_label_set_text(objects.connect_btn_label, "Connect");
            lv_label_set_text(objects.ip_addr_label, "IP: 0.0.0.0");
            // Nem próbálkozunk automatikusan újra, csak jelzés
        }
    }

  wl_status_t udpstatus = WiFi.status();
  if (udpstatus == WL_CONNECTED) {
    int packetSize = udp.parsePacket();
  if (packetSize) {
    int len = udp.read(incomingPacket, sizeof(incomingPacket) - 1);
    if (len > 0) incomingPacket[len] = '\0';

    Serial.printf("Kapott UDP csomag: %s\n", incomingPacket);
    Serial.printf("Forrás IP: %s, Port: %d\n", udp.remoteIP().toString().c_str(), udp.remotePort());

    parseUDP(incomingPacket);

    // Debug
    Serial.printf("Heat: %s\n", heatname);
    Serial.printf("P1(R1): %s\n", P1);
    Serial.printf("P2(R3): %s\n", P2);
    Serial.printf("P3(R6): %s\n", P3);
    Serial.printf("P4(R7): %s\n", P4);
  }
}


    int packetSize = udp.parsePacket();
    if (packetSize) {
        int len = udp.read(incomingPacket, sizeof(incomingPacket) - 1);
        if (len > 0) incomingPacket[len] = '\0';

        Serial.printf("Kapott UDP csomag: %s\n", incomingPacket);
        Serial.printf("Forrás IP: %s, Port: %d\n",
                      udp.remoteIP().toString().c_str(),
                      udp.remotePort());

        parseUDP(incomingPacket);

        Serial.printf("Heat: %s\n", heatname);
        Serial.printf("P1(R1): %s\n", P1);
        Serial.printf("P2(R3): %s\n", P2);
        Serial.printf("P3(R6): %s\n", P3);
        Serial.printf("P4(R7): %s\n", P4);
    }



  //////// SOROS PORT DEBUG ELEJE //////
  // Soros porton érkező üzenetek feldolgozása
 if (Serial.available()) {
    String inmsg = Serial.readStringUntil('\n');
    inmsg.trim(); // whitespace és \r eltávolítása

  if (inmsg.length() > 0 && inmsg.startsWith("[{")){
      processJsonMessage(inmsg.c_str());
  } else {

    if (inmsg == "PEDAL1") {}
    if (inmsg == "PEDAL2") {}
    if (inmsg == "PEDAL3") {}
    if (inmsg == "PEDAL4") {}
    
    if (inmsg == "RESET") action_reset_racer_pedals(NULL);
    // Célbaérkezés logika (Racer N - RY)
    if (inmsg.startsWith("Racer")) {
      int racerIndex = -1;

      if (inmsg.startsWith("Racer 1")) {
        inmsg =   pilot[0];
        racerIndex = 0;
      }
      if (inmsg.startsWith("Racer 2")) {
        inmsg =   pilot[1];
        racerIndex = 1;
      }
      if (inmsg.startsWith("Racer 3")) {
        inmsg =   pilot[2];
        racerIndex = 2;
      }
      if (inmsg.startsWith("Racer 4")) {
        inmsg =   pilot[3];
        racerIndex = 3;
      }

      if (racerIndex != -1) {
        SpotterCounts[racerIndex]++;
        Serial.printf("Racer %d SpotterCount: %d\n", racerIndex + 1, SpotterCounts[racerIndex]);

        if (!finished[racerIndex]) {
          finished[racerIndex] = true;
          finishers[finishCount] = inmsg;
          finishCount++;

        if (lv_obj_has_flag(objects.finishpanel, LV_OBJ_FLAG_HIDDEN)) {
        lv_obj_clear_flag(objects.finishpanel, LV_OBJ_FLAG_HIDDEN);  // csak akkor, ha tényleg rejtve van
        }

          lv_obj_t* finishlines[4] = {objects.finishline0, objects.finishline1, objects.finishline2, objects.finishline3};
          for (int i = 0; i < finishCount; i++) {
            
            String text = String(i + 1) + ". " + finishers[i];
            
            lv_label_set_text(finishlines[i], text.c_str());
            //lv_label_set_text(finishlines[i], Pilots[i]);

            if (lv_obj_has_flag(finishlines[i], LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_clear_flag(finishlines[i], LV_OBJ_FLAG_HIDDEN);
            }
          }
        }
      } 



    }
  } 
 }
  //////// SOROS PORT DEBUG VÉGE ////// 
}