#!/bin/bash

rm *.bin
particle --no-update-check compile photon example-1.cpp --saveTo example-1.bin
