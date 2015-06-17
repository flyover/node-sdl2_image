LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := node-sdl2_image
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(subst \,/,$(shell cd $(LOCAL_PATH) && node -e "require('nan')"))
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)
LOCAL_SRC_FILES := node-sdl2_image.cc
LOCAL_STATIC_LIBRARIES := node
LOCAL_STATIC_LIBRARIES += node-sdl2
LOCAL_SHARED_LIBRARIES := SDL2
LOCAL_SHARED_LIBRARIES += SDL2_image
include $(BUILD_STATIC_LIBRARY)

