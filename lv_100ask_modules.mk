export MODULES_DIR_NAME ?= lv_100ask_modules

include $(LVGL_DIR)/$(MODULES_DIR_NAME)/src/lv_100ask_dbus_handler/lv_100ask_dbus_handler.mk
include $(LVGL_DIR)/$(MODULES_DIR_NAME)/src/lv_100ask_dbus_message_dispatch/lv_100ask_dbus_message_dispatch.mk
include $(LVGL_DIR)/$(MODULES_DIR_NAME)/src/lv_100ask_demo_assistive_touch/assistive_touch.mk
include $(LVGL_DIR)/$(MODULES_DIR_NAME)/src/lv_100ask_demo_init_icon/lv_100ask_demo_init_icon.mk
include $(LVGL_DIR)/$(MODULES_DIR_NAME)/src/lv_100ask_boot_animation/lv_100ask_boot_animation.mk
#include $(LVGL_DIR)/$(MODULES_DIR_NAME)/src/lv_100ask_app_general_template/app_general_template.mk