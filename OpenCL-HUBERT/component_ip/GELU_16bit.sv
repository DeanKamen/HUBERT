`timescale 1ns / 1ps


module AHBU(input wire[15:0] bin_in, output wire[15:0] bin_out);

//----> In_Unary
wire [62:0] In_Unary63;
wire [126:0] In_Unary127;
wire [254:0] In_Unary255;

//----> Out and Out_Unary
wire [6:0] Out_Unary1; wire [2:0] Out1;
wire [6:0] Out_Unary201; wire [2:0] Out201;
wire [6:0] Out_Unary203; wire [2:0] Out203;

//----> Encoders
Encoder_6 Enc1(bin_in[5:0], In_Unary63);
Encoder_7 Enc2(bin_in[6:0], In_Unary127);
Encoder_8 Enc3(bin_in[7:0], In_Unary255);

//----> Decoders
Decoder_3 Dec1(Out_Unary1, Out1);
Decoder_3 Dec201(Out_Unary201, Out201);
Decoder_3 Dec203(Out_Unary203, Out203);

//----> SubFunctions
SubFunction_1 SF1(In_Unary255, Out_Unary1);
SubFunction_201 SF201(In_Unary63, Out_Unary201);
SubFunction_203 SF203(In_Unary127, Out_Unary203);

//----> Mux
assign bin_out = (bin_in < 256) ? {13'b1001, {0{1'b0}}, Out1}:
		 (bin_in < 512) ? {13'b11111, {0{1'b0}}, Out1}:
		 (bin_in < 768) ? {13'b111001, {0{1'b0}}, Out1}:
		 (bin_in < 1024) ? {13'b1010111, {0{1'b0}}, Out1}:
		 (bin_in < 1280) ? {13'b1111000, {0{1'b0}}, Out1}:
		 (bin_in < 1536) ? {13'b10011011, {0{1'b0}}, Out1}:
		 (bin_in < 1792) ? {13'b11000001, {0{1'b0}}, Out1}:
		 (bin_in < 2048) ? {13'b11101000, {0{1'b0}}, Out1}:
		 (bin_in < 2304) ? {13'b100010000, {0{1'b0}}, Out1}:
		 (bin_in < 2560) ? {13'b100111000, {0{1'b0}}, Out1}:
		 (bin_in < 2816) ? {13'b101100000, {0{1'b0}}, Out1}:
		 (bin_in < 3072) ? {13'b110001000, {0{1'b0}}, Out1}:
		 (bin_in < 3328) ? {13'b110101111, {0{1'b0}}, Out1}:
		 (bin_in < 3584) ? {13'b111010110, {0{1'b0}}, Out1}:
		 (bin_in < 3840) ? {13'b111111100, {0{1'b0}}, Out1}:
		 (bin_in < 4096) ? {13'b1000100010, {0{1'b0}}, Out1}:
		 (bin_in < 4352) ? {13'b1001000111, {0{1'b0}}, Out1}:
		 (bin_in < 4608) ? {13'b1001101100, {0{1'b0}}, Out1}:
		 (bin_in < 4864) ? {13'b1010010001, {0{1'b0}}, Out1}:
		 (bin_in < 5120) ? {13'b1010110101, {0{1'b0}}, Out1}:
		 (bin_in < 5376) ? {13'b1011011001, {0{1'b0}}, Out1}:
		 (bin_in < 5632) ? {13'b1011111101, {0{1'b0}}, Out1}:
		 (bin_in < 5888) ? {13'b1100100001, {0{1'b0}}, Out1}:
		 (bin_in < 6144) ? {13'b1101000101, {0{1'b0}}, Out1}:
		 (bin_in < 6400) ? {13'b1101101000, {0{1'b0}}, Out1}:
		 (bin_in < 6656) ? {13'b1110001100, {0{1'b0}}, Out1}:
		 (bin_in < 6912) ? {13'b1110110000, {0{1'b0}}, Out1}:
		 (bin_in < 7168) ? {13'b1111010011, {0{1'b0}}, Out1}:
		 (bin_in < 7424) ? {13'b1111110111, {0{1'b0}}, Out1}:
		 (bin_in < 7680) ? {13'b10000011011, {0{1'b0}}, Out1}:
		 (bin_in < 7936) ? {13'b10000111110, {0{1'b0}}, Out1}:
		 (bin_in < 8192) ? {13'b10001100010, {0{1'b0}}, Out1}:
		 (bin_in < 8448) ? {13'b10010000101, {0{1'b0}}, Out1}:
		 (bin_in < 8704) ? {13'b10010101001, {0{1'b0}}, Out1}:
		 (bin_in < 8960) ? {13'b10011001101, {0{1'b0}}, Out1}:
		 (bin_in < 9216) ? {13'b10011110000, {0{1'b0}}, Out1}:
		 (bin_in < 9472) ? {13'b10100010100, {0{1'b0}}, Out1}:
		 (bin_in < 9728) ? {13'b10100111000, {0{1'b0}}, Out1}:
		 (bin_in < 9984) ? {13'b10101011011, {0{1'b0}}, Out1}:
		 (bin_in < 10240) ? {13'b10101111111, {0{1'b0}}, Out1}:
		 (bin_in < 10496) ? {13'b10110100011, {0{1'b0}}, Out1}:
		 (bin_in < 10752) ? {13'b10111000110, {0{1'b0}}, Out1}:
		 (bin_in < 11008) ? {13'b10111101010, {0{1'b0}}, Out1}:
		 (bin_in < 11264) ? {13'b11000001101, {0{1'b0}}, Out1}:
		 (bin_in < 11520) ? {13'b11000110001, {0{1'b0}}, Out1}:
		 (bin_in < 11776) ? {13'b11001010101, {0{1'b0}}, Out1}:
		 (bin_in < 12032) ? {13'b11001111000, {0{1'b0}}, Out1}:
		 (bin_in < 12288) ? {13'b11010011100, {0{1'b0}}, Out1}:
		 (bin_in < 12544) ? {13'b11011000000, {0{1'b0}}, Out1}:
		 (bin_in < 12800) ? {13'b11011100011, {0{1'b0}}, Out1}:
		 (bin_in < 13056) ? {13'b11100000111, {0{1'b0}}, Out1}:
		 (bin_in < 13312) ? {13'b11100101010, {0{1'b0}}, Out1}:
		 (bin_in < 13568) ? {13'b11101001110, {0{1'b0}}, Out1}:
		 (bin_in < 13824) ? {13'b11101110010, {0{1'b0}}, Out1}:
		 (bin_in < 14080) ? {13'b11110010101, {0{1'b0}}, Out1}:
		 (bin_in < 14336) ? {13'b11110111001, {0{1'b0}}, Out1}:
		 (bin_in < 14592) ? {13'b11111011101, {0{1'b0}}, Out1}:
		 (bin_in < 14848) ? {13'b100000000000, {0{1'b0}}, Out1}:
		 (bin_in < 15104) ? {13'b100000100100, {0{1'b0}}, Out1}:
		 (bin_in < 15360) ? {13'b100001001000, {0{1'b0}}, Out1}:
		 (bin_in < 15616) ? {13'b100001101011, {0{1'b0}}, Out1}:
		 (bin_in < 15872) ? {13'b100010001111, {0{1'b0}}, Out1}:
		 (bin_in < 16128) ? {13'b100010110010, {0{1'b0}}, Out1}:
		 (bin_in < 16384) ? {13'b100011010110, {0{1'b0}}, Out1}:
		 (bin_in < 16640) ? {13'b100011111010, {0{1'b0}}, Out1}:
		 (bin_in < 16896) ? {13'b100100011101, {0{1'b0}}, Out1}:
		 (bin_in < 17152) ? {13'b100101000001, {0{1'b0}}, Out1}:
		 (bin_in < 17408) ? {13'b100101100101, {0{1'b0}}, Out1}:
		 (bin_in < 17664) ? {13'b100110001000, {0{1'b0}}, Out1}:
		 (bin_in < 17920) ? {13'b100110101100, {0{1'b0}}, Out1}:
		 (bin_in < 18176) ? {13'b100111010000, {0{1'b0}}, Out1}:
		 (bin_in < 18432) ? {13'b100111110011, {0{1'b0}}, Out1}:
		 (bin_in < 18688) ? {13'b101000010111, {0{1'b0}}, Out1}:
		 (bin_in < 18944) ? {13'b101000111010, {0{1'b0}}, Out1}:
		 (bin_in < 19200) ? {13'b101001011110, {0{1'b0}}, Out1}:
		 (bin_in < 19456) ? {13'b101010000010, {0{1'b0}}, Out1}:
		 (bin_in < 19712) ? {13'b101010100101, {0{1'b0}}, Out1}:
		 (bin_in < 19968) ? {13'b101011001001, {0{1'b0}}, Out1}:
		 (bin_in < 20224) ? {13'b101011101101, {0{1'b0}}, Out1}:
		 (bin_in < 20480) ? {13'b101100010000, {0{1'b0}}, Out1}:
		 (bin_in < 20736) ? {13'b101100110100, {0{1'b0}}, Out1}:
		 (bin_in < 20992) ? {13'b101101010111, {0{1'b0}}, Out1}:
		 (bin_in < 21248) ? {13'b101101111011, {0{1'b0}}, Out1}:
		 (bin_in < 21504) ? {13'b101110011111, {0{1'b0}}, Out1}:
		 (bin_in < 21760) ? {13'b101111000010, {0{1'b0}}, Out1}:
		 (bin_in < 22016) ? {13'b101111100110, {0{1'b0}}, Out1}:
		 (bin_in < 22272) ? {13'b110000001010, {0{1'b0}}, Out1}:
		 (bin_in < 22528) ? {13'b110000101101, {0{1'b0}}, Out1}:
		 (bin_in < 22784) ? {13'b110001010001, {0{1'b0}}, Out1}:
		 (bin_in < 23040) ? {13'b110001110101, {0{1'b0}}, Out1}:
		 (bin_in < 23296) ? {13'b110010011000, {0{1'b0}}, Out1}:
		 (bin_in < 23552) ? {13'b110010111100, {0{1'b0}}, Out1}:
		 (bin_in < 23808) ? {13'b110011011111, {0{1'b0}}, Out1}:
		 (bin_in < 24064) ? {13'b110100000011, {0{1'b0}}, Out1}:
		 (bin_in < 24320) ? {13'b110100100111, {0{1'b0}}, Out1}:
		 (bin_in < 24576) ? {13'b110101001010, {0{1'b0}}, Out1}:
		 (bin_in < 24832) ? {13'b110101101110, {0{1'b0}}, Out1}:
		 (bin_in < 25088) ? {13'b110110010010, {0{1'b0}}, Out1}:
		 (bin_in < 25344) ? {13'b110110110101, {0{1'b0}}, Out1}:
		 (bin_in < 25600) ? {13'b110111011001, {0{1'b0}}, Out1}:
		 (bin_in < 25856) ? {13'b110111111100, {0{1'b0}}, Out1}:
		 (bin_in < 26112) ? {13'b111000100000, {0{1'b0}}, Out1}:
		 (bin_in < 26368) ? {13'b111001000100, {0{1'b0}}, Out1}:
		 (bin_in < 26624) ? {13'b111001100111, {0{1'b0}}, Out1}:
		 (bin_in < 26880) ? {13'b111010001011, {0{1'b0}}, Out1}:
		 (bin_in < 27136) ? {13'b111010101111, {0{1'b0}}, Out1}:
		 (bin_in < 27392) ? {13'b111011010010, {0{1'b0}}, Out1}:
		 (bin_in < 27648) ? {13'b111011110110, {0{1'b0}}, Out1}:
		 (bin_in < 27904) ? {13'b111100011010, {0{1'b0}}, Out1}:
		 (bin_in < 28160) ? {13'b111100111101, {0{1'b0}}, Out1}:
		 (bin_in < 28416) ? {13'b111101100001, {0{1'b0}}, Out1}:
		 (bin_in < 28672) ? {13'b111110000100, {0{1'b0}}, Out1}:
		 (bin_in < 28928) ? {13'b111110101000, {0{1'b0}}, Out1}:
		 (bin_in < 29184) ? {13'b111111001100, {0{1'b0}}, Out1}:
		 (bin_in < 29440) ? {13'b111111101111, {0{1'b0}}, Out1}:
		 (bin_in < 29696) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 29952) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 30208) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 30464) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 30720) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 30976) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 31232) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 31488) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 31744) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 32000) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 32256) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 32512) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 32768) ? {13'b111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 33024) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 33280) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 33536) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 33792) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 34048) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 34304) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 34560) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 34816) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 35072) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 35328) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 35584) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 35840) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 36096) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 36352) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 36608) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 36864) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 37120) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 37376) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 37632) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 37888) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 38144) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 38400) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 38656) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 38912) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 39168) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 39424) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 39680) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 39936) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 40192) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 40448) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 40704) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 40960) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 41216) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 41472) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 41728) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 41984) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 42240) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 42496) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 42752) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 43008) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 43264) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 43520) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 43776) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 44032) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 44288) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 44544) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 44800) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 45056) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 45312) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 45568) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 45824) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 46080) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 46336) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 46592) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 46848) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 47104) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 47360) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 47616) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 47872) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 48128) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 48384) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 48640) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 48896) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 49152) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 49408) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 49664) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 49920) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 50176) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 50432) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 50688) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 50944) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 51200) ? {13'b0, {0{1'b0}}, Out1}:
		 (bin_in < 51264) ? {13'b0, {0{1'b0}}, Out201}:
		 (bin_in < 51328) ? {13'b1111111111111, {0{1'b0}}, Out201}:
		 (bin_in < 51456) ? {13'b1111111111111, {0{1'b0}}, Out203}:
		 (bin_in < 51712) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 51968) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 52224) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 52480) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 52736) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 52992) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 53248) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 53504) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 53760) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 54016) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 54272) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 54528) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 54784) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 55040) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 55296) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 55552) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 55808) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 56064) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 56320) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 56576) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 56832) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 57088) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 57344) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 57600) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 57856) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 58112) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 58368) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 58624) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 58880) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 59136) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 59392) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 59648) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 59904) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 60160) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 60416) ? {13'b1111111111111, {0{1'b0}}, Out1}:
		 (bin_in < 60672) ? {13'b1111111111110, {0{1'b0}}, Out1}:
		 (bin_in < 60928) ? {13'b1111111111110, {0{1'b0}}, Out1}:
		 (bin_in < 61184) ? {13'b1111111111101, {0{1'b0}}, Out1}:
		 (bin_in < 61440) ? {13'b1111111111100, {0{1'b0}}, Out1}:
		 (bin_in < 61696) ? {13'b1111111111010, {0{1'b0}}, Out1}:
		 (bin_in < 61952) ? {13'b1111111111000, {0{1'b0}}, Out1}:
		 (bin_in < 62208) ? {13'b1111111110101, {0{1'b0}}, Out1}:
		 (bin_in < 62464) ? {13'b1111111110010, {0{1'b0}}, Out1}:
		 (bin_in < 62720) ? {13'b1111111101110, {0{1'b0}}, Out1}:
		 (bin_in < 62976) ? {13'b1111111101010, {0{1'b0}}, Out1}:
		 (bin_in < 63232) ? {13'b1111111100101, {0{1'b0}}, Out1}:
		 (bin_in < 63488) ? {13'b1111111100001, {0{1'b0}}, Out1}:
		 (bin_in < 63744) ? {13'b1111111011101, {0{1'b0}}, Out1}:
		 (bin_in < 64000) ? {13'b1111111011001, {0{1'b0}}, Out1}:
		 (bin_in < 64256) ? {13'b1111111010111, {0{1'b0}}, Out1}:
		 (bin_in < 64512) ? {13'b1111111011000, {0{1'b0}}, Out1}:
		 (bin_in < 64768) ? {13'b1111111011010, {0{1'b0}}, Out1}:
		 (bin_in < 65024) ? {13'b1111111100000, {0{1'b0}}, Out1}:
		 (bin_in < 65280) ? {13'b1111111101010, {0{1'b0}}, Out1}:
		 {13'b1111111110111, {0{1'b0}}, Out1};

endmodule

//=========

module SubFunction_1(input wire[254:0] In, output wire[6:0] Out);
assign Out[0] = In[123];
assign Out[1] = In[125];
assign Out[2] = In[127];
assign Out[3] = In[128];
assign Out[4] = In[130];
assign Out[5] = In[131];
assign Out[6] = In[133];
endmodule

//=========

module SubFunction_201(input wire[62:0] In, output wire[6:0] Out);
assign Out[0] = In[38];
assign Out[1] = In[38];
assign Out[2] = In[38];
assign Out[3] = In[38];
assign Out[4] = In[38];
assign Out[5] = In[38];
assign Out[6] = In[38];
endmodule

//=========

module SubFunction_203(input wire[126:0] In, output wire[6:0] Out);
assign Out[0] = 1'b1;
assign Out[1] = 1'b1;
assign Out[2] = 1'b1;
assign Out[3] = 1'b1;
assign Out[4] = 1'b1;
assign Out[5] = 1'b1;
assign Out[6] = 1'b1;
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
