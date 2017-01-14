/*
   Copyright (c) 2016, The Linux Foundation. All rights reserved.
   Copyright (C) 2016, The CyanogenMod Project
   Copyright (C) 2015-2016, Ketut P. Kumajaya
   Copyright (C) 2016-2017, Nikolai Petrenko
   Copyright (C) 2017, The LineageOS Project

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

#include <stdio.h>
#include <stdlib.h>

#include <android-base/file.h>
#include <android-base/strings.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"
#include <sys/sysinfo.h>

#include "init_msm8916.h"

static std::string board_id;

static void import_entire_kernel_cmdline(bool in_qemu,
                           const std::function<void(const std::string&, bool)>& fn)
{
    std::string cmdline;
    android::base::ReadFileToString("/proc/cmdline", &cmdline);

    for (const auto& entry : android::base::Split(android::base::Trim(cmdline), " ")) {
        fn(entry, in_qemu);
    }
}

static void import_cmdline(const std::string& name, bool for_emulator)
{
    if (name.empty())
        return;

    std::string::size_type pos = name.find('=');
    std::string value = name.substr(pos + 1);
    if (strstr(name.c_str(), "board_id") != NULL) {
        pos = value.find(':');
        board_id = value.substr(0, pos);
    }
}

int is2GB()
{
    struct sysinfo sys;
    sysinfo(&sys);
    return sys.totalram > 1024ull * 1024 * 1024;
}

void init_target_properties()
{
    std::string product = property_get("ro.product.name");
    if (strstr(product.c_str(), "wt88047") == NULL)
        return;

    if (is2GB()) {
        property_set("dalvik.vm.heapstartsize", "8m");
        property_set("dalvik.vm.heapgrowthlimit", "192m");
        property_set("dalvik.vm.heapsize", "512m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "512k");
        property_set("dalvik.vm.heapmaxfree", "8m");
    } else {
        property_set("dalvik.vm.heapstartsize", "8m");
        property_set("dalvik.vm.heapgrowthlimit", "96m");
        property_set("dalvik.vm.heapsize", "256m");
        property_set("dalvik.vm.heaptargetutilization", "0.75");
        property_set("dalvik.vm.heapminfree", "2m");
        property_set("dalvik.vm.heapmaxfree", "8m");
    }

    import_entire_kernel_cmdline(0, import_cmdline);

    if (board_id == "S88047E1") {
        property_set("ro.build.product", "HM2014817");
        property_set("ro.product.device", "HM2014817");
        property_set("ro.product.model", "2014817");
        property_set("ro.product.name", "2014817");
        property_set("ro.telephony.default_network", "9,1");
    } else if (board_id == "S88047D1") {
        property_set("ro.build.product", "HM2014819");
        property_set("ro.product.device", "HM2014819");
        property_set("ro.product.model", "2014819");
        property_set("ro.product.name", "2014819");
        property_set("ro.telephony.default_network", "9,1");
    } else if (board_id == "S88047C1") {
        property_set("ro.build.product", "HM2014818");
        property_set("ro.product.device", "HM2014818");
        property_set("ro.product.model", "2014818");
        property_set("ro.product.name", "2014818");
        property_set("ro.telephony.default_network", "9,1");
        property_set("persist.dbg.volte_avail_ovr", "1");
        property_set("persist.dbg.vt_avail_ovr", "1");
    } else if (board_id == "S88047B2") {
        property_set("ro.build.product", "HM2014821");
        property_set("ro.product.device", "HM2014821");
        property_set("ro.product.model", "2014821");
        property_set("ro.product.name", "2014821");
        property_set("ro.telephony.default_network", "22,1");
        property_set("telephony.lteOnCdmaDevice", "1");
        property_set("persist.radio.sglte.eons_domain", "ps");
    } else if (board_id == "S88047B1") {
        property_set("ro.build.product", "HM2014812");
        property_set("ro.product.device", "HM2014812");
        property_set("ro.product.model", "2014812");
        property_set("ro.product.name", "2014812");
        property_set("ro.telephony.default_network", "22,1");
        property_set("telephony.lteOnCdmaDevice", "1");
        property_set("persist.radio.sglte.eons_domain", "ps");
    } else if ((board_id =="S86047A1") || (board_id == "S86047A1_CD")) {
        property_set("ro.build.product", "HM2014813");
        property_set("ro.product.device", "HM2014813");
        property_set("ro.product.model", "2014813");
        property_set("ro.product.name", "2014813");
        property_set("ro.telephony.default_network", "9,1");
    } else if ((board_id == "S86047A2") || (board_id == "S86047A2_CD")) {
        property_set("ro.build.product", "HM2014112");
        property_set("ro.product.device", "HM2014112");
        property_set("ro.product.model", "2014112");
        property_set("ro.product.name", "2014112");
        property_set("ro.telephony.default_network", "9,1");
    } else { /* including S88047A2 and S88047A1 */
        property_set("ro.build.product", "HM2014811");
        property_set("ro.product.device", "HM2014811");
        property_set("ro.product.model", "2014811");
        property_set("ro.product.name", "2014811");
        property_set("ro.telephony.default_network", "9,1");
    }

    /* Unified description and fingerprint for now */
    property_set("ro.build.description", "wt88047-user 5.1.1 LMY47V 6.1.28 release-keys");
    property_set("ro.build.fingerprint", "Xiaomi/wt88047/wt88047:5.1.1/LMY47V/6.1.28:user/release-keys");
}
