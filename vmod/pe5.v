module pe5 #(parameter BW1=16, BW2=19)
	  (input iCLK, iRSTn, 
	  input signed [7:0] iW1,iW2,iW3,iW4,iW5,
	  input signed [7:0] iX,
	  input signed [BW1-1:0] iPsum,
	  output signed [BW2-1:0] oPsum);


wire signed [16:0] b0;
wire signed [17:0] b1;
wire signed [17:0] b2;
wire signed [18:0] b3;


pe  #(16,17) p0(.iCLK(iCLK),.iRSTn(iRSTn),.iW(iW1),.iX(iX),.iPsum(iPsum),.oPsum(b0));
pe  #(17,18) p1(.iCLK(iCLK),.iRSTn(iRSTn),.iW(iW2),.iX(iX),.iPsum(b0),.oPsum(b1));
pe  #(18,18) p2(.iCLK(iCLK),.iRSTn(iRSTn),.iW(iW3),.iX(iX),.iPsum(b1),.oPsum(b2));
pe  #(18,19) p3(.iCLK(iCLK),.iRSTn(iRSTn),.iW(iW4),.iX(iX),.iPsum(b2),.oPsum(b3));
pe  #(19,19) p4(.iCLK(iCLK),.iRSTn(iRSTn),.iW(iW5),.iX(iX),.iPsum(b3),.oPsum(oPsum));


endmodule
