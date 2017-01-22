# Camera
PRODUCT_PACKAGES += \
    camera.msm8916 \
    libmm-qcamera \
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
    media.stagefright.legacyencoder=true \
    media.stagefright.less-secure=true
