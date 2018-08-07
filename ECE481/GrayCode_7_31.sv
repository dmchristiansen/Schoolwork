// Daniel Christiansen
// ECE 481
// Fall 2017
// Project 2: Task 1b - 7 bit, 31 length Gray Code Encoder / Decoder

// This module takes in a 7-bit value, in the sequence 0000000 through 0011110, and converts
// it to an eight bit Gray Code value.  The sequence of Gray Code values is iterated
// over once for every two iterations through the binary sequence.

// N = Binary input length, L = Length of binary sequence, from 0 to L-1
module GC_7_Encoder #(parameter N = 7, L = 31) (output reg [N:0] G, input logic [N-1:0] B, input logic CLK);

parameter C = 2 ** N;	// Max possible values for B
parameter K = C - L;	// Number of unused bit patterns for B
reg F = 1'b1;		// Flag bit.  Inverts every iteration through B
logic [N-1:0] M;	// Modified binary, as selected by F
logic [N:0] VSB;	// Virtual Space Binary

// Toggle F when B reaches end of sequence
always_ff @(posedge CLK)
begin
	if (B == L - 1) F <= ~F;
end

// Assemble VSB from F and B
always_comb
begin
	M = F ? B : (B + K);
	VSB = {F, M};
end

// Convert virtual binary count to Gray Code
always_ff @(posedge CLK)
begin
	G <= VSB ^ (VSB >> 1);
end

endmodule


// This module takes a 8-bit Gray Code value and converts it into a 7-bit
// binary value between 0000000 and 0011110.  Cycling through the valid
// Gray Code values once will cycle through the binary sequence twice.

module GC_7_Decoder #(parameter N = 7, L = 31) (output reg [N-1:0] B, input logic [N:0] G, input logic CLK);

parameter C = 2 ** N;	// Max possible values for B
parameter K = C - L;	// Number of unused bit patterns for B
logic [N-1:0] M;	// Modified binary, as selected by F
logic [N:0] VSB;	// Virtual Space Binary

// Convert Gray Code to Binary
genvar i;
generate
for (i = 0; i <= N; i++)
	always_comb
	begin
		VSB[i] = ^(G >> i);
	end
endgenerate

// If the MSB of VSB is low, subtract K 
always_ff @(posedge CLK)
begin
	B <= VSB[N] ? VSB[N-1:0] : (VSB[N-1:0] - K);
end

endmodule
