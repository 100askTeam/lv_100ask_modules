/**
 * @file lv_100ask_modules.h
 *
 */

#ifndef LV_100ASK_MODULES_H
#define LV_100ASK_MODULES_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#if defined(LV_LVGL_H_INCLUDE_SIMPLE)
#include "lvgl.h"
#else
#include "../lvgl/lvgl.h"
#endif

#if defined(LV_100ASK_MODULES_PATH)
#define __LV_TO_STR_AUX(x) #x
#define __LV_TO_STR(x) __LV_TO_STR_AUX(x)
#include __LV_TO_STR(LV_100ASK_MODULES_PATH)
#undef __LV_TO_STR_AUX
#undef __LV_TO_STR
#elif defined(LV_100ASK_MODULES_INCLUDE_SIMPLE)
#include "lv_100ask_modules_conf.h"
#else
#include "../lv_100ask_modules_conf.h"
#endif

#include "src/lv_100ask_dbus_handler/lv_100ask_dbus_handler.h"
#include "src/lv_100ask_demo_assistive_touch/assistive_touch.h"
#include "src/lv_100ask_demo_init_icon/lv_100ask_demo_init_icon.h"
#include "src/lv_100ask_dbus_message_dispatch/lv_100ask_dbus_message_dispatch.h"

/*********************
 *      DEFINES
 *********************/
/*Test  lvgl version*/
#if LV_VERSION_CHECK(8, 0, 0) == 0
#error "lv_100ask_modules: Wrong lvgl version"
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/


/**********************
 *      MACROS
 **********************/


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* LV_100ASK_MODULES_H */
