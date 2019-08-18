module convol1  #(parameter BW1=16, BW2=16)
	  	(input iCLK, iRSTn, 
	  	input signed [7:0] iW1,iW2,iW3,iW4,iW5,
	  	input signed [7:0] iX,
	  	input signed [BW1-1:0] iPsum,
	  	output signed [BW2-1:0] oPsum);


wire [18:0] a1;



pe5 #(16,19) hi1 (.iCLK(iCLK),.iRSTn(iRSTn),.iW1(iW1),.iW2(iW2),.iW3(iW3),.iW4(iW4),.iW5(iW5),.iX(iX),.iPsum(iPsum),.oPsum(a1));
satuation  s1 (.oPsum(a1),.iData(oPsum));

endmodule
