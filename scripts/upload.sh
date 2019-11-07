#!/bin/bash

particle usb dfu
particle --no-update-check compile photon *.cpp --saveTo upload.bin
particle flash --usb upload.bin
rm *.bin
