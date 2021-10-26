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


#include "src/lv_100ask_dbus_handler/lv_100ask_dbus_handler.h"
#include "src/lv_100ask_demo_assistive_touch/assistive_touch.h"
#include "src/lv_100ask_demo_init_icon/lv_100ask_demo_init_icon.h"

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
