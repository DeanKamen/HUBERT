`include "GELU_16bit.sv"
`timescale 1ps / 1ps
module gelu (
    input clock,
	input resetn,
    input ivalid,
    input iready,
    output ovalid,
    output oready,
    input [31:0] bin_in, //wire
    output [31:0] bin_out); 

    AHBU inst_unit(bin_in[15:0], bin_out[15:0]);
    assign ovalid = 1'b1;
    assign oready = 1'b1;
endmodule