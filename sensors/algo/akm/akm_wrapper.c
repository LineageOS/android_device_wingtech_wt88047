/*--------------------------------------------------------------------------
Copyright (c) 2014, The Linux Foundation. All rights reserved.

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
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <CalibrationModule.h>

#define LOG_TAG "sensor_cal.akm"
#include <utils/Log.h>

#include "AKFS_Device.h"
#include "AKFS_Decomp.h"
#include "AKFS_AOC.h"
#include "AKFS_Math.h"
#include "AKFS_VNorm.h"

#define SENSOR_CAL_ALGO_VERSION 1
#define AKM_MAG_SENSE                   (1.0)
#define CSPEC_HNAVE_V   8
#define AKFS_GEOMAG_MAX 70

struct sensor_cal_module_t SENSOR_CAL_MODULE_INFO;
static struct sensor_cal_algo_t algo_list[];

/*! A parameter structure. */
/* ix*_ : x-bit integer */
/* f**_ : floating value */
/* p**_ : pointer */
/* e**_ : enum */
/* *s*_ : struct */
/* *v*_ : vector (special type of struct) */
/* **a_ : array */
typedef struct _AKMPRMS{

	/* Variables for Decomp. */
	AKFVEC                  fva_hdata[AKFS_HDATA_SIZE];
	uint8vec                i8v_asa;

	/* Variables forAOC. */
	AKFS_AOC_VAR    s_aocv;

	/* Variables for Magnetometer buffer. */
	AKFVEC                  fva_hvbuf[AKFS_HDATA_SIZE];
	AKFVEC                  fv_ho;
	AKFVEC                  fv_hs;
	AKFS_PATNO              e_hpat;

	/* Variables for Accelerometer buffer. */
	AKFVEC                  fva_avbuf[AKFS_ADATA_SIZE];
	AKFVEC                  fv_ao;
	AKFVEC                  fv_as;

	/* Variables for Direction. */
	AKFLOAT                 f_azimuth;
	AKFLOAT                 f_pitch;
	AKFLOAT                 f_roll;

	/* Variables for vector output */
	AKFVEC                  fv_hvec;
	AKFVEC                  fv_avec;
	int16                   i16_hstatus;

} AKMPRMS;

static AKMPRMS g_prms;

static int convert_magnetic(sensors_vec_t *raw, sensors_vec_t *result,
		struct sensor_algo_args *args)
{
	int16 akret;
	int16 aocret;
	AKFLOAT radius;
	AKMPRMS *prms = &g_prms;
	int i;

	/* Shift out old data from the buffer for better calibration */
	for (i = AKFS_HDATA_SIZE - 1; i >= 1; i--) {
		prms->fva_hdata[i] = prms->fva_hdata[i - 1];
	}

	prms->fva_hdata[0].u.x = raw->x;
	prms->fva_hdata[0].u.y = raw->y;
	prms->fva_hdata[0].u.z = raw->z;

	/* Offset calculation is done in this function */
	/* hdata[in] : Android coordinate, sensitivity adjusted. */
	/* ho   [out]: Android coordinate, sensitivity adjusted. */
	aocret = AKFS_AOC(
		&prms->s_aocv,
		prms->fva_hdata,
		&prms->fv_ho
	);

	/* Subtract offset */
	/* hdata[in] : Android coordinate, sensitivity adjusted. */
	/* ho   [in] : Android coordinate, sensitivity adjusted. */
	/* hvbuf[out]: Android coordinate, sensitivity adjusted, */
	/*			   offset subtracted. */
	akret = AKFS_VbNorm(
		AKFS_HDATA_SIZE,
		prms->fva_hdata,
		1,
		&prms->fv_ho,
		&prms->fv_hs,
		AKM_MAG_SENSE,
		AKFS_HDATA_SIZE,
		prms->fva_hvbuf
	);
	if (akret == AKFS_ERROR) {
		ALOGE("error here!");
		return -1;
	}

	/* Averaging */
	/* hvbuf[in] : Android coordinate, sensitivity adjusted, */
	/*			   offset subtracted. */
	/* hvec [out]: Android coordinate, sensitivity adjusted, */
	/*			   offset subtracted, averaged. */
	akret = AKFS_VbAve(
		AKFS_HDATA_SIZE,
		prms->fva_hvbuf,
		CSPEC_HNAVE_V,
		&prms->fv_hvec
	);
	if (akret == AKFS_ERROR) {
		ALOGE("error here!");
		return -1;
	}

	/* Check the size of magnetic vector */
	radius = AKFS_SQRT(
			(prms->fv_hvec.u.x * prms->fv_hvec.u.x) +
			(prms->fv_hvec.u.y * prms->fv_hvec.u.y) +
			(prms->fv_hvec.u.z * prms->fv_hvec.u.z));

	if (radius > AKFS_GEOMAG_MAX) {
		prms->i16_hstatus = 0;
	} else {
		if (aocret == AKFS_SUCCESS) {
			prms->i16_hstatus = 3;
		}
	}

	result->x = prms->fv_hvec.u.x;
	result->y = prms->fv_hvec.u.y;
	result->z = prms->fv_hvec.u.z;
	result->status = prms->i16_hstatus;

	return 0;
}

static int config_magnetic(int cmd, struct sensor_algo_args *args)
{
	struct compass_algo_args *param = (struct compass_algo_args*)args;

	switch (cmd) {
		case CMD_ENABLE:
			ALOGD("Enable status changed to %d\n", param->common.enable);
			break;
		case CMD_DELAY:
			ALOGD("Polling rate changed to %d\n", param->common.delay_ms);
			break;
		case CMD_BATCH:
			break;
	}

	return 0;
}

static int cal_init(const struct sensor_cal_module_t *module)
{
	AKMPRMS *prms = &g_prms;

	/* Clear all data. */
	memset(prms, 0, sizeof(AKMPRMS));

	/* Sensitivity */
	prms->fv_hs.u.x = AKM_MAG_SENSE;
	prms->fv_hs.u.y = AKM_MAG_SENSE;
	prms->fv_hs.u.z = AKM_MAG_SENSE;

	/* Initialize buffer */
	AKFS_InitBuffer(AKFS_HDATA_SIZE, prms->fva_hdata);
	AKFS_InitBuffer(AKFS_HDATA_SIZE, prms->fva_hvbuf);
	AKFS_InitBuffer(AKFS_ADATA_SIZE, prms->fva_avbuf);

	/* Initialize for AOC */
	AKFS_InitAOC(&prms->s_aocv);
	/* Initialize magnetic status */
	prms->i16_hstatus = 0;

	return 0;
}

static void cal_deinit()
{
	ALOGI("%s called\n", __func__);
}

static int cal_get_algo_list(const struct sensor_cal_algo_t **algo)
{
	*algo = algo_list;
	return 0;
}

static struct sensor_algo_methods_t algo_methods = {
	.convert = convert_magnetic,
	.config = config_magnetic,
};

static const char* sensor_match_table[] = {
	"akm09911-mag",
	"akm8963-mag",
	"compass",
	NULL
};

static struct sensor_cal_algo_t algo_list[] = {
	{
		.tag = SENSOR_CAL_ALGO_TAG,
		.version = SENSOR_CAL_ALGO_VERSION,
		.type = SENSOR_TYPE_MAGNETIC_FIELD,
		.compatible = sensor_match_table,
		.module = &SENSOR_CAL_MODULE_INFO,
		.methods = &algo_methods,
	},
};

static struct sensor_cal_methods_t cal_methods = {
	.init = cal_init,
	.deinit = cal_deinit,
	.get_algo_list = cal_get_algo_list,
};

struct sensor_cal_module_t SENSOR_CAL_MODULE_INFO = {
	.tag = SENSOR_CAL_MODULE_TAG,
	.id = "cal_module_akm",
	.version = SENSOR_CAL_MODULE_VERSION,
	.vendor = "akm",
	.dso = NULL,
	.number = 1,
	.methods = &cal_methods,
	.reserved = {0},
};
