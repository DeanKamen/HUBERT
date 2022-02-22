fpga_crossgen exp_wrapper.xml --target hls --emulation_model expHBU.cpp -o expHBU.obj
fpga_libtool --target hls --create expHBU.lib expHBU.obj