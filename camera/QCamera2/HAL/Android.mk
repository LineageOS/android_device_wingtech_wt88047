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

LOCAL_CFLAGS += -Wall -Wextra -Werror

#use media extension
#ifeq ($(TARGET_USES_MEDIA_EXTENSIONS), true)
LOCAL_CFLAGS += -DUSE_MEDIA_EXTENSIONS
#endif

#Debug logs are enabled
#LOCAL_CFLAGS += -DDISABLE_DEBUG_LOG

LOCAL_CFLAGS += -DDEFAULT_DENOISE_MODE_ON

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../stack/common \
    frameworks/native/include/media/openmax \
    $(call project-path-for,qcom-display)/libgralloc \
    $(call project-path-for,qcom-display)/libqdutils \
    $(call project-path-for,qcom-display)/libqservice \
    $(call project-path-for,qcom-media)/libstagefrighthw \
    system/media/camera/include \
    $(LOCAL_PATH)/../../mm-image-codec/qexif \
    $(LOCAL_PATH)/../../mm-image-codec/qomx_core \
    $(LOCAL_PATH)/../util \
    $(LOCAL_PATH)/wrapper \
    system/media/camera/include

ifeq ($(TARGET_TS_MAKEUP),true)
LOCAL_CFLAGS += -DTARGET_TS_MAKEUP
LOCAL_C_INCLUDES += $(LOCAL_PATH)/tsMakeuplib/include
endif

LOCAL_HEADER_LIBRARIES := generated_kernel_headers
LOCAL_SHARED_LIBRARIES := libcamera_client liblog libhardware libutils libcutils libdl libsensor
LOCAL_SHARED_LIBRARIES += libmmcamera_interface libmmjpeg_interface libqdMetaData
ifeq ($(TARGET_TS_MAKEUP),true)
LOCAL_SHARED_LIBRARIES += libts_face_beautify_hal libts_detected_face_hal
endif
LOCAL_MODULE_RELATIVE_PATH := hw
LOCAL_MODULE := camera.$(TARGET_BOARD_PLATFORM)
LOCAL_32_BIT_ONLY := true
LOCAL_VENDOR_MODULE := true
LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
