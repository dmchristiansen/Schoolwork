// Daniel Christiansen
// ECE 481
// Fall 2017
// Project 2: Task 4 - Preamble Generator

// This module repeats the pattern '10101010' for as long as the start signal is applied.
// If the signal goes low during the sequence, it resets

module Preamble (output logic data_out, input logic start, input logic clk);

typedef enum {RESET, ZERO, ONE} state_t;

state_t state, next;

// State transition logic
always_ff @(posedge clk)
begin: transition_logic
	if(!start) state <= RESET;
	else state <= next;
end: transition_logic

// Next state logic
always_comb
begin: next_state_logic
	case (state)
	RESET: next = ONE;
	ZERO: next = ONE;
	ONE: next = ZERO;
	endcase
end: next_state_logic

// Output logic
always_comb
begin: output_logic
	case (state)
	RESET: data_out = 1'bx;
	ZERO: data_out = 1'b0;
	ONE: data_out = 1'b1;
	endcase
end: output_logic

endmodule

// This testbench applies a sequence of start values, interrupting the pattern several times

module Preamble_Generator_TB ();

reg clk = 1'b0;
logic start = 1'b0;
logic data_out;

Preamble DUT (.data_out(data_out), .start(start), .clk(clk));

always #10 clk <= ~clk;

initial
begin
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b0;
	repeat (1) @(negedge clk); start = 1'b0;
	repeat (1) @(negedge clk); start = 1'b0;
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b1;
	repeat (1) @(negedge clk); start = 1'b0;
	repeat (1) @(negedge clk); start = 1'b0;
	repeat (1) @(negedge clk); $stop;
end

endmodule

