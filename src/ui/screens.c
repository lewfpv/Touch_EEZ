#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_add_event_cb(obj, action_hide_finish_panel, LV_EVENT_SCREEN_LOAD_START, (void *)0);
    {
        lv_obj_t *parent_obj = obj;
        {
            // P1
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.p1 = obj;
            lv_obj_set_pos(obj, 10, 10);
            lv_obj_set_size(obj, 385, 225);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // r1text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.r1text = obj;
                    lv_obj_set_pos(obj, -15, -29);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_hi_jack, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "R1");
                }
                {
                    // pilot1text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.pilot1text = obj;
                    lv_obj_set_pos(obj, 39, 67);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_lv_font_avengeance_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "pilot1text");
                }
            }
        }
        {
            // P2
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.p2 = obj;
            lv_obj_set_pos(obj, 405, 10);
            lv_obj_set_size(obj, 385, 225);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // r3text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.r3text = obj;
                    lv_obj_set_pos(obj, 260, -29);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_hi_jack, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "R3");
                }
                {
                    // pilot2text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.pilot2text = obj;
                    lv_obj_set_pos(obj, 35, 67);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_lv_font_avengeance_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "pilot2text");
                }
            }
        }
        {
            // P3
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.p3 = obj;
            lv_obj_set_pos(obj, 10, 245);
            lv_obj_set_size(obj, 385, 225);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // r6text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.r6text = obj;
                    lv_obj_set_pos(obj, -15, -29);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_hi_jack, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "R6");
                }
                {
                    // pilot3text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.pilot3text = obj;
                    lv_obj_set_pos(obj, 35, 67);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_lv_font_avengeance_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "pilot3text");
                }
            }
        }
        {
            // P4
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.p4 = obj;
            lv_obj_set_pos(obj, 405, 245);
            lv_obj_set_size(obj, 385, 225);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // r7text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.r7text = obj;
                    lv_obj_set_pos(obj, 263, -29);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_hi_jack, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "R7");
                }
                {
                    // pilot4text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.pilot4text = obj;
                    lv_obj_set_pos(obj, 34, 67);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &ui_font_lv_font_avengeance_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "pilot4text");
                }
            }
        }
        {
            // settings_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.settings_btn = obj;
            lv_obj_set_pos(obj, 476, 408);
            lv_obj_set_size(obj, 59, 50);
            lv_obj_add_event_cb(obj, action_on_main_settings_btn_clicked, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50565b), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "\uF013");
                }
            }
        }
        {
            // reset_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.reset_btn = obj;
            lv_obj_set_pos(obj, 332, 408);
            lv_obj_set_size(obj, 136, 50);
            lv_obj_add_event_cb(obj, action_reset_racer_pedals, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50565b), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Reset");
                }
            }
        }
        {
            // finishpanel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.finishpanel = obj;
            lv_obj_set_pos(obj, 138, -8);
            lv_obj_set_size(obj, 515, 406);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_CLICKABLE|LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // finishline0
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.finishline0 = obj;
                    lv_obj_set_pos(obj, 0, 110);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "finishline0");
                }
                {
                    // finishline1
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.finishline1 = obj;
                    lv_obj_set_pos(obj, 0, 170);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "finishline1");
                }
                {
                    // finishline2
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.finishline2 = obj;
                    lv_obj_set_pos(obj, 0, 230);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "finishline2");
                }
                {
                    // finishline3
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.finishline3 = obj;
                    lv_obj_set_pos(obj, 0, 290);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_set_style_text_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "finishline3");
                }
                {
                    lv_obj_t *obj = lv_image_create(parent_obj);
                    lv_obj_set_pos(obj, 13, -23);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_image_set_src(obj, &img_finishflag);
                }
            }
        }
        {
            // heattitle_panel
            lv_obj_t *obj = lv_obj_create(parent_obj);
            objects.heattitle_panel = obj;
            lv_obj_set_pos(obj, 226, -9);
            lv_obj_set_size(obj, 348, 72);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // heattitle_text
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.heattitle_text = obj;
                    lv_obj_set_pos(obj, 35, 2);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Qualification Group 1");
                }
            }
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
}

void create_screen_settings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.settings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 12, 12);
            lv_obj_set_size(obj, 776, 456);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 295, -8);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Settings");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 678, 408);
            lv_obj_set_size(obj, 100, 50);
            lv_obj_add_event_cb(obj, action_on_settings_exit_btn_clicked, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Exit");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 257, 155);
            lv_obj_set_size(obj, 285, 40);
            lv_obj_add_event_cb(obj, action_on_settings_wifi_btn_clicked, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Wifi");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 258, 220);
            lv_obj_set_size(obj, 285, 40);
            lv_obj_add_event_cb(obj, action_on_settings_eventesettings_clicked, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Event");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 258, 285);
            lv_obj_set_size(obj, 285, 40);
            lv_obj_add_event_cb(obj, action_on_settings_startpad_btn_clicked, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Startpad");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 258, 90);
            lv_obj_set_size(obj, 285, 40);
            lv_obj_add_event_cb(obj, action_on_settings_lan_btn_clicked, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Lan");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 258, 350);
            lv_obj_set_size(obj, 285, 40);
            lv_obj_add_event_cb(obj, action_on_settings_about_btn_clicked, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "About");
                }
            }
        }
    }
    
    tick_screen_settings();
}

void tick_screen_settings() {
}

void create_screen_intro() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.intro = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_image_create(parent_obj);
            lv_obj_set_pos(obj, 241, 112);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_image_set_src(obj, &img_tdlogo);
        }
    }
    
    tick_screen_intro();
}

void tick_screen_intro() {
}

void create_screen_lansettings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.lansettings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 13, 12);
            lv_obj_set_size(obj, 776, 456);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 262, -10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Lan settings");
                }
            }
        }
        {
            // lan_current_ip
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.lan_current_ip = obj;
            lv_obj_set_pos(obj, 323, 223);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "IP: 0.0.0.0");
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 716, 25);
            lv_obj_set_size(obj, 59, 50);
            lv_obj_add_event_cb(obj, action_on_main_settings_btn_clicked, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50565b), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "\uF013");
                }
            }
        }
    }
    
    tick_screen_lansettings();
}

void tick_screen_lansettings() {
}

void create_screen_wifisettings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.wifisettings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 12, 12);
            lv_obj_set_size(obj, 776, 456);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 262, -10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Wifi settings");
                }
            }
        }
        {
            // ssid
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.ssid = obj;
            lv_obj_set_pos(obj, 197, 97);
            lv_obj_set_size(obj, 272, 33);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "wifi2");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, action_on_ssid_input_focused, LV_EVENT_FOCUSED, (void *)0);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 115, 102);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "SSID");
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 32, 156);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "PASSWORD");
        }
        {
            // pwd
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.pwd = obj;
            lv_obj_set_pos(obj, 198, 152);
            lv_obj_set_size(obj, 272, 33);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "12345677");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, action_on_pwd_input_focused, LV_EVENT_FOCUSED, (void *)0);
        }
        {
            // keyboard1
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.keyboard1 = obj;
            lv_obj_set_pos(obj, 0, 209);
            lv_obj_set_size(obj, 800, 271);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // connect_btn
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.connect_btn = obj;
            lv_obj_set_pos(obj, 484, 97);
            lv_obj_set_size(obj, 104, 88);
            lv_obj_add_event_cb(obj, action_connect_to_wifi, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    // connect_btn_label
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    objects.connect_btn_label = obj;
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Connect");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 716, 25);
            lv_obj_set_size(obj, 59, 50);
            lv_obj_add_event_cb(obj, action_on_main_settings_btn_clicked, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50565b), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "\uF013");
                }
            }
        }
        {
            // ip_addr_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.ip_addr_label = obj;
            lv_obj_set_pos(obj, 32, 30);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "IP: 0.0.0.0");
        }
    }
    
    tick_screen_wifisettings();
}

void tick_screen_wifisettings() {
}

void create_screen_eventsettings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.eventsettings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 12, 12);
            lv_obj_set_size(obj, 776, 456);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 250, -9);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Event settings");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 116, 103);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "EVENT ID");
        }
        {
            // eventid
            lv_obj_t *obj = lv_textarea_create(parent_obj);
            objects.eventid = obj;
            lv_obj_set_pos(obj, 243, 103);
            lv_obj_set_size(obj, 257, 75);
            lv_textarea_set_max_length(obj, 128);
            lv_textarea_set_text(obj, "z1q8o");
            lv_textarea_set_one_line(obj, false);
            lv_textarea_set_password_mode(obj, false);
            lv_obj_add_event_cb(obj, action_on_eventid_input_focused, LV_EVENT_FOCUSED, (void *)0);
        }
        {
            // keyboard2
            lv_obj_t *obj = lv_keyboard_create(parent_obj);
            objects.keyboard2 = obj;
            lv_obj_set_pos(obj, 0, 209);
            lv_obj_set_size(obj, 800, 271);
            lv_obj_set_style_align(obj, LV_ALIGN_DEFAULT, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            lv_obj_set_pos(obj, 529, 103);
            lv_obj_set_size(obj, 113, 75);
            lv_obj_add_event_cb(obj, action_getjson, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "GetJson");
                }
            }
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 716, 25);
            lv_obj_set_size(obj, 59, 50);
            lv_obj_add_event_cb(obj, action_on_main_settings_btn_clicked, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50565b), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "\uF013");
                }
            }
        }
    }
    
    tick_screen_eventsettings();
}

void tick_screen_eventsettings() {
}

void create_screen_startpadsettings() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.startpadsettings = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 12, 12);
            lv_obj_set_size(obj, 776, 456);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 225, -9);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Startpad settings");
                }
            }
        }
        {
            // startpad_led_sw
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.startpad_led_sw = obj;
            lv_obj_set_pos(obj, 335, 104);
            lv_obj_set_size(obj, 131, 54);
            lv_obj_add_event_cb(obj, action_startpad_led_switch, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_state(obj, LV_STATE_CHECKED);
        }
        {
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 720, 408);
            lv_obj_set_size(obj, 59, 50);
            lv_obj_add_event_cb(obj, action_on_main_settings_btn_clicked, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50565b), LV_PART_MAIN | LV_STATE_DEFAULT);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "\uF013");
                }
            }
        }
        {
            // startpad_all_led_slider
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.startpad_all_led_slider = obj;
            lv_obj_set_pos(obj, 228, 259);
            lv_obj_set_size(obj, 344, 40);
            lv_slider_set_value(obj, 25, LV_ANIM_OFF);
            lv_obj_add_event_cb(obj, action_startpad_all_led_slider, LV_EVENT_RELEASED, (void *)0);
        }
    }
    
    tick_screen_startpadsettings();
}

void tick_screen_startpadsettings() {
}

void create_screen_about() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.about = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 12, 12);
            lv_obj_set_size(obj, 776, 456);
            lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 316, -10);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "About");
                }
                {
                    lv_obj_t *obj = lv_button_create(parent_obj);
                    objects.obj4 = obj;
                    lv_obj_set_pos(obj, 685, 374);
                    lv_obj_set_size(obj, 59, 50);
                    lv_obj_add_event_cb(obj, action_on_main_settings_btn_clicked, LV_EVENT_PRESSED, (void *)0);
                    lv_obj_set_style_bg_color(obj, lv_color_hex(0xff50565b), LV_PART_MAIN | LV_STATE_DEFAULT);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "\uF013");
                        }
                    }
                }
            }
        }
        {
            // version
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.version = obj;
            lv_obj_set_pos(obj, 377, 123);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Text");
        }
        {
            // ota_button
            lv_obj_t *obj = lv_button_create(parent_obj);
            objects.ota_button = obj;
            lv_obj_set_pos(obj, 341, 171);
            lv_obj_set_size(obj, 119, 50);
            lv_obj_add_event_cb(obj, action_ota, LV_EVENT_PRESSED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "OTA Update");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 307, 89);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_label_set_text(obj, "Current firmware version:");
        }
        {
            // ota_spinner
            lv_obj_t *obj = lv_spinner_create(parent_obj);
            objects.ota_spinner = obj;
            lv_obj_set_pos(obj, 360, 286);
            lv_obj_set_size(obj, 80, 80);
            lv_spinner_set_anim_params(obj, 1000, 60);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
    }
    
    tick_screen_about();
}

void tick_screen_about() {
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_settings,
    tick_screen_intro,
    tick_screen_lansettings,
    tick_screen_wifisettings,
    tick_screen_eventsettings,
    tick_screen_startpadsettings,
    tick_screen_about,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_settings();
    create_screen_intro();
    create_screen_lansettings();
    create_screen_wifisettings();
    create_screen_eventsettings();
    create_screen_startpadsettings();
    create_screen_about();
}
