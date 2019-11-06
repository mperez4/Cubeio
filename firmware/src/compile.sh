#!/bin/bash

rm *.bin
particle --no-update-check compile photon firmware.cpp --saveTo upload.bin
