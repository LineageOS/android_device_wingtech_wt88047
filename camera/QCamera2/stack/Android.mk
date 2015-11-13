LOCAL_PATH:= $(call my-dir)
include $(LOCAL_PATH)/mm-camera-interface/Android.mk
include $(LOCAL_PATH)/mm-jpeg-interface/Android.mk
include $(LOCAL_PATH)/mm-camera-test/Android.mk

LOCAL_ADDITIONAL_DEPENDENCIES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr
