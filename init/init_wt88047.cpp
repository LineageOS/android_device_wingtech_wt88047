/*
   Copyright (c) 2016, The Linux Foundation. All rights reserved.
   Copyright (C) 2016, The CyanogenMod Project
   Copyright (C) 2015-2016, Ketut P. Kumajaya
   Copyright (C) 2017-2018, The LineageOS Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <cstdlib>
#include <fstream>
#include <string>
#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <sys/sysinfo.h>

#include <android-base/properties.h>
#include <android-base/strings.h>

#include "vendor_init.h"
#include "property_service.h"

using android::init::property_set;

// copied from build/tools/releasetools/ota_from_target_files.py
// but with "." at the end and empty entry
std::vector<std::string> ro_product_props_default_source_order = {
    "",
    "product.",
    "product_services.",
    "odm.",
    "vendor.",
    "system.",
};

void property_override(char const prop[], char const value[], bool add = true)
{
    auto pi = (prop_info *) __system_property_find(prop);

    if (pi != nullptr) {
        __system_property_update(pi, value, strlen(value));
    } else if (add) {
        __system_property_add(prop, strlen(prop), value, strlen(value));
    }
}

int is2GB()
{
    struct sysinfo sys;
    sysinfo(&sys);
    return sys.totalram > 1024ull * 1024 * 1024;
}

void vendor_load_properties()
{
    std::ifstream fin;
    std::string buf;
    std::string product;

    fin.open("/proc/cmdline");
    while (std::getline(fin, buf, ' '))
        if (buf.find("board_id") != std::string::npos)
            break;
    fin.close();

    const auto set_ro_product_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    /* S88047E1 */
    if (buf.find("S88047E1") != std::string::npos) {
        property_override("ro.build.product", "HM2014817");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "device", "HM2014817");
            set_ro_product_prop(source, "model", "2014817");
            set_ro_product_prop(source, "name", "2014817");
        }
        property_override("ro.telephony.default_network", "9,1");
    }
    /* S88047D1 */
    else if (buf.find("S88047D1") != std::string::npos) {
        property_override("ro.build.product", "HM2014819");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "device", "HM2014819");
            set_ro_product_prop(source, "model", "2014819");
            set_ro_product_prop(source, "name", "2014819");
        }
        property_set("ro.telephony.default_network", "9,1");
    }
    /* S88047C1 */
    else if (buf.find("S88047C1") != std::string::npos) {
        property_override("ro.build.product", "HM2014818");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "device", "HM2014818");
            set_ro_product_prop(source, "model", "2014818");
            set_ro_product_prop(source, "name", "2014818");
        }
        property_set("ro.telephony.default_network", "9,1");
        property_set("persist.dbg.volte_avail_ovr", "1");
        property_set("persist.dbg.vt_avail_ovr", "1");
    }
    /* S88047B2 */
    else if (buf.find("S88047B2") != std::string::npos) {
        property_override("ro.build.product", "HM2014821");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "device", "HM2014821");
            set_ro_product_prop(source, "model", "2014821");
            set_ro_product_prop(source, "name", "2014821");
        }
        property_set("ro.telephony.default_network", "22,1");
        property_set("telephony.lteOnCdmaDevice", "1");
        property_set("persist.radio.sglte.eons_domain", "ps");
    }
    /* S88047B1 */
    else if (buf.find("S88047B1") != std::string::npos) {
        property_override("ro.build.product", "HM2014812");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "device", "HM2014812");
            set_ro_product_prop(source, "model", "2014812");
            set_ro_product_prop(source, "name", "2014812");
        }
        property_set("ro.telephony.default_network", "22,1");
        property_set("telephony.lteOnCdmaDevice", "1");
        property_set("persist.radio.sglte.eons_domain", "ps");
    }
    /* S86047A1 and S86047A1_CD */
    else if (buf.find("S86047A1") != std::string::npos) {
        property_override("ro.build.product", "HM2014813");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "device", "HM2014813");
            set_ro_product_prop(source, "model", "2014813");
            set_ro_product_prop(source, "name", "2014813");
        }
        property_set("ro.telephony.default_network", "9,1");
    }
    /* S86047A2 and S86047A2_CD */
    else if (buf.find("S86047A2") != std::string::npos) {
        property_override("ro.build.product", "HM2014112");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "device", "HM2014112");
            set_ro_product_prop(source, "model", "2014112");
            set_ro_product_prop(source, "name", "2014112");
        }
        property_set("ro.telephony.default_network", "9,1");
    }
    /* S88047A2 and S88047A1 */
    else {
        property_override("ro.build.product", "HM2014811");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_product_prop(source, "device", "HM2014811");
            set_ro_product_prop(source, "model", "2014811");
            set_ro_product_prop(source, "name", "2014811");
        }
        property_set("ro.telephony.default_network", "9,1");
    }

    property_set("dalvik.vm.heapstartsize", "8m");
    property_set("dalvik.vm.heapgrowthlimit", is2GB() ? "192m" : "96m");
    property_set("dalvik.vm.heapsize", is2GB() ? "512m" : "256m");
    property_set("dalvik.vm.heaptargetutilization", "0.75");
    property_set("dalvik.vm.heapminfree", "512k");
    property_set("dalvik.vm.heapmaxfree", "8m");

    // Init a dummy BT MAC address, will be overwritten later
    property_set("ro.boot.btmacaddr", "00:00:00:00:00:00");
}
