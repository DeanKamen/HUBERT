`include "Out6.v"
`timescale 1ns / 1ps
module exp_wrapper (bin_in, clock, bin_out1, resetn, ivalid, ovalid, iready, oready);
    input wire[7:0] bin_in;
    input wire clock;
	input resetn;
    wire[7:0] bin_out;
    output reg[7:0] bin_out1;
    input ivalid;
    input iready;
    output ovalid;
    output oready; 

    New_Imp_Func exp(.bin_in1(bin_in), .clk(clock),  .bin_out(bin_out));
    assign ovalid = 1'b1;
    assign oready = 1'b1;
    always @(posedge clock)
    begin
        bin_out1 <= bin_out;
    end
endmodule