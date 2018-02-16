# Shims
TARGET_LD_SHIM_LIBS += \
    /system/vendor/bin/mm-qcamera-daemon|libshim_camera.so \
    /system/vendor/lib/libmmcamera2_imglib_modules.so|libshim_camera.so \
    /system/vendor/lib/lib-imsvt.so|libshims_ims.so
