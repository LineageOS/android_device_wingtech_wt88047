# Sensor HAL
PRODUCT_PACKAGES += \
    calmodule.cfg \
    libcalmodule_common \
    sensors.msm8916

# Permissions
PRODUCT_COPY_FILES += \
    frameworks/native/data/etc/android.hardware.sensor.accelerometer.xml:system/etc/permissions/android.hardware.sensor.accelerometer.xml \
    frameworks/native/data/etc/android.hardware.sensor.compass.xml:system/etc/permissions/android.hardware.sensor.compass.xml \
    frameworks/native/data/etc/android.hardware.sensor.gyroscope.xml:system/etc/permissions/android.hardware.sensor.gyroscope.xml \
    frameworks/native/data/etc/android.hardware.sensor.light.xml:system/etc/permissions/android.hardware.sensor.light.xml \
    frameworks/native/data/etc/android.hardware.sensor.proximity.xml:system/etc/permissions/android.hardware.sensor.proximity.xml \
    frameworks/native/data/etc/handheld_core_hardware.xml:system/etc/permissions/handheld_core_hardware.xml

# use 3 threads max for dex2oat
PRODUCT_PROPERTY_OVERRIDES += \
    ro.sys.fw.dex2oat_thread_count=3

# relax sensor fusion mag field filter
PRODUCT_PROPERTY_OVERRIDES += \
    ro.fusion.magfield.max=250
