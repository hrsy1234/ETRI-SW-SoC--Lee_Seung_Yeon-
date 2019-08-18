module control #(parameter STRIDE=1, xs=32, ws=5)
 		(input iValid,iCLK, iRSTn,
  		output reg oValid);

reg [4:0] j;
reg [4:0] i;
reg [4:0] col_next;
reg [4:0] row_next;

reg xValid;

always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn) xValid <=0;
	else xValid <= iValid;
	
end


//column index
always@(posedge iCLK, negedge iRSTn)
begin
	if(!iRSTn) j<=0;
		else if(xValid)
			begin
			if( j==xs-1) j<=0;
			else j<=j+1;
 			end
	
end

//row index
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) i<=0;
		else if(xValid)
		begin 
			if (j == xs-1) i<=i+1;
			else if( j==xs-1 && i==xs-1) i<=0;
		end
	end

//column next location
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) col_next <=  ws-1;
		else if(xValid)
			begin 
				if (i==row_next && j==col_next)
					begin
						if(j==xs-1) col_next <= ws-1;
						else col_next <= col_next + STRIDE;
					end
			end
	end

//row next location
always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) row_next<= ws-1;
		else if(xValid)
			begin
				if(i==row_next && j==xs-1)begin
					if(i==xs-1 && j==xs-1) row_next <= ws-1;
					else row_next <= row_next + STRIDE;
				end
			end
	end


//oValid
always@(posedge iCLK, negedge iRSTn)
begin
		if(!iRSTn) oValid<=0;
		else if(xValid && i==row_next && j==col_next) oValid <=1;
		else oValid <=0;
		
		
end

endmodule
