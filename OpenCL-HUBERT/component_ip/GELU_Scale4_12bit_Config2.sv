`timescale 1ns / 1ps

module AHBU(input wire[11:0] bin_in, output wire[11:0] bin_out);

//----> In_Unary
wire [14:0] In_Unary15;

//----> Out and Out_Unary
wire [6:0] Out_Unary1; wire [2:0] Out1;

//----> Encoders
Encoder_4 Enc1(bin_in[3:0], In_Unary15);

//----> Decoders
Decoder_3 Dec1(Out_Unary1, Out1);

//----> SubFunctions
SubFunction_1 SF1(In_Unary15, Out_Unary1);

//----> Mux
assign bin_out = (bin_in < 16) ? {9'b0, {0{1'b0}}, Out1}:
		 (bin_in < 32) ? {9'b1, {0{1'b0}}, Out1}:
		 (bin_in < 48) ? {9'b10, {0{1'b0}}, Out1}:
		 (bin_in < 64) ? {9'b11, {0{1'b0}}, Out1}:
		 (bin_in < 80) ? {9'b100, {0{1'b0}}, Out1}:
		 (bin_in < 96) ? {9'b110, {0{1'b0}}, Out1}:
		 (bin_in < 112) ? {9'b111, {0{1'b0}}, Out1}:
		 (bin_in < 128) ? {9'b1000, {0{1'b0}}, Out1}:
		 (bin_in < 144) ? {9'b1010, {0{1'b0}}, Out1}:
		 (bin_in < 160) ? {9'b1011, {0{1'b0}}, Out1}:
		 (bin_in < 176) ? {9'b1101, {0{1'b0}}, Out1}:
		 (bin_in < 192) ? {9'b1110, {0{1'b0}}, Out1}:
		 (bin_in < 208) ? {9'b10000, {0{1'b0}}, Out1}:
		 (bin_in < 224) ? {9'b10001, {0{1'b0}}, Out1}:
		 (bin_in < 240) ? {9'b10011, {0{1'b0}}, Out1}:
		 (bin_in < 256) ? {9'b10101, {0{1'b0}}, Out1}:
		 (bin_in < 272) ? {9'b10110, {0{1'b0}}, Out1}:
		 (bin_in < 288) ? {9'b11000, {0{1'b0}}, Out1}:
		 (bin_in < 304) ? {9'b11010, {0{1'b0}}, Out1}:
		 (bin_in < 320) ? {9'b11100, {0{1'b0}}, Out1}:
		 (bin_in < 336) ? {9'b11110, {0{1'b0}}, Out1}:
		 (bin_in < 352) ? {9'b100000, {0{1'b0}}, Out1}:
		 (bin_in < 368) ? {9'b100010, {0{1'b0}}, Out1}:
		 (bin_in < 384) ? {9'b100100, {0{1'b0}}, Out1}:
		 (bin_in < 400) ? {9'b100110, {0{1'b0}}, Out1}:
		 (bin_in < 416) ? {9'b101000, {0{1'b0}}, Out1}:
		 (bin_in < 432) ? {9'b101010, {0{1'b0}}, Out1}:
		 (bin_in < 448) ? {9'b101100, {0{1'b0}}, Out1}:
		 (bin_in < 464) ? {9'b101110, {0{1'b0}}, Out1}:
		 (bin_in < 480) ? {9'b110000, {0{1'b0}}, Out1}:
		 (bin_in < 496) ? {9'b110010, {0{1'b0}}, Out1}:
		 (bin_in < 512) ? {9'b110100, {0{1'b0}}, Out1}:
		 (bin_in < 528) ? {9'b110110, {0{1'b0}}, Out1}:
		 (bin_in < 544) ? {9'b111001, {0{1'b0}}, Out1}:
		 (bin_in < 560) ? {9'b111011, {0{1'b0}}, Out1}:
		 (bin_in < 576) ? {9'b111101, {0{1'b0}}, Out1}:
		 (bin_in < 592) ? {9'b111111, {0{1'b0}}, Out1}:
		 (bin_in < 608) ? {9'b1000001, {0{1'b0}}, Out1}:
		 (bin_in < 624) ? {9'b1000100, {0{1'b0}}, Out1}:
		 (bin_in < 640) ? {9'b1000110, {0{1'b0}}, Out1}:
		 (bin_in < 656) ? {9'b1001000, {0{1'b0}}, Out1}:
		 (bin_in < 672) ? {9'b1001010, {0{1'b0}}, Out1}:
		 (bin_in < 688) ? {9'b1001101, {0{1'b0}}, Out1}:
		 (bin_in < 704) ? {9'b1001111, {0{1'b0}}, Out1}:
		 (bin_in < 720) ? {9'b1010001, {0{1'b0}}, Out1}:
		 (bin_in < 736) ? {9'b1010011, {0{1'b0}}, Out1}:
		 (bin_in < 752) ? {9'b1010110, {0{1'b0}}, Out1}:
		 (bin_in < 768) ? {9'b1011000, {0{1'b0}}, Out1}:
		 (bin_in < 784) ? {9'b1011010, {0{1'b0}}, Out1}:
		 (bin_in < 800) ? {9'b1011100, {0{1'b0}}, Out1}:
		 (bin_in < 816) ? {9'b1011111, {0{1'b0}}, Out1}:
		 (bin_in < 832) ? {9'b1100001, {0{1'b0}}, Out1}:
		 (bin_in < 848) ? {9'b1100011, {0{1'b0}}, Out1}:
		 (bin_in < 864) ? {9'b1100101, {0{1'b0}}, Out1}:
		 (bin_in < 880) ? {9'b1101000, {0{1'b0}}, Out1}:
		 (bin_in < 896) ? {9'b1101010, {0{1'b0}}, Out1}:
		 (bin_in < 912) ? {9'b1101100, {0{1'b0}}, Out1}:
		 (bin_in < 928) ? {9'b1101110, {0{1'b0}}, Out1}:
		 (bin_in < 944) ? {9'b1110000, {0{1'b0}}, Out1}:
		 (bin_in < 960) ? {9'b1110011, {0{1'b0}}, Out1}:
		 (bin_in < 976) ? {9'b1110101, {0{1'b0}}, Out1}:
		 (bin_in < 992) ? {9'b1110111, {0{1'b0}}, Out1}:
		 (bin_in < 1008) ? {9'b1111001, {0{1'b0}}, Out1}:
		 (bin_in < 1024) ? {9'b1111011, {0{1'b0}}, Out1}:
		 (bin_in < 1040) ? {9'b1111110, {0{1'b0}}, Out1}:
		 (bin_in < 1056) ? {9'b10000000, {0{1'b0}}, Out1}:
		 (bin_in < 1072) ? {9'b10000010, {0{1'b0}}, Out1}:
		 (bin_in < 1088) ? {9'b10000100, {0{1'b0}}, Out1}:
		 (bin_in < 1104) ? {9'b10000110, {0{1'b0}}, Out1}:
		 (bin_in < 1120) ? {9'b10001000, {0{1'b0}}, Out1}:
		 (bin_in < 1136) ? {9'b10001010, {0{1'b0}}, Out1}:
		 (bin_in < 1152) ? {9'b10001101, {0{1'b0}}, Out1}:
		 (bin_in < 1168) ? {9'b10001111, {0{1'b0}}, Out1}:
		 (bin_in < 1184) ? {9'b10010001, {0{1'b0}}, Out1}:
		 (bin_in < 1200) ? {9'b10010011, {0{1'b0}}, Out1}:
		 (bin_in < 1216) ? {9'b10010101, {0{1'b0}}, Out1}:
		 (bin_in < 1232) ? {9'b10010111, {0{1'b0}}, Out1}:
		 (bin_in < 1248) ? {9'b10011001, {0{1'b0}}, Out1}:
		 (bin_in < 1264) ? {9'b10011011, {0{1'b0}}, Out1}:
		 (bin_in < 1280) ? {9'b10011101, {0{1'b0}}, Out1}:
		 (bin_in < 1296) ? {9'b10011111, {0{1'b0}}, Out1}:
		 (bin_in < 1312) ? {9'b10100010, {0{1'b0}}, Out1}:
		 (bin_in < 1328) ? {9'b10100100, {0{1'b0}}, Out1}:
		 (bin_in < 1344) ? {9'b10100110, {0{1'b0}}, Out1}:
		 (bin_in < 1360) ? {9'b10101000, {0{1'b0}}, Out1}:
		 (bin_in < 1376) ? {9'b10101010, {0{1'b0}}, Out1}:
		 (bin_in < 1392) ? {9'b10101100, {0{1'b0}}, Out1}:
		 (bin_in < 1408) ? {9'b10101110, {0{1'b0}}, Out1}:
		 (bin_in < 1424) ? {9'b10110000, {0{1'b0}}, Out1}:
		 (bin_in < 1440) ? {9'b10110010, {0{1'b0}}, Out1}:
		 (bin_in < 1456) ? {9'b10110100, {0{1'b0}}, Out1}:
		 (bin_in < 1472) ? {9'b10110110, {0{1'b0}}, Out1}:
		 (bin_in < 1488) ? {9'b10111000, {0{1'b0}}, Out1}:
		 (bin_in < 1504) ? {9'b10111010, {0{1'b0}}, Out1}:
		 (bin_in < 1520) ? {9'b10111100, {0{1'b0}}, Out1}:
		 (bin_in < 1536) ? {9'b10111110, {0{1'b0}}, Out1}:
		 (bin_in < 1552) ? {9'b11000000, {0{1'b0}}, Out1}:
		 (bin_in < 1568) ? {9'b11000010, {0{1'b0}}, Out1}:
		 (bin_in < 1584) ? {9'b11000100, {0{1'b0}}, Out1}:
		 (bin_in < 1600) ? {9'b11000110, {0{1'b0}}, Out1}:
		 (bin_in < 1616) ? {9'b11001000, {0{1'b0}}, Out1}:
		 (bin_in < 1632) ? {9'b11001010, {0{1'b0}}, Out1}:
		 (bin_in < 1648) ? {9'b11001100, {0{1'b0}}, Out1}:
		 (bin_in < 1664) ? {9'b11001110, {0{1'b0}}, Out1}:
		 (bin_in < 1680) ? {9'b11010000, {0{1'b0}}, Out1}:
		 (bin_in < 1696) ? {9'b11010010, {0{1'b0}}, Out1}:
		 (bin_in < 1712) ? {9'b11010100, {0{1'b0}}, Out1}:
		 (bin_in < 1728) ? {9'b11010110, {0{1'b0}}, Out1}:
		 (bin_in < 1744) ? {9'b11011000, {0{1'b0}}, Out1}:
		 (bin_in < 1760) ? {9'b11011010, {0{1'b0}}, Out1}:
		 (bin_in < 1776) ? {9'b11011100, {0{1'b0}}, Out1}:
		 (bin_in < 1792) ? {9'b11011110, {0{1'b0}}, Out1}:
		 (bin_in < 1808) ? {9'b11100000, {0{1'b0}}, Out1}:
		 (bin_in < 1824) ? {9'b11100010, {0{1'b0}}, Out1}:
		 (bin_in < 1840) ? {9'b11100100, {0{1'b0}}, Out1}:
		 (bin_in < 1856) ? {9'b11100110, {0{1'b0}}, Out1}:
		 (bin_in < 1872) ? {9'b11101000, {0{1'b0}}, Out1}:
		 (bin_in < 1888) ? {9'b11101010, {0{1'b0}}, Out1}:
		 (bin_in < 1904) ? {9'b11101100, {0{1'b0}}, Out1}:
		 (bin_in < 1920) ? {9'b11101110, {0{1'b0}}, Out1}:
		 (bin_in < 1936) ? {9'b11110000, {0{1'b0}}, Out1}:
		 (bin_in < 1952) ? {9'b11110010, {0{1'b0}}, Out1}:
		 (bin_in < 1968) ? {9'b11110100, {0{1'b0}}, Out1}:
		 (bin_in < 1984) ? {9'b11110110, {0{1'b0}}, Out1}:
		 (bin_in < 2000) ? {9'b11111000, {0{1'b0}}, Out1}:
		 (bin_in < 2016) ? {9'b11111010, {0{1'b0}}, Out1}:
		 (bin_in < 2032) ? {9'b11111100, {0{1'b0}}, Out1}:
		 (bin_in < 2048) ? {9'b11111110, {0{1'b0}}, Out1}:
		 (bin_in < 2064) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2080) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2096) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2112) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2128) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2144) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2160) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2176) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2192) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2208) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2224) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2240) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2256) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2272) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2288) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2304) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2320) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2336) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2352) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2368) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2384) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2400) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2416) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2432) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2448) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2464) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2480) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2496) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2512) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2528) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2544) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2560) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2576) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2592) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2608) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2624) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2640) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2656) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2672) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2688) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2704) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2720) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2736) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2752) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2768) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2784) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2800) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2816) ? {9'b111111111, {0{1'b0}}, Out1}:
		 (bin_in < 2832) ? {9'b111111110, {0{1'b0}}, Out1}:
		 (bin_in < 2848) ? {9'b111111110, {0{1'b0}}, Out1}:
		 (bin_in < 2864) ? {9'b111111110, {0{1'b0}}, Out1}:
		 (bin_in < 2880) ? {9'b111111110, {0{1'b0}}, Out1}:
		 (bin_in < 2896) ? {9'b111111110, {0{1'b0}}, Out1}:
		 (bin_in < 2912) ? {9'b111111110, {0{1'b0}}, Out1}:
		 (bin_in < 2928) ? {9'b111111110, {0{1'b0}}, Out1}:
		 (bin_in < 2944) ? {9'b111111110, {0{1'b0}}, Out1}:
		 (bin_in < 2960) ? {9'b111111110, {0{1'b0}}, Out1}:
		 (bin_in < 2976) ? {9'b111111110, {0{1'b0}}, Out1}:
		 (bin_in < 2992) ? {9'b111111101, {0{1'b0}}, Out1}:
		 (bin_in < 3008) ? {9'b111111101, {0{1'b0}}, Out1}:
		 (bin_in < 3024) ? {9'b111111101, {0{1'b0}}, Out1}:
		 (bin_in < 3040) ? {9'b111111101, {0{1'b0}}, Out1}:
		 (bin_in < 3056) ? {9'b111111101, {0{1'b0}}, Out1}:
		 (bin_in < 3072) ? {9'b111111101, {0{1'b0}}, Out1}:
		 (bin_in < 3088) ? {9'b111111101, {0{1'b0}}, Out1}:
		 (bin_in < 3104) ? {9'b111111100, {0{1'b0}}, Out1}:
		 (bin_in < 3120) ? {9'b111111100, {0{1'b0}}, Out1}:
		 (bin_in < 3136) ? {9'b111111100, {0{1'b0}}, Out1}:
		 (bin_in < 3152) ? {9'b111111100, {0{1'b0}}, Out1}:
		 (bin_in < 3168) ? {9'b111111100, {0{1'b0}}, Out1}:
		 (bin_in < 3184) ? {9'b111111011, {0{1'b0}}, Out1}:
		 (bin_in < 3200) ? {9'b111111011, {0{1'b0}}, Out1}:
		 (bin_in < 3216) ? {9'b111111011, {0{1'b0}}, Out1}:
		 (bin_in < 3232) ? {9'b111111011, {0{1'b0}}, Out1}:
		 (bin_in < 3248) ? {9'b111111010, {0{1'b0}}, Out1}:
		 (bin_in < 3264) ? {9'b111111010, {0{1'b0}}, Out1}:
		 (bin_in < 3280) ? {9'b111111010, {0{1'b0}}, Out1}:
		 (bin_in < 3296) ? {9'b111111010, {0{1'b0}}, Out1}:
		 (bin_in < 3312) ? {9'b111111001, {0{1'b0}}, Out1}:
		 (bin_in < 3328) ? {9'b111111001, {0{1'b0}}, Out1}:
		 (bin_in < 3344) ? {9'b111111001, {0{1'b0}}, Out1}:
		 (bin_in < 3360) ? {9'b111111001, {0{1'b0}}, Out1}:
		 (bin_in < 3376) ? {9'b111111000, {0{1'b0}}, Out1}:
		 (bin_in < 3392) ? {9'b111111000, {0{1'b0}}, Out1}:
		 (bin_in < 3408) ? {9'b111111000, {0{1'b0}}, Out1}:
		 (bin_in < 3424) ? {9'b111111000, {0{1'b0}}, Out1}:
		 (bin_in < 3440) ? {9'b111110111, {0{1'b0}}, Out1}:
		 (bin_in < 3456) ? {9'b111110111, {0{1'b0}}, Out1}:
		 (bin_in < 3472) ? {9'b111110111, {0{1'b0}}, Out1}:
		 (bin_in < 3488) ? {9'b111110111, {0{1'b0}}, Out1}:
		 (bin_in < 3504) ? {9'b111110110, {0{1'b0}}, Out1}:
		 (bin_in < 3520) ? {9'b111110110, {0{1'b0}}, Out1}:
		 (bin_in < 3536) ? {9'b111110110, {0{1'b0}}, Out1}:
		 (bin_in < 3552) ? {9'b111110110, {0{1'b0}}, Out1}:
		 (bin_in < 3568) ? {9'b111110110, {0{1'b0}}, Out1}:
		 (bin_in < 3584) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3600) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3616) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3632) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3648) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3664) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3680) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3696) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3712) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3728) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3744) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3760) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3776) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3792) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3808) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3824) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3840) ? {9'b111110101, {0{1'b0}}, Out1}:
		 (bin_in < 3856) ? {9'b111110110, {0{1'b0}}, Out1}:
		 (bin_in < 3872) ? {9'b111110110, {0{1'b0}}, Out1}:
		 (bin_in < 3888) ? {9'b111110110, {0{1'b0}}, Out1}:
		 (bin_in < 3904) ? {9'b111110111, {0{1'b0}}, Out1}:
		 (bin_in < 3920) ? {9'b111110111, {0{1'b0}}, Out1}:
		 (bin_in < 3936) ? {9'b111111000, {0{1'b0}}, Out1}:
		 (bin_in < 3952) ? {9'b111111000, {0{1'b0}}, Out1}:
		 (bin_in < 3968) ? {9'b111111001, {0{1'b0}}, Out1}:
		 (bin_in < 3984) ? {9'b111111001, {0{1'b0}}, Out1}:
		 (bin_in < 4000) ? {9'b111111010, {0{1'b0}}, Out1}:
		 (bin_in < 4016) ? {9'b111111011, {0{1'b0}}, Out1}:
		 (bin_in < 4032) ? {9'b111111011, {0{1'b0}}, Out1}:
		 (bin_in < 4048) ? {9'b111111100, {0{1'b0}}, Out1}:
		 (bin_in < 4064) ? {9'b111111101, {0{1'b0}}, Out1}:
		 (bin_in < 4080) ? {9'b111111110, {0{1'b0}}, Out1}:
		 {9'b111111111, {0{1'b0}}, Out1};

endmodule

//=========

module SubFunction_1(input wire[14:0] In, output wire[6:0] Out);
assign Out[0] = In[1];
assign Out[1] = In[3];
assign Out[2] = In[5];
assign Out[3] = In[7];
assign Out[4] = In[9];
assign Out[5] = In[11];
assign Out[6] = In[13];
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