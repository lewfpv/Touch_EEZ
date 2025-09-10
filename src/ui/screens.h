#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *settings;
    lv_obj_t *intro;
    lv_obj_t *lansettings;
    lv_obj_t *wifisettings;
    lv_obj_t *eventsettings;
    lv_obj_t *startpadsettings;
    lv_obj_t *p1;
    lv_obj_t *r1text;
    lv_obj_t *pilot1text;
    lv_obj_t *p2;
    lv_obj_t *r3text;
    lv_obj_t *pilot2text;
    lv_obj_t *p3;
    lv_obj_t *r6text;
    lv_obj_t *pilot3text;
    lv_obj_t *p4;
    lv_obj_t *r7text;
    lv_obj_t *pilot4text;
    lv_obj_t *settings_btn;
    lv_obj_t *reset_btn;
    lv_obj_t *finishpanel;
    lv_obj_t *finishline0;
    lv_obj_t *finishline1;
    lv_obj_t *finishline2;
    lv_obj_t *finishline3;
    lv_obj_t *heattitle_panel;
    lv_obj_t *heattitle_text;
    lv_obj_t *lan_current_ip;
    lv_obj_t *obj0;
    lv_obj_t *ssid;
    lv_obj_t *pwd;
    lv_obj_t *keyboard1;
    lv_obj_t *connect_btn;
    lv_obj_t *connect_btn_label;
    lv_obj_t *obj1;
    lv_obj_t *ip_addr_label;
    lv_obj_t *eventid;
    lv_obj_t *keyboard2;
    lv_obj_t *obj2;
    lv_obj_t *startpad_led_sw;
    lv_obj_t *obj3;
    lv_obj_t *startpad_all_led_slider;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_SETTINGS = 2,
    SCREEN_ID_INTRO = 3,
    SCREEN_ID_LANSETTINGS = 4,
    SCREEN_ID_WIFISETTINGS = 5,
    SCREEN_ID_EVENTSETTINGS = 6,
    SCREEN_ID_STARTPADSETTINGS = 7,
};

void create_screen_main();
void tick_screen_main();

void create_screen_settings();
void tick_screen_settings();

void create_screen_intro();
void tick_screen_intro();

void create_screen_lansettings();
void tick_screen_lansettings();

void create_screen_wifisettings();
void tick_screen_wifisettings();

void create_screen_eventsettings();
void tick_screen_eventsettings();

void create_screen_startpadsettings();
void tick_screen_startpadsettings();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/