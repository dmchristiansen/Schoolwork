
// Daniel Christiansen
// ECE 481
// Fall 2017
// Project 2: Task 3 - Traffic Light Controller Test Bench

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

