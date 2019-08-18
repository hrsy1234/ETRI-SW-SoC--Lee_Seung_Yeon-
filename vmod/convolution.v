module convolution#(parameter BW1=16, BW2=16,STRIDE=1, xs=32, ws=5)
	  	(input iCLK, iRSTn, iWren,
		input [4:0] iADDR,
		input [7:0] iWeight,
	  	 input signed [7:0] iX,
		input iValid,
	  	 output signed [BW2-1:0] oPsum,
		output oValid);



wire signed [7:0] iW1,iW2,iW3,iW4,iW5,iW6,iW7,iW8,iW9,iW10,iW11,iW12,iW13,iW14,iW15,iW16,iW17,iW18,iW19,iW20,iW21,iW22,iW23,iW24,iW25;
reg signed [7:0] iX0;

wire signed[BW2-1:0] sat1;
wire signed[BW2-1:0] d1;
wire signed[BW2-1:0] sat2;
wire signed[BW2-1:0] d2;
wire signed[BW2-1:0] sat3;
wire signed[BW2-1:0] d3;
wire signed[BW2-1:0] sat4;
wire signed[BW2-1:0] d4;

always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn) iX0 <=0;
	else iX0 <= iX;
end

decoder dec1(.iCLK(iCLK),.iRSTn(iRSTn),.iWren(iWren),.iAddr(iADDR),.iWeight(iWeight),.iW1(iW1),.iW2(iW2),.iW3(iW3),.iW4(iW4),.iW5(iW5),.iW6(iW6),.iW7(iW7),.iW8(iW8),.iW9(iW9),.iW10(iW10),.iW11(iW11),.iW12(iW12),.iW13(iW13),.iW14(iW14),.iW15(iW15),.iW16(iW16),.iW17(iW17),.iW18(iW18),.iW19(iW19),.iW20(iW20),.iW21(iW21),.iW22(iW22),.iW23(iW23),.iW24(iW24),.iW25(iW25));

convol1  c1(.iCLK(iCLK),.iRSTn(iRSTn),.iW1(iW1),.iW2(iW2),.iW3(iW3),.iW4(iW4),.iW5(iW5),.iX(iX0),.iPsum(16'd0),.oPsum(sat1));
line_buf line1(.iCLK(iCLK),.iRSTn(iRSTn),.iData(sat1),.oData(d1));


convol1  c2(.iCLK(iCLK),.iRSTn(iRSTn),.iW1(iW6),.iW2(iW7),.iW3(iW8),.iW4(iW9),.iW5(iW10),.iX(iX0),.iPsum(d1),.oPsum(sat2));
line_buf line2(.iCLK(iCLK),.iRSTn(iRSTn),.iData(sat2),.oData(d2));


convol1  c3(.iCLK(iCLK),.iRSTn(iRSTn),.iW1(iW11),.iW2(iW12),.iW3(iW13),.iW4(iW14),.iW5(iW15),.iX(iX0),.iPsum(d2),.oPsum(sat3));
line_buf line3(.iCLK(iCLK),.iRSTn(iRSTn),.iData(sat3),.oData(d3));

convol1  c4(.iCLK(iCLK),.iRSTn(iRSTn),.iW1(iW16),.iW2(iW17),.iW3(iW18),.iW4(iW19),.iW5(iW20),.iX(iX0),.iPsum(d3),.oPsum(sat4));
line_buf line4(.iCLK(iCLK),.iRSTn(iRSTn),.iData(sat4),.oData(d4));

convol1  c5(.iCLK(iCLK),.iRSTn(iRSTn),.iW1(iW21),.iW2(iW22),.iW3(iW23),.iW4(iW24),.iW5(iW25),.iX(iX0),.iPsum(d4),.oPsum(oPsum));

//////////////////////////////////////////

control cc1 (.iCLK(iCLK),.iRSTn(iRSTn),.iValid(iValid),.oValid(oValid));

endmodule
