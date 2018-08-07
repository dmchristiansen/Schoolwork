module DisplayTest();

reg [3:0]IN;
wire B1, B2, B3, B4, B5, B6;

initial
begin

	for(IN = 0; IN < 10; IN=IN+1)
	begin
		#100;
	end

$finish();
end

endmodule

	
