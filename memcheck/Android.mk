LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE_TAGS := optional
LOCAL_C_INCLUDES := system/core/init
LOCAL_CFLAGS := -Wall
LOCAL_STATIC_LIBRARIES := liblog libcutils
LOCAL_SRC_FILES := memcheck.c
LOCAL_MODULE := memcheck
include $(BUILD_EXECUTABLE)
