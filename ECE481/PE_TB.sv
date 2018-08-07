// Daniel Christiansen
// ECE 481
// Project 1: Part 2b - Priority Encoder Testbench

module PE_TB;

parameter n = 2;
reg [(2**n)-1:0] IN;
wire [n-1:0] OUT;
wire Valid;

PE #(n) DUT(OUT, Valid, IN);

int i;

initial
begin
	for (i = 0; i < 2**(2**n); i++)
	begin
		#10;
		IN <= i;
	end
end

endmodule
