LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := sensors.$(TARGET_BOARD_PLATFORM)

LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_VENDOR_MODULE := true

LOCAL_CFLAGS := -Wall -Werror -DLOG_TAG=\"MultiHal\"

LOCAL_SRC_FILES := \
    multihal.cpp \
    SensorEventQueue.cpp \

LOCAL_SHARED_LIBRARIES := \
    libcutils \
    libdl \
    liblog \
    libutils \

LOCAL_STRIP_MODULE := false

include $(BUILD_SHARED_LIBRARY)
