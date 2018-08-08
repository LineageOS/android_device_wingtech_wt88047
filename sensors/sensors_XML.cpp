/*--------------------------------------------------------------------------
Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.

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

#include <sensors_extension.h>
#include "sensors_XML.h"
#include <cutils/log.h>
#include "unistd.h"
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <private/android_filesystem_config.h>

#define SENSOR_XML_ROOT_ELEMENT "sensors"

ANDROID_SINGLETON_STATIC_INSTANCE(sensors_XML);
const static char *filepath[] = {
    "/persist/sensors/sensors_calibration_params.xml",
    "/data/sensors_calibration_params.xml"
};

const char *sensor_param[] = {"offset_x", "offset_y", "offset_z", "threshold_h", "threshold_l", "bias"};
const char *cal_state[] = {"static","dynamic"};
sensors_XML :: sensors_XML()
    : mdoc(NULL)
{
}

static int config_file_copy()
{
    int bufsize;
    int fd[2];
    off_t offset;
    char *ptr;
    char *wptr;
    int bytes_read, bytes_write;
    int err = 0;

    if ((fd[0] = open(filepath[0], O_RDONLY)) == -1) {
        ALOGE("open calibrate sensor config error %d", errno);
        return -errno;
    }
    if ((fd[1] = open(filepath[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1) {
        ALOGE("create calibrate sensor config error");
        close(fd[0]);
        return -errno;
    }

    offset = lseek(fd[0], 0, SEEK_END);
    if (offset < 0) {
        ALOGE("lseek %s error %d", filepath[0], errno);
        err = -errno;
        goto close_fd;
    }

    bufsize = offset;
    ptr = (char*)malloc(bufsize);
    if (ptr == NULL) {
        ALOGE("malloc memory for %s error", filepath[1]);
        err = -errno;
        goto close_fd;
    }

    offset = lseek(fd[0], 0, SEEK_SET);
    if (offset < 0) {
        ALOGE("lseek %s error %d", filepath[0], errno);
        err = -errno;
        goto free_ptr;
    }
    bytes_read = read(fd[0], ptr, bufsize);
    if (bytes_read == -1 && errno != EINTR) {
        ALOGE("read calibrate sensor config error");
        err = -errno;
        goto free_ptr;
    }

    wptr = ptr;
    while ((bytes_write = write(fd[1], wptr, bytes_read))) {
        if (bytes_write == -1 && errno != EINTR) {
            ALOGE("write calibrate sensor config error");
            err = -errno;
            goto free_ptr;
        } else if (bytes_write == bytes_read) {
            break;
        }else if (bytes_write > 0) {
            wptr += bytes_write;
            bytes_read -= bytes_write;
        }
    }
free_ptr:
    free(ptr);
close_fd:
    close(fd[0]);
    close(fd[1]);
    return err;
}

int sensors_XML :: write_sensors_params(struct sensor_t *sensor, struct cal_result_t *cal_result, int state)
{
    xmlNodePtr rootNode, curNode, newNode;
    xmlAttrPtr value;
    bool newcreate = false;
    char string[33];
    int fnum = 0;
    int i = 0, j, MAX = 0;
    int err = 0;

    if (state < CAL_STATIC || state > CAL_DYNAMIC) {
        ALOGE("state error\n");
        return -1;
    }
    if (cal_result == NULL) {
        ALOGE("Null pointer parameter\n");
        return -1;
    }

    if (state == 1)
        fnum = 1;

    if (!access(filepath[fnum], F_OK)) {
        if (!access(filepath[fnum], W_OK)) {
            mdoc = xmlReadFile(filepath[fnum], "UTF-8" , XML_PARSE_NOBLANKS);
            if (mdoc == NULL) {
                ALOGE("read calibration file error\n");
                return -EINVAL;
            }
        } else {
            ALOGE("No permission write file %s\n", filepath[fnum]);
            return -1;
        }
    } else {
        mdoc = xmlNewDoc(BAD_CAST "1.0");
        if (mdoc == NULL) {
            ALOGE("create sensor calibration file error\n");
            return -1;
        }
        newcreate = true;
    }

    if(newcreate) {
        rootNode = xmlNewNode(NULL, BAD_CAST SENSOR_XML_ROOT_ELEMENT);
        xmlDocSetRootElement(mdoc, rootNode);
        curNode = xmlNewNode(NULL, BAD_CAST "sensor");
        xmlAddChild(rootNode, curNode);
        xmlNewProp(curNode, BAD_CAST "name", BAD_CAST sensor->name);
        xmlNewProp(curNode, BAD_CAST "state", BAD_CAST cal_state[state]);
    } else {
        rootNode = xmlDocGetRootElement(mdoc);
        if (rootNode == NULL) {
            ALOGE("empty document\n");
            xmlFreeDoc(mdoc);
            return -1;
        }

        if (xmlStrcmp(rootNode->name, BAD_CAST SENSOR_XML_ROOT_ELEMENT)) {
            ALOGE("root node != sensors\n");
            xmlFreeDoc(mdoc);
            return -1;
        }
        curNode = rootNode->xmlChildrenNode;
        while(curNode != NULL) {
            if (!xmlStrcmp(xmlGetProp(curNode, BAD_CAST "name"), BAD_CAST sensor->name) &&
                !xmlStrcmp(xmlGetProp(curNode, BAD_CAST "state"), BAD_CAST cal_state[state]))
                break;
            curNode = curNode->next;
        }
    }
    switch(sensor->type) {
        case SENSOR_TYPE_ACCELEROMETER:
        case SENSOR_TYPE_GYROSCOPE:
            i = 0;
            MAX = 3;
            break;
        case SENSOR_TYPE_PROXIMITY:
            i = 3;
            MAX = 6;
            break;
        case SENSOR_TYPE_LIGHT:
        case SENSOR_TYPE_MAGNETIC_FIELD:
        case SENSOR_TYPE_PRESSURE:
        case SENSOR_TYPE_TEMPERATURE:
        default:
            break;
    }
    if (newcreate) {
        for(j = 0; i < MAX && j < 3; i++, j++) {
            snprintf(string, sizeof(string), "%d", cal_result->offset[j]);
            value = xmlNewProp(curNode, BAD_CAST sensor_param[i], BAD_CAST string);
            if (value == NULL) {
                ALOGE("write value in new create error\n");
                xmlFreeDoc(mdoc);
                return -1;
            }
        }
    } else {
        if (curNode == NULL) {
            curNode = xmlNewNode(NULL, BAD_CAST "sensor");
            xmlAddChild(rootNode, curNode);
            value = xmlNewProp(curNode, BAD_CAST "name", BAD_CAST sensor->name);
            if (value == NULL) {
                ALOGE("name is NULL\n");
                xmlFreeDoc(mdoc);
                return -1;
            }
            value = xmlNewProp(curNode, BAD_CAST "state", BAD_CAST cal_state[state]);
            if (value == NULL) {
                ALOGE("state is NULL\n");
                xmlFreeDoc(mdoc);
                return -1;
            }
            for(j = 0; i < MAX && j < 3; i++, j++) {
                snprintf(string, sizeof(string), "%d", cal_result->offset[j]);
                value = xmlNewProp(curNode, BAD_CAST sensor_param[i], BAD_CAST string);
                if (value == NULL) {
                    ALOGE("write value error\n");
                    xmlFreeDoc(mdoc);
                    return -1;
                }
            }
        } else {
            for(j = 0; i < MAX && j < 3; i++, j++) {
                snprintf(string, sizeof(string), "%d", cal_result->offset[j]);
                value = xmlSetProp(curNode, BAD_CAST sensor_param[i], BAD_CAST string);
                if (value == NULL) {
                    ALOGE("set value error\n");
                    xmlFreeDoc(mdoc);
                    return -1;
                }
            }
        }
    }
    if (xmlSaveFormatFileEnc(filepath[fnum], mdoc, "UTF-8", 1) == -1) {
        ALOGE("save %s failed %s\n", filepath[fnum], strerror(errno));
        xmlFreeDoc(mdoc);
        return -1;
    }
    if (fnum == 0) {
        if (getuid() != AID_ROOT) {
            goto exit;
        }
        err = chown(filepath[fnum], AID_ROOT, AID_SYSTEM);
        if (err != 0) {
            ALOGE("chown %s failed %s", filepath[fnum], strerror(errno));
            xmlFreeDoc(mdoc);
            return -1;
        }
        err = chmod(filepath[fnum], 0660);
        if (err != 0) {
            ALOGE("chmod %s failed %s", filepath[fnum], strerror(errno));
            xmlFreeDoc(mdoc);
            return -1;
        }
    }

exit:
    xmlFreeDoc(mdoc);
    return 0;
}

int sensors_XML :: read_sensors_params(struct sensor_t *sensor, struct cal_result_t *cal_result, int state)
{
    xmlNodePtr rootNode, curNode;
    int i = 0, j, MAX = 0;

    if (state < CAL_STATIC || state > CAL_DYNAMIC) {
        ALOGE("state error\n");
        return -1;
    }
    if (cal_result == NULL) {
        ALOGE("Null pointer parameter\n");
        return -1;
    }
    if (!access(filepath[1], R_OK)) {
        mdoc = xmlReadFile(filepath[1], "UTF-8" , XML_PARSE_RECOVER);
    } else if (!access(filepath[0], F_OK)){
        int err;

        err = config_file_copy();
        if (err < 0) {
            ALOGE("copy %s error", filepath[0]);
            return err;
        }
        if (!access(filepath[1], R_OK)) {
            mdoc = xmlReadFile(filepath[1], "UTF-8" , XML_PARSE_RECOVER);
        } else {
            ALOGE("file %s can't read\n", filepath[1]);
            return -1;
        }
    } else {
        ALOGE("file %s can't read\n", filepath[0]);
        return -1;
    }
    rootNode = xmlDocGetRootElement(mdoc);
    if (rootNode == NULL) {
        ALOGE("empty document\n");
        xmlFreeDoc(mdoc);
        return -1;
    }

    if (xmlStrcmp(rootNode->name, BAD_CAST SENSOR_XML_ROOT_ELEMENT)) {
        ALOGE("root node != sensors\n");
        xmlFreeDoc(mdoc);
        return -1;
    }
    curNode = rootNode->xmlChildrenNode;
    while(curNode != NULL) {
        if (!xmlStrcmp(xmlGetProp(curNode, BAD_CAST "name"), BAD_CAST sensor->name) &&
            !xmlStrcmp(xmlGetProp(curNode, BAD_CAST "state"), BAD_CAST cal_state[state]))
            break;
            curNode = curNode->next;
    }
    switch(sensor->type) {
        case SENSOR_TYPE_ACCELEROMETER:
        case SENSOR_TYPE_GYROSCOPE:
            i = 0;
            MAX = 3;
            break;
        case SENSOR_TYPE_PROXIMITY:
            i = 3;
            MAX = 6;
            break;
        case SENSOR_TYPE_LIGHT:
        case SENSOR_TYPE_MAGNETIC_FIELD:
        case SENSOR_TYPE_PRESSURE:
        case SENSOR_TYPE_TEMPERATURE:
        default:
            break;
    }
    if (curNode != NULL) {
        xmlChar* value;
        for(j = 0; i < MAX && j < 3; i++, j++) {
            value = xmlGetProp(curNode, BAD_CAST sensor_param[i]);
            if(value != NULL) {
               cal_result->offset[j] = atoi((char*)value);
            }
        }
    } else {
        for(j = 0; j < 3; j++) {
            cal_result->offset[j] = 0;
        }
        ALOGE("The sensor %s calibrate parameters is not found\n", sensor->name);
        xmlFreeDoc(mdoc);
        return -1;
    }
    xmlFreeDoc(mdoc);
    return 0;
}

int sensors_XML :: sensors_calibrate_reset()
{
    int i;
    for(i=0; i < 2; i++) {
        if (access(filepath[i], F_OK)) {
            ALOGE("file is not exits\n");
            return -1;
        }
        if (remove(filepath[i])) {
            ALOGE("reset calibrate error\n");
            return -1;
        }
    }
    return 0;
}

int sensors_XML :: sensors_rm_file()
{

    if (access(filepath[1], F_OK)) {
        return 0;
    }
    if (remove(filepath[1])) {
        ALOGE("reset calibrate error\n");
        return -1;
    }
    return 0;
}
