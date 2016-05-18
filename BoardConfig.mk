#
# Copyright (C) 2015 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

FORCE_32_BIT := true

include device/cyanogen/msm8916-common/BoardConfigCommon.mk
DEVICE_PATH := device/wingtech/wt88047
TARGET_SPECIFIC_HEADER_PATH := $(DEVICE_PATH)/include

# Bootloader
TARGET_BOOTLOADER_BOARD_NAME :=

# Kernel
BOARD_CUSTOM_BOOTIMG_MK := $(DEVICE_PATH)/mkbootimg.mk
BOARD_KERNEL_CMDLINE += phy-msm-usb.floated_charger_enable=1
TARGET_KERNEL_SOURCE := kernel/wingtech/msm8916
TARGET_KERNEL_CONFIG := cyanogenmod_wt88047_defconfig

# CPU
TARGET_CPU_CORTEX_A53 := true

# WT88047 init
TARGET_LIBINIT_MSM8916_DEFINES_FILE := $(DEVICE_PATH)/init/init_wt88047.cpp
TARGET_UNIFIED_DEVICE := true

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(DEVICE_PATH)/bluetooth

# Display
TARGET_CONTINUOUS_SPLASH_ENABLED := false

# Charger
BOARD_CHARGER_DISABLE_INIT_BLANK := true
BOARD_HAL_STATIC_LIBRARIES := libhealthd.wt88047

# Camera
BOARD_CAMERA_SENSORS := \
    ov2680_5987fhq \
    ov8865_q8v18a \
    ov2680_skuhf
TARGET_USE_VENDOR_CAMERA_EXT := true
USE_DEVICE_SPECIFIC_CAMERA := true

# DPM NSRM Feature
TARGET_LDPRELOAD := libNimsWrap.so

# Flags
COMMON_GLOBAL_CFLAGS += -DNO_SECURE_DISCARD -DCONFIG_WT88047_CAMERA -DCAMERA_VENDOR_L_COMPAT

# GPS
USE_DEVICE_SPECIFIC_GPS := true
TARGET_NO_RPC := true

# Lights
TARGET_PROVIDES_LIBLIGHT := true

# Partitions
BOARD_FLASH_BLOCK_SIZE := 131072
BOARD_BOOTIMAGE_PARTITION_SIZE := 33554432
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_CACHEIMAGE_PARTITION_SIZE := 335544320
BOARD_PERSISTIMAGE_PARTITION_SIZE := 33554432
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 33554432
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1073741824
BOARD_USERDATAIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_USERDATAIMAGE_PARTITION_SIZE := 5939100672

# Recovery
TARGET_RECOVERY_FSTAB := $(DEVICE_PATH)/rootdir/etc/fstab.qcom
TARGET_USERIMAGES_USE_EXT4 := true
TARGET_USERIMAGES_USE_F2FS := true

TARGET_SYSTEM_PROP += $(DEVICE_PATH)/system.prop

BOARD_SEPOLICY_DIRS += $(DEVICE_PATH)/sepolicy

# inherit from the proprietary version
-include vendor/wingtech/wt88047/BoardConfigVendor.mk
