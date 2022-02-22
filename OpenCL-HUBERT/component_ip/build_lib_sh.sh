#!/bin/bash
fpga_crossgen exp_wrapper.xml --target hls --emulation_model expHBU.cpp -o expHBU.o
fpga_libtool --target hls --create expHBU.a expHBU.o