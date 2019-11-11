# Audio
PRODUCT_PROPERTY_OVERRIDES += \
    ro.vendor.audio.sdk.fluencetype=fluence \
    persist.vendor.audio.fluence.voicecall=true \
    persist.vendor.audio.fluence.voicerec=false \
    persist.vendor.audio.fluence.speaker=false

# Camera
PRODUCT_PROPERTY_OVERRIDES += \
    persist.camera.cpp.duplication=false \
    persist.camera.hal.debug.mask=0 \
    ro.camera.sensors=ov8865_q8v18a,ov2680_skuhf,ov2680_5987fhq

# Display
PRODUCT_PROPERTY_OVERRIDES += \
    ro.sf.lcd_density=320

# Factory Reset Protection
PRODUCT_PROPERTY_OVERRIDES += \
    ro.frp.pst=/dev/block/platform/soc.0/7824900.sdhci/by-name/config

# Fusion mag field filter
PRODUCT_PROPERTY_OVERRIDES += \
    ro.fusion.magfield.max=250

# IMS
PRODUCT_PROPERTY_OVERRIDES += \
    persist.ims.disableADBLogs=1 \
    persist.ims.disableDebugLogs=1 \
    persist.ims.disableIMSLogs=1 \
    persist.ims.disableQXDMLogs=1

# Radio
PRODUCT_PROPERTY_OVERRIDES += \
    persist.data.target=dpm1 \
    persist.radio.multisim.config=dsds \
    persist.radio.custom_ecc=1 \
    persist.radio.ecc_hard_1=112,911,110,122,119,120,000,118 \
    persist.radio.ecc_hard_count=1 \
    rild.libpath=/system/vendor/lib/libril-qc-qmi-1.so \
    ril.subscription.types=RUIM
