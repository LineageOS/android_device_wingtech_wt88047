# Camera
PRODUCT_PACKAGES += \
    camera.msm8916 \
    libmm-qcamera \
    libshim_camera \
    libboringssl-compat \
    Snap

# Build libstlport for vendor blobs
PRODUCT_PACKAGES += \
    libstlport

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.camera.flash-autofocus.xml:system/etc/permissions/android.hardware.camera.flash-autofocus.xml \
    frameworks/native/data/etc/android.hardware.camera.front.xml:system/etc/permissions/android.hardware.camera.front.xml

# Properties
PRODUCT_PROPERTY_OVERRIDES += \
    persist.camera.cpp.duplication=false \
    persist.camera.hal.debug.mask=0 \
    persist.ts.postmakeup=true \
    persist.ts.rtmakeup=true \
    media.stagefright.legacyencoder=true \
    media.stagefright.less-secure=true \
    ro.camera.sensors=ov8865_q8v18a,ov2680_skuhf,ov2680_5987fhq
