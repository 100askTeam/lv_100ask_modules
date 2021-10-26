/**
 * @file assistive_touch.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_100ask_modules.h"

#if LV_USE_100ASK_DEMO_ASSISTIVE_TOUCH

#include <stdio.h>
#include <signal.h>
#include <dbus/dbus.h>
#include "assistive_touch.h"


static void assistive_touch_event_handler(lv_event_t * e);


static void assistive_touch_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
#if 1
    if(code == LV_EVENT_CLICKED) {
        lv_obj_set_style_img_recolor_opa(obj, LV_OPA_100, 0);
        lv_obj_set_style_img_recolor(obj, lv_color_hex(0x515151), 0);
        dbus_method_call("net.ask100.lvgl.main", "/net/ask100/lvgl/main", "net.ask100.lvgl.main", "states", 1, getpid());
    }
#endif
#if 0

    static int flag = 1;
    if(code == LV_EVENT_CLICKED) {
        if(1 == flag)
        {
            lv_obj_set_style_img_recolor_opa(obj, LV_OPA_100, 0);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0x515151), 0);
            flag = 0;
        }
        else
        {
            lv_obj_set_style_img_recolor_opa(obj, LV_OPA_100, 0);
            lv_obj_set_style_img_recolor(obj, lv_color_hex(0xbfbfbf), 0);
            flag = 1;
        }
    }
#endif    
}

void assistive_touch_init(void)
{
    lv_obj_t * img = lv_img_create(lv_scr_act());
	lv_img_set_src(img, "/root/assets/assistive_pic.png");
    lv_obj_align(img, LV_ALIGN_RIGHT_MID, -50, -200);
    lv_obj_add_flag(img, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(img, assistive_touch_event_handler, LV_EVENT_CLICKED, NULL);
}


#endif

