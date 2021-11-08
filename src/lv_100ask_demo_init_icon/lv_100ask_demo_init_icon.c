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
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include "lv_100ask_demo_init_icon.h"


#define ICON_PATH   ("/root/assets/icon/")

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
static void str_replace_all(char * str, char old_char, char new_char)
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
        //printf("str_icon_name: %s\n", str_icon_name);
        char str_dbus_path[64] = {0};
        sprintf(str_dbus_path, "/%s", str_icon_name);
        str_replace_all(str_dbus_path, '.', '/');
        dbus_method_call(str_icon_name, str_dbus_path, str_icon_name, "states", 1, 0);

        //char * str_dbus_path = malloc(sizeof(char) * strlen(str_icon_name) + 1);
        //free(str_dbus_path);
    }
}


static void lv_timer_update_time(lv_timer_t * timer)
{
    lv_obj_t * label = timer->user_data;

    // 获取系统时间
    char buf[32];
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);

    lv_label_set_text_fmt(label, "   %02d:%02d  %02d-%02d-%02d", info->tm_hour, info->tm_min, (info->tm_year + 2000 - 100), (info->tm_mon + 1), info->tm_mday);
}

static void lcd_top_widgets(lv_obj_t * parent)
{
    static lv_style_t obj_layout_style;   // 容器的样式

    lv_style_init(&obj_layout_style);
    lv_style_set_pad_all(&obj_layout_style, 0);
    lv_style_set_bg_opa(&obj_layout_style, 0);
    lv_style_set_text_font(&obj_layout_style, &lv_font_montserrat_16);
    lv_style_set_border_opa(&obj_layout_style, 0);
    lv_style_set_radius(&obj_layout_style, 0);
    lv_style_set_text_color(&obj_layout_style, lv_color_hex(0xffffff));

    /* Layout Init */
    lv_obj_t * panel = lv_obj_create(parent);
    lv_obj_set_size(panel,  LV_PCT(100), 30);
    lv_obj_add_style(panel, &obj_layout_style, 0);
    lv_obj_align(panel, LV_ALIGN_TOP_MID, 0, 5);

    /* 右上角小图标 */
    lv_obj_t * panel_icon = lv_obj_create(panel);
    lv_obj_set_size(panel_icon,  200, 25);
    lv_obj_set_layout(panel_icon, LV_LAYOUT_FLEX);
    lv_obj_set_style_base_dir(panel_icon, LV_BASE_DIR_RTL, 0);
    lv_obj_set_flex_flow(panel_icon, LV_FLEX_FLOW_ROW);
    lv_obj_align(panel_icon, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_add_style(panel_icon, &obj_layout_style, 0);

    lv_obj_t * label = lv_label_create(panel_icon);
    lv_label_set_text(label,  " ");

    lv_obj_t * label_bat = lv_label_create(panel_icon);
    lv_label_set_text(label_bat,  LV_SYMBOL_BATTERY_EMPTY);

    lv_obj_t * label_batchar = lv_label_create(label_bat);
    lv_obj_set_style_text_font(label_batchar, &lv_font_montserrat_14, 0);
    lv_label_set_text(label_batchar,  LV_SYMBOL_CHARGE);
    lv_obj_center(label_batchar);


    lv_obj_t * label_wifi = lv_label_create(panel_icon);
    lv_label_set_text(label_wifi, LV_SYMBOL_WIFI);

    lv_obj_t * label_time = lv_label_create(panel);
    lv_label_set_text(label_time, "  ");
    lv_obj_align(label_time, LV_ALIGN_LEFT_MID, 0, 0);

    lv_timer_t * timer = lv_timer_create(lv_timer_update_time, 1000,  label_time);
}


static void clean_screen_obj(lv_obj_t * parent)
{
    uint32_t i;
    for(i = 0; i < lv_obj_get_child_cnt(parent); i++)
    {
        lv_obj_t * child = lv_obj_get_child(parent, i);
        if (child != lv_scr_act())
            lv_obj_del(child);  // lv_obj_clean
        /*Do something with child*/
    }
}

//void lv_100ask_demo_init_icon(lv_anim_t * a)
void lv_100ask_demo_init_icon(void)
{
    struct dirent *de;                          // Pointer for directory entry
  	static lv_style_t cont_style;               // 中间图标区域，容器的样式
	static lv_style_t icon_style;               // 中间图标区域，容器中的图标的样式
    static lv_style_t obj_bottom_panel_style;   // 底部容器的样式

    if (lv_obj_get_child(lv_scr_act(), 0))
    lv_obj_del(lv_obj_get_child(lv_scr_act(), 0));
    lv_obj_t * screen = lv_obj_create(NULL);
    lv_scr_load(screen);

    //lv_style_reset(&cont_style);
    //lv_style_reset(&icon_style);
    //lv_style_reset(&obj_bottom_panel_style);

	/* 设置容器的样式 */
	lv_style_init(&cont_style);
    lv_style_set_bg_opa(&cont_style, 0);
    lv_style_set_border_opa(&cont_style, 0);
    lv_style_set_pad_column(&cont_style, ICON_COL_SPACE);
    lv_style_set_pad_row(&cont_style, ICON_ROW_SPACE);
    lv_style_set_pad_all(&cont_style, 0);


	/* 容器中的图标的样式 */
	lv_style_init(&icon_style);
    lv_style_set_text_opa(&icon_style, 0);
    lv_style_set_text_font(&icon_style,  &lv_font_montserrat_8);
	//lv_style_set_radius(&icon_style, 0);
    //lv_style_set_border_width(&icon_style, 1);

    /* 屏幕顶部状态栏区域 */
    lcd_top_widgets(lv_scr_act());

	/* 中间图标区域 */
    lv_obj_t * icon_cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(icon_cont, ICON_HOR_RES, ICON_VER_RES);
    lv_obj_set_layout(icon_cont, LV_LAYOUT_FLEX);
    lv_obj_set_style_base_dir(icon_cont, LV_BASE_DIR_LTR, 0);
    lv_obj_set_flex_flow(icon_cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_center(icon_cont);
    //lv_obj_align(icon_cont, LV_ALIGN_CENTER, 0, -10);
    lv_obj_add_style(icon_cont, &cont_style, 0);

    /* 底部面板区域 */
    lv_style_init(&obj_bottom_panel_style);
    lv_style_set_pad_all(&obj_bottom_panel_style, 0);
    lv_style_set_bg_opa(&obj_bottom_panel_style, LV_OPA_50);
    lv_style_set_pad_left(&obj_bottom_panel_style, 10);
    lv_style_set_pad_right(&obj_bottom_panel_style, 10);

    //lv_style_set_shadow_opa(&obj_bottom_panel_style, 0);
    lv_style_set_border_opa(&obj_bottom_panel_style, 0);
    lv_style_set_radius(&obj_bottom_panel_style, 22);

    /* Layout Init */
    lv_obj_t * bottom_panel = lv_obj_create(lv_scr_act());
    lv_obj_set_size(bottom_panel,  LV_PCT(70), 80);
    lv_obj_add_style(bottom_panel, &obj_bottom_panel_style, 0);
    lv_obj_set_layout(bottom_panel, LV_LAYOUT_FLEX);
    //lv_obj_set_style_base_dir(bottom_panel, LV_BASE_DIR_RTL, 0);
    lv_obj_set_flex_flow(bottom_panel, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(bottom_panel, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_align(bottom_panel, LV_ALIGN_BOTTOM_MID, 0, -15);

    // opendir() returns a pointer of DIR type. 
    //DIR *dr = opendir("assets/icon");
    DIR *dr = opendir("./");
  
    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory!\n");
        return 0;
    }
  
    lv_obj_t * img_gb;
    lv_obj_t * img_icon;
    lv_obj_t * label_icon;
    lv_obj_t * label_icon_name;
    lv_obj_t * img_bottom_icon;
    lv_obj_t * label_bottom_icon;
    // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html
    // for readdir()
    while ((de = readdir(dr)) != NULL)
    {
        if((strcmp(de->d_name,".") == 0)  ||\
           (strcmp(de->d_name,"..") == 0) ||\
           (strcmp((de->d_name + (strlen(de->d_name) - 4)) , ".png") != 0)||\
           (strcmp(de->d_name, "100ask_logo.png") == 0))
        {
            continue;
        }
        //if(strcmp((de->d_name + (strlen(de->d_name) - 4)) , "100ask_logo.png") == 0)  //只存取 .png 扩展名的文件名 
        //{
        //    continue;
        //}

        // 背景
        if(strcmp(de->d_name, "net.ask100.lvgl.bg.png") == 0)
        {
            img_gb = lv_img_create(lv_scr_act());
            lv_img_set_src(img_gb, de->d_name);
        }
        // 图标
        else
        {
            img_icon = lv_img_create(icon_cont);
            lv_img_set_src(img_icon, de->d_name);
            lv_obj_add_flag(img_icon, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_style(img_icon, &icon_style, 0);
            lv_obj_add_event_cb(img_icon, event_handler, LV_EVENT_CLICKED, NULL);

            img_bottom_icon = lv_img_create(bottom_panel);
            lv_img_set_src(img_bottom_icon, de->d_name);
            //lv_img_set_zoom(img_bottom_icon, 250);
            lv_obj_add_flag(img_bottom_icon, LV_OBJ_FLAG_CLICKABLE);
            lv_obj_add_style(img_bottom_icon, &icon_style, 0);
            lv_obj_add_event_cb(img_bottom_icon, event_handler, LV_EVENT_CLICKED, NULL);

            // 点击图标时调用的服务名(点击图标时父类提取)
            strip_ext(de->d_name);  // 去掉最后的后缀名 .png
            label_icon = lv_label_create(img_icon);
            lv_obj_set_width(label_icon, 64);
            lv_label_set_text(label_icon, de->d_name);

            // 点击图标时调用的服务名(点击图标时父类提取)
            label_bottom_icon = lv_label_create(img_bottom_icon);
            lv_obj_set_width(label_bottom_icon, 64);
            lv_label_set_text(label_bottom_icon, de->d_name);

            // 显示在图标下方的app名称
            label_icon_name = lv_label_create(lv_scr_act());
            lv_obj_set_style_text_font(label_icon_name, &lv_font_montserrat_14, 0);
            lv_obj_set_style_text_color(label_icon_name, lv_color_hex(0xffffff), 0);
            lv_obj_set_style_text_align(label_icon_name, LV_TEXT_ALIGN_CENTER, 0);
            lv_obj_set_width(label_icon_name, 64);
            lv_label_set_text(label_icon_name, strrchr(de->d_name, '.') + 1);
            lv_obj_align_to(label_icon_name, img_icon, LV_ALIGN_OUT_BOTTOM_MID, 0, 5);
            lv_obj_move_foreground(label_icon_name); // 防止被桌面背景图覆盖，将其移到前台           
        }

        //printf("%s\n", de->d_name);
    }
    lv_obj_move_background(img_gb);  // 将背景移动到后台
  
    closedir(dr);    
    return 0;
}


#endif
