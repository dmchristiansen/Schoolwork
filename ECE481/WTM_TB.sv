// Daniel Christiansen
// ECE 481
// Project 1: Part 2a - Wallace Tree Multiplier Test Bench

module WTM_TB;

reg [7:0] A, B;
wire [15:0] product;

int i, j;

WTM DUT(product, A, B);

initial
begin
for (i = 0; i < 20; i++)
begin
	for (j = 0; j < 10; j++)
	begin
		#10;
		A <= i;
		B <= j;
	end
end
end
endmodule 
