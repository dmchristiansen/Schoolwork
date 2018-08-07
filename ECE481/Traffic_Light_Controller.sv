// Daniel Christiansen
// ECE 481
// Fall 2017
// Project 2: Task 3 - Traffic Light Controller


typedef enum {	OFF, // power off
		RED, // red state
		YELLOW, // yellow state
		GREEN,// green state
		PRE_GREEN} // state before green
lights_t;

module TLC_TB ();

timeunit 1ns;
timeprecision 100ps;


reg clk = 1'b0;
logic reset_n = 1'b1;
logic emgcy_sensor = 1'b0;
logic ew_sensor = 1'b0;
lights_t ns_light, ew_light;

trafficlight DUT 
	(.ns_light(ns_light), 
	.ew_light(ew_light), 
	.ew_sensor(ew_sensor),
	.emgcy_sensor(emgcy_sensor),
	.reset_n(reset_n),
	.clk(clk));


always
begin
	#10 clk <= ~clk;
end

initial
begin
	// Reset to initial state
	repeat (1) @(negedge clk); reset_n = 1'b0;
	repeat (2) @(negedge clk); reset_n = 1'b1;
	// Allow light to sit for several cycles
	repeat (4) @(negedge clk);
	// Test ns emergency sensor response
	emgcy_sensor = 1'b1;
	repeat (1) @(negedge clk); emgcy_sensor = 1'b0;
	// Allow lights to return to normal
	repeat (4) @(negedge clk);
	// Test ew sensor
	ew_sensor = 1'b1;
	repeat (2) @(negedge clk); ew_sensor = 1'b0;
	// Allow lights to return to normal
	repeat (4) @(negedge clk);
	// Test a lot of people at ew light
	ew_sensor = 1'b1;
	repeat (8) @(negedge clk); ew_sensor = 1'b0;
	repeat (2) @(negedge clk); $stop;
end

endmodule

module trafficlight (
	output lights_t ns_light, // North/South light status, Main road
	output lights_t ew_light, // East/West light status
	input ew_sensor, // East/West sensor for new car
	input emgcy_sensor, // emergency sensor
	input reset_n, // synchronous reset
	input clk // master clock
);

timeunit 1ns;
timeprecision 100ps;
parameter FAIL = 1'b0;

lights_t ns_next, ew_next;

logic [1:0] ns_green_timer; // timer for NS light in GREEN
logic [1:0] ew_green_timer; // timer for EW light in GREEN

// -------------
// N-S FSM logic
// -------------

// Timer logic
always_ff @(posedge clk, negedge reset_n)
begin: ns_timer_logic
	if (!reset_n | (ns_next == YELLOW)) ns_green_timer = 2'b00;
	else if (clk) 
		if (ns_green_timer == 2'b11) ns_green_timer = 2'b11;
		else ns_green_timer++;
end: ns_timer_logic

// State transition logic
always_ff @(posedge clk, negedge reset_n)
begin: ns_state_transition_logic
	if(!reset_n)
		ns_light <= GREEN;
	else
		ns_light <= ns_next;
end: ns_state_transition_logic

// Next state logic
always_comb
begin: ns_next_state_logic
	case (ns_light)
		OFF: ns_next = OFF;
		RED:
			if (ns_green_timer == 2'b11) ns_next = GREEN;
			else ns_next = RED;
		YELLOW: ns_next = RED;
		GREEN:
			if (emgcy_sensor | (ew_sensor & ns_green_timer == 2'b11))
				ns_next = YELLOW;
			else ns_next = GREEN;
		PRE_GREEN: ns_next = PRE_GREEN; // This shouldn't happen
	endcase
end: ns_next_state_logic

// -------------
// E-W FSM Logic
// -------------

// Timer logic
always_ff @(posedge clk, negedge reset_n)
begin: ew_timer_logic
	if (!reset_n | (ew_next == RED)) ew_green_timer = 2'b00;
	else 
		if (ew_green_timer == 2'b11) ew_green_timer = 2'b11;
		else ew_green_timer++;
end: ew_timer_logic

// State transition logic
always_ff @(posedge clk, negedge reset_n)
begin: ew_state_transition_logic
	if(!reset_n)
		ew_light <= RED;
	else
		ew_light <= ew_next;
end: ew_state_transition_logic

// Next state logic
always_comb
begin: ew_next_state_logic
	case (ew_light)
		OFF: ew_next <= OFF;
		RED:
			if (ew_sensor & ns_green_timer == 2'b11)
				ew_next = PRE_GREEN;
			else ew_next = RED;
		YELLOW: ew_next = RED;
		GREEN:
			if (emgcy_sensor | ew_green_timer == 2'b11)
				ew_next = YELLOW;
			else ew_next = GREEN;
		PRE_GREEN: ew_next = GREEN;
	endcase
end: ew_next_state_logic

endmodule
