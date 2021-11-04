/**
 * @file app_general_template.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_100ask_modules.h"

#if LV_USE_100ASK_APP_GENERAL_TEMPLATE

#include <stdio.h>
#include "app_general_template.h"


void app_general_template_init(const char * titel)
{
    lv_obj_t * obj_layout;
    static lv_style_t obj_layout_style;   // 容器的样式

    lv_style_init(&obj_layout_style);
    //lv_style_set_pad_all(&obj_layout_style, 0);
    //lv_style_set_bg_opa(&obj_layout_style, 0);
    //lv_style_set_shadow_opa(&obj_layout_style, 0);
    lv_style_set_border_opa(&obj_layout_style, 0);


    /* Layout Init */
    obj_layout = lv_obj_create(lv_scr_act());
    lv_obj_set_size(obj_layout,  LV_PCT(100), LV_PCT(100));
    lv_obj_set_layout(obj_layout, LV_LAYOUT_FLEX);
    lv_obj_set_style_base_dir(obj_layout, LV_BASE_DIR_RTL, 0);
    lv_obj_set_flex_flow(obj_layout, LV_FLEX_FLOW_COLUMN);
    lv_obj_center(obj_layout);
    lv_obj_add_style(obj_layout, &obj_layout_style, 0);

    /* Create title */
    lv_obj_t * label_title = lv_label_create(obj_layout);
    lv_obj_set_width(label_title, LV_PCT(100));
    lv_obj_set_style_text_font(label_title, &lv_font_montserrat_28, 0);
    lv_obj_set_style_text_align(label_title, LV_TEXT_ALIGN_CENTER, 0);
    //lv_label_set_recolor(label_title, true);                      /*Enable re-coloring by commands in the text*/
    lv_label_set_text(label_title, titel);
    lv_obj_align(label_title, LV_ALIGN_CENTER, 0, 0); //lv_obj_center(label_title);

}


#endif

