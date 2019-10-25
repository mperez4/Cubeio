#!/bin/bash

rm *.bin
particle --no-update-check compile photon set_calibration.cpp --saveTo set_calibration.bin
