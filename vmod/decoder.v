module decoder(input iCLK, iRSTn,iWren,
		input [4:0] iAddr,
		input [7:0] iWeight,
		output reg [7:0] iW1,iW2,iW3,iW4,iW5,iW6,iW7,iW8,iW9,iW10,iW11,iW12,iW13,iW14,iW15,iW16,iW17,iW18,iW19,iW20,iW21,iW22,iW23,iW24,iW25);

wire [24:0] en;

//enable
assign en[0] = (iWren && iAddr==0)?1:0;
assign en[1] = (iWren && iAddr==1)?1:0;
assign en[2] = (iWren && iAddr==2)?1:0;
assign en[3] = (iWren && iAddr==3)?1:0;
assign en[4] = (iWren && iAddr==4)?1:0;
assign en[5] = (iWren && iAddr==5)?1:0;
assign en[6] = (iWren && iAddr==6)?1:0;
assign en[7] = (iWren && iAddr==7)?1:0;
assign en[8] = (iWren && iAddr==8)?1:0;
assign en[9] = (iWren && iAddr==9)?1:0;
assign en[10] = (iWren && iAddr==10)?1:0;
assign en[11] = (iWren && iAddr==11)?1:0;
assign en[12] = (iWren && iAddr==12)?1:0;
assign en[13] = (iWren && iAddr==13)?1:0;
assign en[14] = (iWren && iAddr==14)?1:0;
assign en[15] = (iWren && iAddr==15)?1:0;
assign en[16] = (iWren && iAddr==16)?1:0;
assign en[17] = (iWren && iAddr==17)?1:0;
assign en[18] = (iWren && iAddr==18)?1:0;
assign en[19] = (iWren && iAddr==19)?1:0;
assign en[20] = (iWren && iAddr==20)?1:0;
assign en[21] = (iWren && iAddr==21)?1:0;
assign en[22] = (iWren && iAddr==22)?1:0;
assign en[23] = (iWren && iAddr==23)?1:0;
assign en[24] = (iWren && iAddr==24)?1:0;
 
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW1<=0;
		else if (en[0]==1) iW1 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW2<=0;
		else if (en[1]==1) iW2 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW3<=0;
		else if (en[2]==1) iW3 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW4<=0;
		else if (en[3]==1) iW4<= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW5<=0;
		else if (en[4]==1) iW5 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW6<=0;
		else if (en[5]==1) iW6 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW7<=0;
		else if (en[6]==1) iW7 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW8<=0;
		else if (en[7]==1) iW8 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW9<=0;
		else if (en[8]==1) iW9 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW10<=0;
		else if (en[9]==1) iW10 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW11<=0;
		else if (en[10]==1) iW11 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW12<=0;
		else if (en[11]==1) iW12 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW13<=0;
		else if (en[12]==1) iW13 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW14<=0;
		else if (en[13]==1) iW14 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW15<=0;
		else if (en[14]==1) iW15 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW16<=0;
		else if (en[15]==1) iW16 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW17<=0;
		else if (en[16]==1) iW17 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW18<=0;
		else if (en[17]==1) iW18 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW19<=0;
		else if (en[18]==1) iW19 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW20<=0;
		else if (en[19]==1) iW20 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW21<=0;
		else if (en[20]==1) iW21 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW22<=0;
		else if (en[21]==1) iW22 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW23<=0;
		else if (en[22]==1) iW23 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW24<=0;
		else if (en[23]==1) iW24 <= iWeight;
	end
//Dff1
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) iW25<=0;
		else if (en[24]==1) iW25 <= iWeight;
	end


endmodule
