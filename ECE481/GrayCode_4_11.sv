// Daniel Christiansen
// ECE 481
// Fall 2017
// Project 2: Task 1a - 4 bit, 11 length Gray Code Encoder

// This module takes in a 4-bit value, in the sequence 0000 through 1010, and converts
// it to a five bit Gracy Code value.  The sequence of Gray Code values is iterated
// over once for every two iterations through the binary sequence.

module GC_4 (output reg [4:0] G, input logic [3:0] B, input logic CLK);

reg F = 1'b1;		// Flag bit.  Inverts every iteration through B
logic [3:0] M;		// Modified binary, as selected by F
logic [4:0] VSB;	// Virtual Space Binary

// Toggle F when B reaches end of sequence
always_ff @(posedge CLK)
begin
	if (B == 4'b1010) F <= ~F;
end

// Assemble VSB from F and B
always_comb
begin
	M = F ? B : (B + 5);
	VSB = {F, M};
end

// Convert virtual binary count to Gray Code
always_ff @(posedge CLK)
begin
	G <= VSB ^ (VSB >> 1);
end

endmodule
