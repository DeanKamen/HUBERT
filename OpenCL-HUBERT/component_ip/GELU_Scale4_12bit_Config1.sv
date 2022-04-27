`timescale 1ns / 1ps
module Top_For_Clk(input wire[11:0] bin_in, input wire clk, output reg[11:0] bout_out);

reg[11:0] bin_reg;
wire[11:0] bout_wire;
AHBU UUT0(bin_reg, bout_wire);

always @(posedge clk)begin
	bout_out <= bout_wire;
	bin_reg <= bin_in;
end

endmodule

//=========

module AHBU(input wire[11:0] bin_in, output wire[11:0] bin_out);

//----> In_Unary
wire [62:0] In_Unary63;

//----> Out and Out_Unary
wire [30:0] Out_Unary1; wire [4:0] Out1;

//----> Encoders
Encoder_6 Enc1(bin_in[5:0], In_Unary63);

//----> Decoders
Decoder_5 Dec1(Out_Unary1, Out1);

//----> SubFunctions
SubFunction_1 SF1(In_Unary63, Out_Unary1);

//----> Mux
assign bin_out = (bin_in < 64) ? {7'b0, {0{1'b0}}, Out1}:
		 (bin_in < 128) ? {7'b1, {0{1'b0}}, Out1}:
		 (bin_in < 192) ? {7'b11, {0{1'b0}}, Out1}:
		 (bin_in < 256) ? {7'b100, {0{1'b0}}, Out1}:
		 (bin_in < 320) ? {7'b110, {0{1'b0}}, Out1}:
		 (bin_in < 384) ? {7'b1000, {0{1'b0}}, Out1}:
		 (bin_in < 448) ? {7'b1010, {0{1'b0}}, Out1}:
		 (bin_in < 512) ? {7'b1100, {0{1'b0}}, Out1}:
		 (bin_in < 576) ? {7'b1110, {0{1'b0}}, Out1}:
		 (bin_in < 640) ? {7'b10000, {0{1'b0}}, Out1}:
		 (bin_in < 704) ? {7'b10010, {0{1'b0}}, Out1}:
		 (bin_in < 768) ? {7'b10101, {0{1'b0}}, Out1}:
		 (bin_in < 832) ? {7'b10111, {0{1'b0}}, Out1}:
		 (bin_in < 896) ? {7'b11001, {0{1'b0}}, Out1}:
		 (bin_in < 960) ? {7'b11011, {0{1'b0}}, Out1}:
		 (bin_in < 1024) ? {7'b11110, {0{1'b0}}, Out1}:
		 (bin_in < 1088) ? {7'b100000, {0{1'b0}}, Out1}:
		 (bin_in < 1152) ? {7'b100010, {0{1'b0}}, Out1}:
		 (bin_in < 1216) ? {7'b100100, {0{1'b0}}, Out1}:
		 (bin_in < 1280) ? {7'b100110, {0{1'b0}}, Out1}:
		 (bin_in < 1344) ? {7'b101000, {0{1'b0}}, Out1}:
		 (bin_in < 1408) ? {7'b101010, {0{1'b0}}, Out1}:
		 (bin_in < 1472) ? {7'b101100, {0{1'b0}}, Out1}:
		 (bin_in < 1536) ? {7'b101110, {0{1'b0}}, Out1}:
		 (bin_in < 1600) ? {7'b110000, {0{1'b0}}, Out1}:
		 (bin_in < 1664) ? {7'b110010, {0{1'b0}}, Out1}:
		 (bin_in < 1728) ? {7'b110100, {0{1'b0}}, Out1}:
		 (bin_in < 1792) ? {7'b110110, {0{1'b0}}, Out1}:
		 (bin_in < 1856) ? {7'b111000, {0{1'b0}}, Out1}:
		 (bin_in < 1920) ? {7'b111010, {0{1'b0}}, Out1}:
		 (bin_in < 1984) ? {7'b111100, {0{1'b0}}, Out1}:
		 (bin_in < 2048) ? {7'b111110, {0{1'b0}}, Out1}:
		 (bin_in < 2112) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2176) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2240) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2304) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2368) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2432) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2496) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2560) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2624) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2688) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2752) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2816) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2880) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 2944) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 3008) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 3072) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 3136) ? {7'b1111111, {0{1'b0}}, Out1}:
		 (bin_in < 3200) ? {7'b1111110, {0{1'b0}}, Out1}:
		 (bin_in < 3264) ? {7'b1111110, {0{1'b0}}, Out1}:
		 (bin_in < 3328) ? {7'b1111110, {0{1'b0}}, Out1}:
		 (bin_in < 3392) ? {7'b1111110, {0{1'b0}}, Out1}:
		 (bin_in < 3456) ? {7'b1111110, {0{1'b0}}, Out1}:
		 (bin_in < 3520) ? {7'b1111101, {0{1'b0}}, Out1}:
		 (bin_in < 3584) ? {7'b1111101, {0{1'b0}}, Out1}:
		 (bin_in < 3648) ? {7'b1111101, {0{1'b0}}, Out1}:
		 (bin_in < 3712) ? {7'b1111101, {0{1'b0}}, Out1}:
		 (bin_in < 3776) ? {7'b1111101, {0{1'b0}}, Out1}:
		 (bin_in < 3840) ? {7'b1111101, {0{1'b0}}, Out1}:
		 (bin_in < 3904) ? {7'b1111101, {0{1'b0}}, Out1}:
		 (bin_in < 3968) ? {7'b1111110, {0{1'b0}}, Out1}:
		 (bin_in < 4032) ? {7'b1111110, {0{1'b0}}, Out1}:
		 {7'b1111111, {0{1'b0}}, Out1};

endmodule

//=========

module SubFunction_1(input wire[62:0] In, output wire[30:0] Out);
assign Out[0] = In[1];
assign Out[1] = In[3];
assign Out[2] = In[5];
assign Out[3] = In[7];
assign Out[4] = In[9];
assign Out[5] = In[11];
assign Out[6] = In[13];
assign Out[7] = In[15];
assign Out[8] = In[17];
assign Out[9] = In[19];
assign Out[10] = In[21];
assign Out[11] = In[23];
assign Out[12] = In[25];
assign Out[13] = In[26];
assign Out[14] = In[28];
assign Out[15] = In[30];
assign Out[16] = In[32];
assign Out[17] = In[34];
assign Out[18] = In[35];
assign Out[19] = In[37];
assign Out[20] = In[39];
assign Out[21] = In[41];
assign Out[22] = In[43];
assign Out[23] = In[44];
assign Out[24] = In[46];
assign Out[25] = In[48];
assign Out[26] = In[50];
assign Out[27] = In[51];
assign Out[28] = In[53];
assign Out[29] = In[55];
assign Out[30] = In[56];
endmodule

//=========

//=====================================================
module Encoder_2(bin_in,the_out);
input [1:0] bin_in;
output [2:0] the_out;

assign the_out[0] = bin_in[0]|bin_in[1];
assign the_out[1] = bin_in[1];
assign the_out[2] = bin_in[0]&bin_in[1];

endmodule
//-------------------------------------------------------------------------
module Encoder_3(bin_in,the_out);
input [2:0] bin_in;
output [6:0] the_out;

assign the_out[0] = bin_in[0]|bin_in[1]|bin_in[2];
assign the_out[1] = bin_in[1]|bin_in[2];
assign the_out[2] = bin_in[0]&bin_in[1]|bin_in[2];
assign the_out[3] = bin_in[2];

assign the_out[4] = (bin_in[0]|bin_in[1])&bin_in[2];
assign the_out[5] = (bin_in[1]&bin_in[2]);
assign the_out[6] = (bin_in[0]&bin_in[1])&bin_in[2];

endmodule
//-------------------------------------------------------------------------
module Encoder_4(bin_in,the_out);
input [3:0] bin_in;
output [14:0] the_out;

assign the_out[0] = bin_in[0]|bin_in[1]|bin_in[2]|bin_in[3];
assign the_out[1] = bin_in[1]|bin_in[2]|bin_in[3];
assign the_out[2] = bin_in[0]&bin_in[1]|bin_in[2]|bin_in[3];
assign the_out[3] = bin_in[2]|bin_in[3];

assign the_out[4] = (bin_in[0]|bin_in[1])&bin_in[2]|bin_in[3];
assign the_out[5] = (bin_in[1]&bin_in[2])|bin_in[3];
assign the_out[6] = (bin_in[0]&bin_in[1])&bin_in[2]|bin_in[3];
assign the_out[7] = bin_in[3];

assign the_out[8] = (bin_in[0]|bin_in[1]|bin_in[2])&bin_in[3];
assign the_out[9] = (bin_in[1]|bin_in[2])&bin_in[3];
assign the_out[10]= ((bin_in[0]&bin_in[1])|bin_in[2])&bin_in[3];
assign the_out[11]= bin_in[2]&bin_in[3];

assign the_out[12]= ((bin_in[0]|bin_in[1])&bin_in[2])&bin_in[3];
assign the_out[13]= ((bin_in[1])&bin_in[2])&bin_in[3];
assign the_out[14]= ((bin_in[0]&bin_in[1])&bin_in[2])&bin_in[3];

endmodule
//-------------------------------------------------------------------------
module Encoder_5(bin_in,out_all);
input  [4:0] bin_in;
output [30:0] out_all;

wire [14:0] the_out1;

Encoder_4 col(bin_in[3:0],the_out1);

wire [15:0] c;

assign c = {1'b0,the_out1};

assign  out_all[15:0]  = {16{bin_in[4]}}|c;
assign  out_all[30:16] = c[14:0]&{15{bin_in[4]}};

endmodule
//-------------------------------------------------------------------------
module Encoder_6(bin_in,out_all);
input  [5:0] bin_in;
output [62:0] out_all;

wire [2:0] the_out;
wire [14:0] the_out1;

Encoder_2 row(bin_in[5:4],the_out);
Encoder_4 col(bin_in[3:0],the_out1);

wire [3:0]  r;
wire [15:0] c;
assign r = {the_out,1'b1};
assign c = {1'b0,the_out1};

assign  out_all[15:0]  = {16{r[1]}}|(c&{16{r[0]}});
assign  out_all[31:16] = {16{r[2]}}|(c&{16{r[1]}});
assign  out_all[47:32] = {16{r[3]}}|(c&{16{r[2]}});
assign  out_all[62:48] = c[14:0]&{15{r[3]}};

endmodule
//-------------------------------------------------------------------------
module Encoder_7(bin_in,out_all);
input [6:0] bin_in;
output [126:0] out_all;
wire [6:0] the_out;
wire [14:0] the_out1;

Encoder_3 row(bin_in[6:4],the_out);
Encoder_4 col(bin_in[3:0],the_out1);

wire [7:0]  r;
wire [15:0] c;
assign r = {the_out,1'b1};
assign c = {1'b0,the_out1};

assign  out_all[15:0] 	 = {16{r[1]}}|(c&{16{r[0]}});
assign  out_all[31:16] 	 = {16{r[2]}}|(c&{16{r[1]}});
assign  out_all[47:32] 	 = {16{r[3]}}|(c&{16{r[2]}});
assign  out_all[63:48] 	 = {16{r[4]}}|(c&{16{r[3]}});
assign  out_all[79:64] 	 = {16{r[5]}}|(c&{16{r[4]}});
assign  out_all[95:80] 	 = {16{r[6]}}|(c&{16{r[5]}});
assign  out_all[111:96]  = {16{r[7]}}|(c&{16{r[6]}});
assign  out_all[126:112] = c[14:0]&{15{r[7]}};

endmodule
//-------------------------------------------------------------------------
module Encoder_8(bin_in,out_all);
input [7:0] bin_in;
output [254:0] out_all;
wire [14:0] the_out, the_out1;

Encoder_4 row(bin_in[7:4],the_out);
Encoder_4 col(bin_in[3:0],the_out1);

wire [15:0] r,c;
assign r = {the_out,1'b1};
assign c = {1'b0,the_out1};

assign  out_all[15:0] = {16{r[1]}}|(c&{16{r[0]}});
assign  out_all[31:16] = {16{r[2]}}|(c&{16{r[1]}});
assign  out_all[47:32] = {16{r[3]}}|(c&{16{r[2]}});
assign  out_all[63:48] = {16{r[4]}}|(c&{16{r[3]}});
assign  out_all[79:64] = {16{r[5]}}|(c&{16{r[4]}});
assign  out_all[95:80] = {16{r[6]}}|(c&{16{r[5]}});
assign  out_all[111:96] = {16{r[7]}}|(c&{16{r[6]}});
assign  out_all[127:112] = {16{r[8]}}|(c&{16{r[7]}});
assign  out_all[143:128] = {16{r[9]}}|(c&{16{r[8]}});
assign  out_all[159:144] = {16{r[10]}}|(c&{16{r[9]}});
assign  out_all[175:160] = {16{r[11]}}|(c&{16{r[10]}});
assign  out_all[191:176] = {16{r[12]}}|(c&{16{r[11]}});
assign  out_all[207:192] = {16{r[13]}}|(c&{16{r[12]}});
assign  out_all[223:208] = {16{r[14]}}|(c&{16{r[13]}});
assign  out_all[239:224] = {16{r[15]}}|(c&{16{r[14]}});
assign  out_all[254:240] = c[14:0]&{15{r[15]}};

endmodule
//-------------------------------------------------------------------------
module Encoder_9(bin_in,out_all);
input [8:0] bin_in;
output [510:0] out_all;

wire [254:0] the_out1;

Encoder_8 col(bin_in[7:0],the_out1);

wire [255:0] c;
assign c = {1'b0,the_out1};

assign  out_all[255:0]    = {256{bin_in[8]}}| c;
assign  out_all[510:256]  = c[254:0]&{255{bin_in[8]}};
endmodule
//-------------------------------------------------------------------------
module Encoder_10(bin_in,out_all);
input [9:0] bin_in;
output [1022:0] out_all;

wire [2:0] the_out;
wire [254:0] the_out1;

Encoder_2 row(bin_in[9:8],the_out);
Encoder_8 col(bin_in[7:0],the_out1);

wire [3:0]  r;
wire [255:0] c;
assign r = {the_out,1'b1};
assign c = {1'b0,the_out1};

assign  out_all[255:0]    = {256{r[1]}}|(c&{256{r[0]}});
assign  out_all[511:256]  = {256{r[2]}}|(c&{256{r[1]}});
assign  out_all[767:512]  = {256{r[3]}}|(c&{256{r[2]}});
assign  out_all[1022:768] = c[254:0]&{255{r[3]}};

endmodule
//-------------------------------------------------------------------------
module Encoder_11(bin_in,out_all);
input [10:0] bin_in;
output [2046:0] out_all;

wire [1022:0] the_out1;

Encoder_10 col(bin_in[9:0],the_out1);

wire [1023:0] c;
assign c = {1'b0,the_out1};

assign  out_all[1023:0]    = {1024{bin_in[10]}}| c;
assign  out_all[2046:1024]  = c[1022:0]&{1023{bin_in[10]}};
endmodule
//-------------------------------------------------------------------------
module Encoder_12(bin_in,out_all);
input [11:0] bin_in;
output [4094:0] out_all;

wire [2:0] the_out;
wire [1022:0] the_out1;

Encoder_2 row(bin_in[11:10],the_out);
Encoder_10 col(bin_in[9:0],the_out1);

wire [3:0]  r;
wire [1023:0] c;
assign r = {the_out,1'b1};
assign c = {1'b0,the_out1};

assign  out_all[1023:0]    = {1024{r[1]}}|(c&{1024{r[0]}});
assign  out_all[2047:1024]  = {1024{r[2]}}|(c&{1024{r[1]}});
assign  out_all[3071:2048]  = {1024{r[3]}}|(c&{1024{r[2]}});
assign  out_all[4094:3072] = c[1022:0]&{1023{r[3]}};

endmodule
//-------------------------------------------------------------------------
module Encoder_13(bin_in,out_all);
input [12:0] bin_in;
output [8190:0] out_all;

wire [4094:0] the_out1;

Encoder_12 col(bin_in[11:0],the_out1);

wire [4095:0] c;
assign c = {1'b0,the_out1};

assign  out_all[4095:0]    = {4096{bin_in[12]}}| c;
assign  out_all[8190:4096]  = c[4094:0]&{4095{bin_in[12]}};
endmodule
//-------------------------------------------------------------------------
module Encoder_14(bin_in,out_all);
input [13:0] bin_in;
output [16382:0] out_all;

wire [2:0] the_out;
wire [4094:0] the_out1;

Encoder_2 row(bin_in[13:12],the_out);
Encoder_12 col(bin_in[11:0],the_out1);

wire [3:0]  r;
wire [4095:0] c;
assign r = {the_out,1'b1};
assign c = {1'b0,the_out1};

assign  out_all[4095:0]     = {4096{r[1]}}|(c&{4096{r[0]}});
assign  out_all[8191:4096]  = {4096{r[2]}}|(c&{4096{r[1]}});
assign  out_all[12287:8192] = {4096{r[3]}}|(c&{4096{r[2]}});
assign  out_all[16382:12288]= c[4094:0]&{4095{r[3]}};

endmodule
//-------------------------------------------------------------------------
module Encoder_15(bin_in,out_all);
input [14:0] bin_in;
output [32766:0] out_all;

wire [16382:0] the_out1;

Encoder_14 col(bin_in[13:0],the_out1);

wire [16383:0] c;
assign c = {1'b0,the_out1};

assign  out_all[16383:0]    = {16384{bin_in[14]}}| c;
assign  out_all[32766:16384]  = c[16382:0]&{16383{bin_in[14]}};
endmodule
//-------------------------------------------------------------------------
module Encoder_16(bin_in,out_all);
input [15:0] bin_in;
output [65534:0] out_all;

wire [2:0] the_out;
wire [16382:0] the_out1;

Encoder_2 row(bin_in[15:14],the_out);
Encoder_14 col(bin_in[13:0],the_out1);

wire [3:0]  r;
wire [16383:0] c;
assign r = {the_out,1'b1};
assign c = {1'b0,the_out1};

assign  out_all[16383:0]     = {16384{r[1]}}|(c&{16384{r[0]}});
assign  out_all[32767:16384]  = {16384{r[2]}}|(c&{16384{r[1]}});
assign  out_all[49151:32768] = {16384{r[3]}}|(c&{16384{r[2]}});
assign  out_all[65534:49152]= c[16382:0]&{16383{r[3]}};

endmodule
//-------------------------------------------------------------------------//=====================================================
module Decoder_1 (unary_in, bin_out);
input  unary_in;
output bin_out;

assign bin_out= unary_in;

endmodule
//-------------------------------------------------------------------------
module Decoder_2 (unary_in, bin_out);
input  [2:0]  unary_in;
output [1:0] bin_out;

assign bin_out[0] = (unary_in[1] == 1'b1) ? unary_in[2] : unary_in[0];
assign bin_out[1] = (unary_in[1] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_3 (unary_in, bin_out);
input  [6:0]  unary_in;
output [2:0] bin_out;

wire [2:0] unarytemp;

Decoder_2 LowerDec(unarytemp[2:0], bin_out[1:0]);

assign unarytemp = (unary_in[3] == 1'b1) ? unary_in[6:4] : unary_in[2:0];
assign bin_out[2]= (unary_in[3] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_4 (unary_in, bin_out);
input  [14:0]  unary_in;
output [3:0] bin_out;

wire [6:0] unarytemp;

Decoder_3 LowerDec(unarytemp[6:0], bin_out[2:0]);

assign unarytemp = (unary_in[7] == 1'b1) ? unary_in[14:8] : unary_in[6:0];
assign bin_out[3]= (unary_in[7] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_5 (unary_in, bin_out);
input  [30:0]  unary_in;
output [4:0] bin_out;

wire [14:0] unarytemp;

Decoder_4 LowerDec(unarytemp[14:0], bin_out[3:0]);

assign unarytemp = (unary_in[15] == 1'b1) ? unary_in[30:16] : unary_in[14:0];
assign bin_out[4]= (unary_in[15] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_6 (unary_in, bin_out);
input  [62:0]  unary_in;
output [5:0] bin_out;

wire [30:0] unarytemp;

Decoder_5 LowerDec(unarytemp[30:0], bin_out[4:0]);

assign unarytemp = (unary_in[31] == 1'b1) ? unary_in[62:32] : unary_in[30:0];
assign bin_out[5]= (unary_in[31] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_7 (unary_in, bin_out);
input  [126:0]  unary_in;
output [6:0] bin_out;

wire [62:0] unarytemp;

Decoder_6 LowerDec(unarytemp[62:0], bin_out[5:0]);

assign unarytemp = (unary_in[63] == 1'b1) ? unary_in[126:64] : unary_in[62:0];
assign bin_out[6]= (unary_in[63] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_8 (unary_in, bin_out);
input  [254:0]  unary_in;
output [7:0] bin_out;

wire [126:0] unarytemp;

Decoder_7 LowerDec(unarytemp[126:0], bin_out[6:0]);

assign unarytemp = (unary_in[127] == 1'b1) ? unary_in[254:128] : unary_in[126:0];
assign bin_out[7]= (unary_in[127] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_9 (unary_in, bin_out);
input  [510:0]  unary_in;
output [8:0] bin_out;

wire [254:0] unarytemp;

Decoder_8 LowerDec(unarytemp[254:0], bin_out[7:0]);

assign unarytemp = (unary_in[255] == 1'b1) ? unary_in[510:256] : unary_in[254:0];
assign bin_out[8]= (unary_in[255] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_10 (unary_in, bin_out);
input  [1022:0]  unary_in;
output [9:0] bin_out;

wire [510:0] unarytemp;

Decoder_9 LowerDec(unarytemp[510:0], bin_out[8:0]);

assign unarytemp = (unary_in[511] == 1'b1) ? unary_in[1022:512] : unary_in[510:0];
assign bin_out[9]= (unary_in[511] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_11 (unary_in, bin_out);
input  [2046:0]  unary_in;
output [10:0] bin_out;

wire [1022:0] unarytemp;

Decoder_10 LowerDec(unarytemp[1022:0], bin_out[9:0]);

assign unarytemp  = (unary_in[1023] == 1'b1) ? unary_in[2046:1024] : unary_in[1022:0];
assign bin_out[10]= (unary_in[1023] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_12 (unary_in, bin_out);
input  [4094:0]  unary_in;
output [11:0] bin_out;

wire [2046:0] unarytemp;

Decoder_11 LowerDec(unarytemp[2046:0], bin_out[10:0]);

assign unarytemp  = (unary_in[2047] == 1'b1) ? unary_in[4094:2048] : unary_in[2046:0];
assign bin_out[11]= (unary_in[2047] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_13 (unary_in, bin_out);
input  [8190:0]  unary_in;
output [12:0] bin_out;

wire [4094:0] unarytemp;

Decoder_12 LowerDec(unarytemp[4094:0], bin_out[11:0]);

assign unarytemp  = (unary_in[4095] == 1'b1) ? unary_in[8190:4096] : unary_in[4094:0];
assign bin_out[12]= (unary_in[4095] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_14 (unary_in, bin_out);
input  [16382:0]  unary_in;
output [13:0] bin_out;

wire [8190:0] unarytemp;

Decoder_13 LowerDec(unarytemp[8190:0], bin_out[12:0]);

assign unarytemp  = (unary_in[8191] == 1'b1) ? unary_in[16382:8192] : unary_in[8190:0];
assign bin_out[13]= (unary_in[8191] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_15 (unary_in, bin_out);
input  [32766:0]  unary_in;
output [14:0] bin_out;

wire [16382:0] unarytemp;

Decoder_14 LowerDec(unarytemp[16382:0], bin_out[13:0]);

assign unarytemp  = (unary_in[16383] == 1'b1) ? unary_in[32766:16384] : unary_in[16382:0];
assign bin_out[14]= (unary_in[16383] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------
module Decoder_16 (unary_in, bin_out);
input  [65534:0]  unary_in;
output [15:0] bin_out;

wire [32766:0] unarytemp;

Decoder_15 LowerDec(unarytemp[32766:0], bin_out[14:0]);

assign unarytemp  = (unary_in[32767] == 1'b1) ? unary_in[65534:32768] : unary_in[32766:0];
assign bin_out[15]= (unary_in[32767] == 1'b1) ? 1 : 0;

endmodule
//-------------------------------------------------------------------------