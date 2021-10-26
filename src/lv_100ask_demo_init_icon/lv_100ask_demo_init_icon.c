/**
 * @file lv_100ask_demo_get_icon.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "../../lv_100ask_modules.h"

#if LV_USE_100ASK_DEMO_INIT_ICON

#include <stdio.h>
#include <dirent.h>
#include "lv_100ask_demo_init_icon.h"


// 去掉最后的后缀名
static void strip_ext(char *fname)
{
    char *end = fname + strlen(fname);

    while (end > fname && *end != '.') {
        --end;
    }

    if (end > fname) {
        *end = '\0';
    }
}


// 替换给定字符串中所有出现的字符。
void str_replace_all(char * str, char old_char, char new_char)
{
    int i = 0;

    /* Run till end of string */
    while(str[i] != '\0')
    {
        /* If occurrence of character is found */
        if(str[i] == old_char)
        {
            str[i] = new_char;
        }
        i++;
    }
}

static void event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * obj = lv_event_get_target(e);
    //char * str_icon_name = lv_event_get_user_data(e);

    if(code == LV_EVENT_CLICKED) {
        char * str_icon_name = lv_label_get_text(lv_obj_get_child(obj, 0));
        char * str_dbus_path = malloc(sizeof(char) * strlen(str_icon_name) + 1);
        sprintf(str_dbus_path, "/%s", str_icon_name);
        str_replace_all(str_dbus_path, '.', '/');
        dbus_method_call(str_icon_name, str_dbus_path, str_icon_name, "states", 1);
        free(str_dbus_path);
    }
}

#define ICON_SIZE           (64)
#define ICON_ROW_COUNT      (4)
#define ICON_COLUNM_COUNT   (6)
#define ICON_PAD_TOP        (40)
#define ICON_PAD_BOTTOM     (40)
#define ICON_PAD_LEFT       (115)
#define ICON_PAD_RIGHT      (115)

#define ICON_ROW_SPACE      (60)
#define ICON_COL_SPACE      (90)//((ICON_HOR_RES - (ICON_SIZE * ICON_COLUNM_COUNT)) / (ICON_COLUNM_COUNT - 1))
#define ICON_HOR_RES        (4 + (ICON_SIZE * ICON_COLUNM_COUNT) + (ICON_COL_SPACE * (ICON_COLUNM_COUNT - 1)))//((LV_HOR_RES - ICON_PAD_LEFT - ICON_PAD_RIGHT))        // 列间距
#define ICON_VER_RES        (4 + (ICON_SIZE * ICON_ROW_COUNT) + (ICON_ROW_SPACE * (ICON_ROW_COUNT - 1)))//((LV_VER_RES - ICON_PAD_TOP  - ICON_PAD_BOTTOM))       // 行间距


void lv_100ask_demo_init_icon(void)
{
    struct dirent *de;  // Pointer for directory entry
  	static lv_style_t cont_style;   // 容器的样式
	static lv_style_t icon_style;    // 容器中的图标的样式

	/* 设置容器的样式 */
	lv_style_init(&cont_style);
    lv_style_set_bg_opa(&cont_style, 0);
    lv_style_set_border_opa(&cont_style, 0);
    lv_style_set_pad_column(&cont_style, ICON_COL_SPACE);
    lv_style_set_pad_row(&cont_style, ICON_ROW_SPACE);
    lv_style_set_pad_all(&cont_style, 0);
#if 0
    //lv_style_set_flex_flow(&cont_style, LV_FLEX_FLOW_ROW_WRAP);
    //lv_style_set_flex_main_place(&cont_style, LV_FLEX_ALIGN_SPACE_EVENLY);
    //lv_style_set_layout(&cont_style, LV_LAYOUT_FLEX);
    //lv_style_set_flex_flow(&cont_style, LV_FLEX_FLOW_ROW_WRAP);
    //lv_style_set_base_dir(&cont_style, LV_BASE_DIR_LTR);
    //lv_style_set_flex_flow(&cont_style, LV_FLEX_FLOW_ROW_WRAP);
    lv_style_set_pad_top(&cont_style, ICON_PAD_TOP);
    lv_style_set_pad_bottom(&cont_style, ICON_PAD_BOTTOM);
    lv_style_set_pad_right(&cont_style, ICON_PAD_LEFT);
    lv_style_set_pad_left(&cont_style, ICON_PAD_RIGHT);
#endif


	/* 容器中的图标的样式 */
	lv_style_init(&icon_style);
    lv_style_set_text_opa(&icon_style, 0);
    lv_style_set_text_font(&icon_style,  &lv_font_montserrat_8);
	//lv_style_set_radius(&icon_style, 0);
    //lv_style_set_border_width(&icon_style, 1);

	/* 使用 flex 创建容器 */
    lv_obj_t * icon_cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(icon_cont, ICON_HOR_RES, ICON_VER_RES);
    lv_obj_set_layout(icon_cont, LV_LAYOUT_FLEX);
    lv_obj_set_style_base_dir(icon_cont, LV_BASE_DIR_LTR, 0);
    lv_obj_set_flex_flow(icon_cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_center(icon_cont);
    lv_obj_add_style(icon_cont, &cont_style, 0);

    // opendir() returns a pointer of DIR type. 
    DIR *dr = opendir(".");
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory!\n");
        return 0;
    }
  
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL)
    {
        if(strcmp(de->d_name,".")==0||strcmp(de->d_name,"..")==0)
        {
            continue;
        }
        if(strcmp((de->d_name + (strlen(de->d_name) - 4)) , ".png") != 0)  //只存取 .png 扩展名的文件名 
        {
            continue;
        }

        if(strcmp(de->d_name, "lvgl_100ask_bg.png") == 0)
        {
            lv_obj_t * img_gb = lv_img_create(lv_scr_act());
            lv_img_set_src(img_gb, de->d_name);
        }
        else
        {
            lv_obj_t * img_icon = lv_img_create(icon_cont);
            lv_img_set_src(img_icon, de->d_name);
            lv_obj_add_flag(img_icon, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_style(img_icon, &icon_style, 0);
            lv_obj_add_event_cb(img_icon, event_handler, LV_EVENT_CLICKED, NULL);

            strip_ext(de->d_name);// 去掉最后的后缀名
            lv_obj_t * label_icon_name = lv_label_create(img_icon);
            lv_obj_set_width(label_icon_name, 64);
            lv_label_set_text(label_icon_name, de->d_name);         
        }
        //printf("%s\n", de->d_name);
    }

    lv_obj_move_foreground(icon_cont);
  
    closedir(dr);    
    return 0;
}


#endif
