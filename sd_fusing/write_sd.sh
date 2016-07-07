#!/bin/sh

UBOOT=../fip/gxl/u-boot.bin.sd.bin

if [ -z $1 ]; then
	echo "Usage ./flash_firmware.sh <SD card reader's device>"
	exit 1
fi

if [ ! -f $UBOOT ]; then
	echo "error: $UBOOT is not exist"
	exit 1
fi

sudo dd if=$UBOOT of=$1 conv=fsync bs=1 count=442
sudo dd if=$UBOOT of=$1 conv=fsync bs=512 skip=1 seek=1

sync
