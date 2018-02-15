# GPS
PRODUCT_PACKAGES += \
    gps.msm8916

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/gps/flp.conf:system/vendor/etc/flp.conf \
    $(LOCAL_PATH)/gps/gps.conf:system/vendor/etc/gps.conf \
    $(LOCAL_PATH)/gps/izat.conf:system/vendor/etc/izat.conf \
    $(LOCAL_PATH)/gps/sap.conf:system/vendor/etc/sap.conf

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.location.gps.xml:system/vendor/etc/permissions/android.hardware.location.gps.xml
