#!/bin/bash
fpga_crossgen gelu_wrapper.xml --target hls --emulation_model geluHBU.cpp -o geluHBU.o
fpga_libtool --target hls --create geluHBU.a geluHBU.o