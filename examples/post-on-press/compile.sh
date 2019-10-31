#!/bin/bash

rm *.bin
particle --no-update-check compile photon post-on-press.cpp --saveTo example-1.bin
