# IMS
PRODUCT_PACKAGES += \
    ims \
    imscmlibrary \
    imssettings \
    init.qti.ims.sh

PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/configs/ims/imscm.xml:system/etc/permissions/imscm.xml \
    $(LOCAL_PATH)/configs/ims/ims.xml:system/etc/permissions/ims.xml \
    $(LOCAL_PATH)/configs/ims/qti_permissions.xml:system/etc/permissions/qti_permissions.xml

PRODUCT_PROPERTY_OVERRIDES += \
    persist.radio.jbims=1 \
    persist.radio.ROTATION_ENABLE=1 \
    persist.radio.VT_ENABLE=1 \
    persist.radio.VT_HYBRID_ENABLE=1 \
    persist.radio.VT_USE_MDM_TIME=0

# Telephony-ext
PRODUCT_PACKAGES += telephony-ext ims-ext-common
PRODUCT_BOOT_JARS += telephony-ext
