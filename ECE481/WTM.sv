// Daniel Christiansen
// ECE 481
// Project 1: Part 2a - Wallace Tree Multiplier

// Module to implement an 8-bit WTM
module WTM(output reg[15:0] product, input wire[7:0] A, input wire[7:0] B);

wire [7:0][7:0] pp; // matrix of partial products

// Create partial products
genvar i, j;

for(i = 0; i < 8; i++)
begin
	for(j = 0; j < 8; j++)
	begin
		assign pp[i][j] = A[i] & B[j];
	end
end


assign product = {8'b00000000, pp[0]}
		+{7'b0000000, pp[1], 1'b0}
		+{6'b000000, pp[2], 2'b00}
		+{5'b00000, pp[3], 3'b000}
		+{4'b0000, pp[4], 4'b0000}
		+{3'b000, pp[5], 5'b00000}
		+{2'b00, pp[6], 6'b000000}
		+{1'b0, pp[7], 7'b0000000};

endmodule

