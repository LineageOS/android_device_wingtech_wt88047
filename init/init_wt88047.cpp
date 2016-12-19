/*
   Copyright (c) 2016, The CyanogenMod Project
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

#include <stdlib.h>
#include <stdio.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm8916.h"

static char board_id[32];

static void import_cmdline(const std::string& key,
        const std::string& value, bool for_emulator __attribute__((unused)))
{
    if (key.empty()) return;

    if (key == "board_id") {
        const char s[2] = ":";
        char *board = strtok(value.c_str(), s);
        strlcpy(board_id, board, sizeof(board_id));
    }
}

void init_target_properties()
{
    std::string device;

    device = property_get("ro.cm.device");
    if (device != "wt88047")
        return;

    import_kernel_cmdline(0, import_cmdline);
    ERROR("Detected board ID=%s\n", board_id);

    if (strcmp(board_id, "S88047E1") == 0) {
        property_set("ro.build.product", "HM2014817");
        property_set("ro.product.device", "HM2014817");
        property_set("ro.product.model", "2014817");
        property_set("ro.product.name", "2014817");
        property_set("ro.telephony.default_network", "9,1");
        property_set("telephony.lteOnCdmaDevice", "0");
    } else if (strcmp(board_id, "S88047D1") == 0) {
        property_set("ro.build.product", "HM2014819");
        property_set("ro.product.device", "HM2014819");
        property_set("ro.product.model", "2014819");
        property_set("ro.product.name", "2014819");
        property_set("ro.telephony.default_network", "9,1");
        property_set("telephony.lteOnCdmaDevice", "0");
    } else if (strcmp(board_id, "S88047C1") == 0) {
        property_set("ro.build.product", "HM2014818");
        property_set("ro.product.device", "HM2014818");
        property_set("ro.product.model", "2014818");
        property_set("ro.product.name", "2014818");
        property_set("ro.telephony.default_network", "9,1");
        property_set("telephony.lteOnCdmaDevice", "0");
        property_set("persist.dbg.volte_avail_ovr", "1");
        property_set("persist.dbg.vt_avail_ovr", "1");
    } else if (strcmp(board_id, "S88047B2") == 0) {
        property_set("ro.build.product", "HM2014821");
        property_set("ro.product.device", "HM2014821");
        property_set("ro.product.model", "2014821");
        property_set("ro.product.name", "2014821");
        property_set("ro.telephony.default_network", "22,1");
        property_set("telephony.lteOnCdmaDevice", "1");
        property_set("persist.radio.sglte.eons_domain", "ps");
    } else if (strcmp(board_id, "S88047B1") == 0) {
        property_set("ro.build.product", "HM2014812");
        property_set("ro.product.device", "HM2014812");
        property_set("ro.product.model", "2014812");
        property_set("ro.product.name", "2014812");
        property_set("ro.telephony.default_network", "22,1");
        property_set("telephony.lteOnCdmaDevice", "1");
        property_set("persist.radio.sglte.eons_domain", "ps");
    } else if ((strcmp(board_id, "S86047A1") == 0) || (strcmp(board_id, "S86047A1_CD") == 0)) {
        property_set("ro.build.product", "HM2014813");
        property_set("ro.product.device", "HM2014813");
        property_set("ro.product.model", "2014813");
        property_set("ro.product.name", "2014813");
        property_set("ro.telephony.default_network", "9,1");
        property_set("telephony.lteOnCdmaDevice", "0");
    } else if ((strcmp(board_id, "S86047A2") == 0) || (strcmp(board_id, "S86047A2_CD") == 0)) {
        property_set("ro.build.product", "HM2014112");
        property_set("ro.product.device", "HM2014112");
        property_set("ro.product.model", "2014112");
        property_set("ro.product.name", "2014112");
        property_set("ro.telephony.default_network", "9,1");
        property_set("telephony.lteOnCdmaDevice", "0");
    } else { /* including S88047A2 and S88047A1 */
        property_set("ro.build.product", "HM2014811");
        property_set("ro.product.device", "HM2014811");
        property_set("ro.product.model", "2014811");
        property_set("ro.product.name", "2014811");
        property_set("ro.telephony.default_network", "9,1");
        property_set("telephony.lteOnCdmaDevice", "0");
    }
}
