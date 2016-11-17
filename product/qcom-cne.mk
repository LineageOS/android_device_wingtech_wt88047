# CNE and DPM symbol
PRODUCT_PACKAGES += \
    libshim_parcel

PRODUCT_PROPERTY_OVERRIDES += \
    persist.data.target=dpm1 \
    persist.data.qmi.adb_logmask=0
