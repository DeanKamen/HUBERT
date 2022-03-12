fpga_crossgen --target hls --emulation_model expHBU.cpp -o expHBU.obj exp_wrapper.xml
fpga_libtool --target hls --create expHBU.lib expHBU.obj