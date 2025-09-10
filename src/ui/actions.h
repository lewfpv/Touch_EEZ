#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_enter_settings(lv_event_t * e);
extern void action_on_main_settings_btn_clicked(lv_event_t * e);
extern void action_on_settings_exit_btn_clicked(lv_event_t * e);
extern void action_change_bgcolor(lv_event_t * e);
extern void action_ch_panel_bg(lv_event_t * e);
extern void action_reset_racer_pedals(lv_event_t * e);
extern void action_on_settings_wifi_btn_clicked(lv_event_t * e);
extern void action_on_ssid_input_focused(lv_event_t * e);
extern void action_on_pwd_input_focused(lv_event_t * e);
extern void action_connect_to_wifi(lv_event_t * e);
extern void action_getjson(lv_event_t * e);
extern void action_on_settings_eventesettings_clicked(lv_event_t * e);
extern void action_on_eventid_input_focused(lv_event_t * e);
extern void action_on_settings_startpad_btn_clicked(lv_event_t * e);
extern void action_startpad_led_switch(lv_event_t * e);
extern void action_hide_finish_panel(lv_event_t * e);
extern void action_on_panel1_touch(lv_event_t * e);
extern void action_on_panel2_touch(lv_event_t * e);
extern void action_on_panel3_touch(lv_event_t * e);
extern void action_on_panel4_touch(lv_event_t * e);
extern void action_startpad_all_led_slider(lv_event_t * e);
extern void action_on_settings_lan_btn_clicked(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/