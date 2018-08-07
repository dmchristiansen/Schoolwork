// Daniel Christiansen
// ECE 481
// Fall 2017
// Project 2: Task 1a - 4 bit, 11 length Gray Code Encoder - Test Bench

// This test bench cycles through a 4-bit binary count from
// 0000 to 1010 three times, to test that the Gray Code produced is accurate.

module GC_4_TB ();

reg CLK;
reg [3:0] B = 4'b0000;
wire [4:0] G;

GC_4 DUT(.G(G), .B(B), .CLK(CLK));

initial
begin
	CLK = 1'b0;
	forever #10 CLK = ~CLK;
end

always_ff @(negedge CLK)
	B <= (B < 10) ? B + 1 : 4'b0000;

initial
begin
	#660 $stop;
end

endmodule
