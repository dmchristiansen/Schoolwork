module GreaterThanNineTest();

reg [4:0] IN;
wire OUT;

GreaterThanNine GTN(IN, OUT);

initial
begin
for (IN = 0; IN < 18; IN = IN + 1)
begin
	#100;
end
end

endmodule