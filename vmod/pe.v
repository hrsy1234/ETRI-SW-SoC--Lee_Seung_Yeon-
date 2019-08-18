module pe #(parameter BW1=16, BW2=16)
	  (input iCLK, iRSTn, 
	  input signed [7:0] iW,
	  input signed [7:0] iX,
	  input signed [BW1-1:0] iPsum,
	  output reg signed [BW2-1:0] oPsum);





wire signed [15:0] inn1;
wire signed [BW2-1:0] inn2;


assign inn1 = iW * iX;
assign inn2 = inn1 + iPsum;


always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn) oPsum <=0;
	else oPsum <= inn2;
end



endmodule















//reg signed [7:0] iX0;

/*always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn) iX0 <=0;
	else iX0 <= iX;
end
*/
