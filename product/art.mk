# Enable ART small mode
PRODUCT_PROPERTY_OVERRIDES += \
    pm.dexopt.install=interpret-only \
    pm.dexopt.bg-dexopt=speed-profile \
    pm.dexopt.boot=verify-profile
