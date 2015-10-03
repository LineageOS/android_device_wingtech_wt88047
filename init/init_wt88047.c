/*
   Copyright (c) 2015, The Linux Foundation. All rights reserved.

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

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm.h"

static char board_id[32];

static void import_kernel_nv(char *name, int in_qemu)
{
    if (*name != '\0') {
        char *value = strchr(name, '=');
        if (value != NULL) {
            *value++ = 0;
            if (!strcmp(name,"board_id"))
            {
                const char s[2] = ":";
                value = strtok(value, s);
                strlcpy(board_id, value, sizeof(board_id));
            }
        }
    }
}

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char device[PROP_VALUE_MAX];
    int rc;

    UNUSED(msm_id);
    UNUSED(msm_ver);
    UNUSED(board_type);

    rc = property_get("ro.cm.device", device);
    if (!rc || !ISMATCH(device, "wt88047"))
        return;

    import_kernel_cmdline(0, import_kernel_nv);
    property_set("ro.product.board", board_id);
    ERROR("Detected board ID=%s\n", board_id);

    if (strcmp(board_id, "S88047E1") == 0) {
        property_set("ro.build.product", "HM2014817");
        property_set("ro.product.device", "HM2014817");
        property_set("ro.product.model", "2014817");
        property_set("ro.product.name", "2014817");
    } else if (strcmp(board_id, "S88047D1") == 0) {
        property_set("ro.build.product", "HM2014819");
        property_set("ro.product.device", "HM2014819");
        property_set("ro.product.model", "2014819");
        property_set("ro.product.name", "2014819");
    } else if (strcmp(board_id, "S88047C1") == 0) {
        property_set("ro.build.product", "HM2014818");
        property_set("ro.product.device", "HM2014818");
        property_set("ro.product.model", "2014818");
        property_set("ro.product.name", "2014818");
    } else if (strcmp(board_id, "S88047B2") == 0) {
        property_set("ro.build.product", "HM2014821");
        property_set("ro.product.device", "HM2014821");
        property_set("ro.product.model", "2014821");
        property_set("ro.product.name", "2014821");
        property_set("telephony.lteOnCdmaDevice", "1");
        property_set("persist.radio.sglte.eons_domain", "ps");
    } else if (strcmp(board_id, "S88047B1") == 0) {
        property_set("ro.build.product", "HM2014812");
        property_set("ro.product.device", "HM2014812");
        property_set("ro.product.model", "2014812");
        property_set("ro.product.name", "2014812");
        property_set("telephony.lteOnCdmaDevice", "1");
        property_set("persist.radio.sglte.eons_domain", "ps");
    } else if (strcmp(board_id, "S88047A2") == 0) {
        property_set("ro.build.product", "HM2014811");
        property_set("ro.product.device", "HM2014811");
        property_set("ro.product.model", "2014811");
        property_set("ro.product.name", "2014811");
    } else if (strcmp(board_id, "S88047A1") == 0) {
        property_set("ro.build.product", "HM2014813");
        property_set("ro.product.device", "HM2014813");
        property_set("ro.product.model", "2014813");
        property_set("ro.product.name", "2014813");
    } else {
        property_set("ro.build.product", "HM2014811");
        property_set("ro.product.device", "HM2014811");
        property_set("ro.product.model", "2014811");
        property_set("ro.product.name", "2014811");
    }

    /* Unified description and fingerprint for now */
    property_set("ro.build.description", "2014811-user 4.4.4 KTU84P HM2014811 release-keys");
    property_set("ro.build.fingerprint", "Xiaomi/2014811/HM2014811:4.4.4/KTU84P/V6.6.7.0.KHJMICF:user/release-keys");

    ERROR("Setup %s properties done!\n", board_id);

    return;
}
