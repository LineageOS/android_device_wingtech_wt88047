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

# Enables CSVT
TARGET_USES_CSVT := true

# Bootloader
TARGET_BOOTLOADER_BOARD_NAME :=

# Kernel
BOARD_CUSTOM_BOOTIMG_MK := $(DEVICE_PATH)/mkbootimg.mk
BOARD_KERNEL_CMDLINE += phy-msm-usb.floated_charger_enable=1
TARGET_KERNEL_SOURCE := kernel/cyanogen/msm8916
TARGET_KERNEL_CONFIG := cyanogenmod_wt88047_defconfig

# CPU
TARGET_CPU_CORTEX_A53 := true

# WT88047 init
TARGET_LIBINIT_DEFINES_FILE := $(DEVICE_PATH)/init/init_wt88047.c
TARGET_UNIFIED_DEVICE := true

# Bluetooth
BOARD_BLUETOOTH_BDROID_BUILDCFG_INCLUDE_DIR := $(DEVICE_PATH)/bluetooth

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
COMMON_GLOBAL_CFLAGS += -DNO_SECURE_DISCARD

# FM
AUDIO_FEATURE_ENABLED_FM := true
TARGET_QCOM_NO_FM_FIRMWARE := true

# Fonts
EXTENDED_FONT_FOOTPRINT := true

# GPS
TARGET_GPS_HAL_PATH := $(DEVICE_PATH)/gps
TARGET_NO_RPC := true

# Lights
TARGET_PROVIDES_LIBLIGHT := true

# Partitions
BOARD_CACHEIMAGE_FILE_SYSTEM_TYPE := ext4
BOARD_FLASH_BLOCK_SIZE := 131072
BOARD_BOOTIMAGE_PARTITION_SIZE := 33554432
BOARD_CACHEIMAGE_PARTITION_SIZE := 335544320
BOARD_PERSISTIMAGE_PARTITION_SIZE := 33554432
BOARD_RECOVERYIMAGE_PARTITION_SIZE := 33554432
BOARD_SYSTEMIMAGE_PARTITION_SIZE := 1073741824
BOARD_USERDATAIMAGE_PARTITION_SIZE := 5939100672

# Recovery
TARGET_RECOVERY_FSTAB := $(DEVICE_PATH)/rootdir/etc/fstab.qcom

TARGET_SYSTEM_PROP += $(DEVICE_PATH)/system.prop

BOARD_SEPOLICY_DIRS += \
    $(DEVICE_PATH)/sepolicy

BOARD_SEPOLICY_UNION += \
    memcheck.te \
    irsc_util.te \
    mm-qcamerad.te \
    system_server.te \
    file_contexts

# inherit from the proprietary version
-include vendor/wingtech/wt88047/BoardConfigVendor.mk
