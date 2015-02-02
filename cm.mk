# Copyright (C) 2014 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

$(call inherit-product, device/smartfren/rendang/full_rendang.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

PRODUCT_NAME := cm_rendang
BOARD_VENDOR := smartfren
PRODUCT_DEVICE := rendang

PRODUCT_GMS_CLIENTID_BASE := android-smartfren

TARGET_VENDOR_PRODUCT_NAME := RENDANG
TARGET_VENDOR_DEVICE_NAME := RENDANG
PRODUCT_BUILD_PROP_OVERRIDES += TARGET_DEVICE=RENDANG PRODUCT_NAME=RENDANG

ifeq ($(SIGN_BUILD),true)
# Signed builds gets a special boot animation because they are special.
PRODUCT_BOOTANIMATION := device/smartfren/rendang/bootanimation.zip
endif
