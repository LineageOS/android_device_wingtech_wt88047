LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := \
        QCamera2Factory.cpp \
        QCamera2Hal.cpp \
        QCamera2HWI.cpp \
        QCameraMem.cpp \
        ../util/QCameraQueue.cpp \
        ../util/QCameraCmdThread.cpp \
        QCameraStateMachine.cpp \
        QCameraChannel.cpp \
        QCameraStream.cpp \
        QCameraPostProc.cpp \
        QCamera2HWICallbacks.cpp \
        QCameraParameters.cpp \
        QCameraThermalAdapter.cpp \
        wrapper/QualcommCamera.cpp

LOCAL_CFLAGS = -Wall -Wextra -Werror -DDEFAULT_DENOISE_MODE_ON

LOCAL_C_INCLUDES := \
        $(LOCAL_PATH)/../stack/common \
        frameworks/native/include/media/openmax \
        $(call project-path-for,qcom-display)/libgralloc \
        $(call project-path-for,qcom-media)/libstagefrighthw \
        system/media/camera/include \
        $(LOCAL_PATH)/../../mm-image-codec/qexif \
        $(LOCAL_PATH)/../../mm-image-codec/qomx_core \
        $(LOCAL_PATH)/../util \
        $(LOCAL_PATH)/wrapper

LOCAL_C_INCLUDES += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
LOCAL_C_INCLUDES += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include/media
LOCAL_ADDITIONAL_DEPENDENCIES := $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr

LOCAL_SHARED_LIBRARIES := libcamera_client liblog libhardware libutils libcutils libdl
LOCAL_SHARED_LIBRARIES += libmmcamera_interface libmmjpeg_interface

LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw
LOCAL_MODULE := camera.$(TARGET_BOARD_PLATFORM)
LOCAL_32_BIT_ONLY := true
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
