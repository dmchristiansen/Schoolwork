// Daniel Christiansen
// ECE481
// Fall 2017
// Project 2: Task 5 - Sequence Detector

// This module compares an input sequence to a sequence stored internally,
// and determined whether or not it matches.

module Sequence_Detector (output logic match, output logic mismatch, input logic in, input logic clk);

parameter logic [7:0] seq = 8'b0110_0110; // 66 in BCD

enum {SCAN, MATCH, MISMATCH} state, next;

logic [2:0] count = 3'b000;

// State transition logic
always_ff @(posedge clk)
begin: state_transition_logic
	if (next == SCAN)
	begin
		state <= next;
		count++;
	end else
	begin
		state <= next;
		count = 3'b000;
	end
end: state_transition_logic

// Next state logic
always_comb
begin: next_state_logic
	case (state)
	SCAN:
		if (in == seq[count])
			if (count == 3'b111) next = MATCH;
			else next = SCAN;
		else next = MISMATCH;
	MATCH:
		next = MATCH;
	MISMATCH: 
		if (in == seq[count]) next = SCAN;
		else next = MISMATCH;
	endcase
end: next_state_logic

// Output logic
always_comb
begin: output_logic
	case (state)
	SCAN: {match, mismatch} = 2'b00;
	MATCH: {match, mismatch} = 2'b10;
	MISMATCH: {match, mismatch} = 2'b01;
	endcase
end: output_logic

endmodule

// This module feeds several incorrect sequences to the detector, followed by the correct sequence

module Sequence_Detector_TB ();

logic clk = 1'b0;
logic in = 1'b0;
logic match, mismatch;

Sequence_Detector DUT (.match(match), .mismatch(mismatch), .in(in), .clk(clk));

always #10 clk <= ~clk;

initial
begin
	repeat (1) @(negedge clk); in = 1'b1;
	repeat (1) @(negedge clk); in = 1'b1;
	repeat (1) @(negedge clk); in = 1'b1;
	repeat (1) @(negedge clk); in = 1'b1;
	repeat (1) @(negedge clk); in = 1'b0;
	repeat (1) @(negedge clk); in = 1'b1;
	repeat (1) @(negedge clk); in = 1'b1;
	repeat (1) @(negedge clk); in = 1'b0;
	repeat (1) @(negedge clk); in = 1'b0;
	repeat (1) @(negedge clk); in = 1'b0;
	repeat (1) @(negedge clk); in = 1'b0;
	repeat (1) @(negedge clk); in = 1'b1;
	repeat (1) @(negedge clk); in = 1'b1;
	repeat (1) @(negedge clk); in = 1'b0;
	repeat (1) @(negedge clk); in = 1'b0;
	repeat (1) @(negedge clk); in = 1'b1;
	repeat (1) @(negedge clk); in = 1'b1;
	repeat (1) @(negedge clk); in = 1'b0;
	repeat (1) @(negedge clk); in = 1'b1;
	repeat (1) @(negedge clk); $stop;

end

endmodule

