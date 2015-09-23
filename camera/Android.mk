ifeq ($(call my-dir),$(call project-path-for,qcom-camera))
MM_V4L2_DRIVER_LIST += msm8960
MM_V4L2_DRIVER_LIST += msm8974
MM_V4L2_DRIVER_LIST += msm8226
MM_V4L2_DRIVER_LIST += msm8610
MM_V4L2_DRIVER_LIST += msm_bronze
MM_V4L2_DRIVER_LIST += msm8916

LOCAL_32_BIT_ONLY := true
ifeq ($(call is-board-platform-in-list,$(MM_V4L2_DRIVER_LIST)),true)
    ifneq ($(BUILD_TINY_ANDROID),true)
      include $(call all-subdir-makefiles)
    endif
endif
endif
