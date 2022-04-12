fpga_crossgen --target hls --emulation_model geluHBU.cpp -o geluHBU.obj gelu_wrapper.xml
fpga_libtool --target hls --create geluHBU.lib geluHBU.obj