# Kernel
TARGET_KERNEL_SOURCE := kernel/cyanogen/msm8916
TARGET_KERNEL_CONFIG := lineageos_wt88047_defconfig
BOARD_KERNEL_CMDLINE += sched_enable_hmp=1 phy-msm-usb.floated_charger_enable=1
