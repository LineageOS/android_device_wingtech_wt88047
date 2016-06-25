# Connectivity Engine support (CNE)
PRODUCT_PACKAGES += \
    CNEService \
    cneapiclient \
    com.quicinc.cne \
    init.cne.rc

# DPM
PRODUCT_PACKAGES += \
    com.qti.dpmframework \
    dpmapi

# CNE and DPM symbol
PRODUCT_PACKAGES += \
    libshim_parcel

PRODUCT_PROPERTY_OVERRIDES += \
    persist.cne.feature=4 \
    persist.data.target=dpm1 \
    persist.data.qmi.adb_logmask=0
