// Daniel Christiansen
// ECE 481
// Fall 2017
// Project 2: Task 1b - 7 bit, 31 length Gray Code Encoder - Test Bench

// This test bench cycles through a 7-bit binary count from
// 0000000 to 0011110 three times, to test that the Gray Code produced is accurate.

module GC_7_TB ();

parameter CLOCK_PERIOD = 20;
parameter N = 7;
parameter L = 31;

reg CLK;
reg [N-1:0] B_in = 0;
wire [N:0] G;
wire [N-1:0] B_out;

GC_7_Encoder DUT_E (.G(G), .B(B_in), .CLK(CLK));
GC_7_Decoder DUT_D (.B(B_out), .G(G), .CLK(CLK));

initial
begin
	CLK = 1'b0;
	forever #(CLOCK_PERIOD / 2) CLK = ~CLK;
end

always_ff @(negedge CLK)
	B_in <= (B_in < (L-1)) ? B_in + 1 : 0;

initial
begin
	#(CLOCK_PERIOD * L * 3) $stop;
end

endmodule
