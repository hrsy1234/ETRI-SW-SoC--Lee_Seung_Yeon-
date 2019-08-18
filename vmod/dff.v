module dff #(parameter N = 16)
	      (input iCLK, iRSTn,
	      input [N-1:0] iD, 
	      output reg [N-1:0] oQ);

always@(posedge iCLK, negedge iRSTn)
	begin
		if(!iRSTn) oQ <=0;
		else oQ <= iD;
	end

endmodule
