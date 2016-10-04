# Copyright 2013 The Android Open Source Project
# Copyright 2015 The CyanogenMod Project

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := healthd_board_wt88047.cpp
LOCAL_MODULE := libhealthd.wt88047
LOCAL_C_INCLUDES := system/core/healthd
LOCAL_C_INCLUDES += system/core/healthd/include/healthd
LOCAL_CFLAGS := -Werror
include $(BUILD_STATIC_LIBRARY)
