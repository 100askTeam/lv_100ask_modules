CSRCS += lv_100ask_boot_animation.c

DEPPATH += --dep-path $(LVGL_DIR)/$(MODULES_DIR_NAME)/src/lv_100ask_boot_animation/
VPATH += :$(LVGL_DIR)/$(MODULES_DIR_NAME)/src/lv_100ask_boot_animation/

CFLAGS += "-I$(LVGL_DIR)/$(MODULES_DIR_NAME)/src/lv_100ask_boot_animation/"
