fpga_crossgen --target hls --emulation_model geluHBU.cpp -o geluHBU.obj gelu.xml
fpga_libtool --target hls --create geluHBU.lib geluHBU.obj