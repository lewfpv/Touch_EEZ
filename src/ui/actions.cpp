#include <Arduino.h>  // Serial, delay, millis, stb.
#include <WiFi.h>     // WiFi kapcsolódáshoz (ESP32)
#include "ui.h"
#include "actions.h"  // ez fontos, hogy illeszkedjen a prototípusokhoz
#include "message.h"
#include "addpeers.h"
#include <WiFiUdp.h>
//#include <udpconfig.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ESP32httpUpdate.h>
#include <ArduinoJson.h>

// Vevők MAC címei
//uint8_t rec1[] = { 0xEC, 0xDA, 0x3B, 0xBF, 0xE6, 0x44 };  // Start pad, LEDek
//uint8_t rec2[] = { 0xEC, 0xDA, 0x3B, 0xBF, 0xE9, 0xA8 };  // pedál 1-2 EC:DA:3B:BF:E9:A8
//uint8_t rec3[] = { 0xEC, 0xDA, 0x3B, 0xBF, 0xC6, 0xB8 };  // pedál 3-4 EC:DA:3B:BF:C6:B8

extern void SendNOW(const uint8_t *mac, const Message &msg);
extern void resetRaceStats();
extern void reset();


void action_enter_settings(lv_event_t * e) {
    lv_scr_load(objects.settings);  // vagy lv_scr_load_anim(...) ha animált váltás kell
}

void action_on_main_settings_btn_clicked(lv_event_t * e) {
    lv_scr_load(objects.settings);
}

void action_on_settings_exit_btn_clicked(lv_event_t * e) {
    lv_scr_load(objects.main);
}

void action_on_settings_lan_btn_clicked(lv_event_t * e){
    lv_scr_load(objects.lansettings);
}

void action_on_settings_wifi_btn_clicked(lv_event_t * e) {
    lv_scr_load(objects.wifisettings);
}

void action_on_settings_eventesettings_clicked(lv_event_t * e){
    lv_scr_load(objects.eventsettings);
}

void action_on_settings_startpad_btn_clicked(lv_event_t * e){
    lv_scr_load(objects.startpadsettings);
}

void action_on_settings_about_btn_clicked(lv_event_t * e){
    lv_scr_load(objects.about);
}

void action_on_panel1_touch(lv_event_t * e){
  lv_obj_add_flag(objects.p1, LV_OBJ_FLAG_HIDDEN);
}

void action_on_panel2_touch(lv_event_t * e){
  lv_obj_add_flag(objects.p2, LV_OBJ_FLAG_HIDDEN);
}

void action_on_panel3_touch(lv_event_t * e){
  lv_obj_add_flag(objects.p3, LV_OBJ_FLAG_HIDDEN);
}

void action_on_panel4_touch(lv_event_t * e){
  lv_obj_add_flag(objects.p4, LV_OBJ_FLAG_HIDDEN);
}

void action_reset_racer_pedals(lv_event_t * e) {
  reset();
}

void action_startpad_led_switch(lv_event_t * e){
  if (lv_obj_has_state(objects.startpad_led_sw, LV_STATE_CHECKED)) {
        Serial.println("Kapcsoló: BE");
        Message msg = {5, 1, 0};  // type, index, value  (type=9 reset, index mit reseteljen, value mire reseteljen 0 tehát pirosra
        SendNOW(peers[6], msg); //startpad ledek
    } else {
        Serial.println("Kapcsoló: KI");
        Message msg = {5, 1, 1};  // type, index, value  (type=9 reset, index mit reseteljen, value mire reseteljen 0 tehát pirosra
        SendNOW(peers[6], msg); //startpad ledek
    }
}

void action_startpad_all_led_slider(lv_event_t * e){
  int val = lv_slider_get_value(objects.startpad_all_led_slider);

  //Serial.printf("📊 Slider value: %d\n", val);
  int brightness = val * 255 / 100;
  Serial.printf("📊 Slider value: %d\n", brightness);
  Message msg = {5, 0, static_cast<uint8_t>(brightness)};  // type, index, value  (type=9 reset, index mit reseteljen, value mire reseteljen 0 tehát pirosra
  SendNOW(peers[6], msg);
}

void action_hide_finish_panel(lv_event_t * e){
    // main sreen init-nél
}

void action_on_ssid_input_focused(lv_event_t * e) {
    lv_keyboard_set_textarea(objects.keyboard1, objects.ssid);
}

void action_on_pwd_input_focused(lv_event_t * e) {
    lv_keyboard_set_textarea(objects.keyboard1, objects.pwd);
}

void action_on_eventid_input_focused(lv_event_t * e) {
    lv_keyboard_set_textarea(objects.keyboard2, objects.eventid);
}

void action_connect_to_wifi(lv_event_t * e) {
  if(WiFi.status() == WL_CONNECTED){
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
  } else {
    const char *ssid = lv_textarea_get_text(objects.ssid);
    const char *password = lv_textarea_get_text(objects.pwd);

    Serial.printf("Connecting to SSID: %s\n", ssid);

    WiFi.disconnect(true);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }

    Serial.println("\nWiFi csatlakozva!");
    Serial.print("ESP32 IP: ");
    Serial.println(WiFi.localIP());

    //udp.begin(100);
    //Serial.printf("UDP figyelés port %d\n", localUdpPort);
    //Serial.println("\nUDP figyelése...");

    // Nem várunk itt, nem blokkolunk
    // Később a loop() vagy eseményfigyelő ad tájékoztatást
  }
}

void action_getjson(lv_event_t * e) {
  //empty
}

//OTA frissítés
void action_ota(lv_event_t * e) {
  const char *ssid = lv_textarea_get_text(objects.ssid);
  const char *password = lv_textarea_get_text(objects.pwd);

  Serial.printf("Connecting to SSID: %s\n", ssid);

  WiFi.disconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  // Várjuk meg, amíg csatlakozik a WiFi-hez
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi connected!");
    Serial.println(WiFi.localIP());

    // Firmware URL
    String fwURL = "http://yourserver.com/firmware.bin";

    t_httpUpdate_return ret = ESPhttpUpdate.update(fwURL);
    switch(ret) {
    case HTTP_UPDATE_FAILED:
      Serial.printf("Update failed: %s\n", ESPhttpUpdate.getLastErrorString().c_str());
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("No update available");
      break;
    case HTTP_UPDATE_OK:
      Serial.println("Update ok"); // automatikusan újraindul
      break;
  }
  } else {
    Serial.println("\n❌ WiFi connection failed.");
  }
}
