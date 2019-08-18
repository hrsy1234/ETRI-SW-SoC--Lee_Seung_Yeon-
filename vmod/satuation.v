module satuation(input signed [18:0] oPsum,
		 output reg signed [15:0] iData);

always@(*)
begin
	if(oPsum<=-32768) iData=-32768;
	else if(oPsum>=32767) iData=32767;
	else iData=oPsum;
end
endmodule
