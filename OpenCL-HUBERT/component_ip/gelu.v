`include "Out6.v"
`timescale 1ps / 1ps
module exp_wrapper (
    input clock,
	input resetn,
    input ivalid,
    input iready,
    output ovalid,
    output oready,
    input [7:0] bin_in, //wire
    output [7:0] bin_out1); //reg

    //wire[7:0] bin_out;
    New_Imp_Func exp(.bin_in1(bin_in), .clk(clock),  .bin_out(bin_out1));
    assign ovalid = 1'b1;
    assign oready = 1'b1;
    //always @(posedge clock)
    //begin
        //bin_out1 <= bin_out;
    //end
endmodule