LOCAL_32_BIT_ONLY := true
ifeq ($(TARGET_ARCH),$(filter $(TARGET_ARCH),arm arm64))
  include $(call all-subdir-makefiles)
endif
