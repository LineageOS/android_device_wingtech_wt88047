# Kernel
BOARD_CUSTOM_BOOTIMG_MK := device/wingtech/wt88047/mkbootimg.mk
BOARD_KERNEL_CMDLINE += sched_enable_hmp=1 phy-msm-usb.floated_charger_enable=1
TARGET_KERNEL_SOURCE := kernel/wingtech/msm8916
TARGET_KERNEL_CONFIG := cyanogenmod_wt88047_defconfig
