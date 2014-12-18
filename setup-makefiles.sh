#!/bin/sh

set -e

export VENDOR=smartfren
export DEVICE=rendang
./../../$VENDOR/msm8916-common/setup-makefiles.sh $@
