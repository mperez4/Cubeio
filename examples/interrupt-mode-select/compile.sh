#!/bin/bash

rm *.bin
particle --no-update-check compile photon interrupt-mode-select.cpp --saveTo interrupt-mode-select.bin
