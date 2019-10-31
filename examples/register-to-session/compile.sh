#!/bin/bash

rm *.bin
particle --no-update-check compile photon register-to-session.cpp --saveTo upload.bin
