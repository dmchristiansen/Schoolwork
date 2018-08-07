// Daniel Christiansen
// ECE 585
// HW #1
// Train Control Logic - Test Bench

module TestBench;
reg Clock, Reset;
reg [1:5] S;
wire [1:0] DA, DB;
wire [1:3] SW;

parameter CLOCK_PERIOD = 20;

TrainControl TCFSM(Clock, Reset, S, DA, DB, SW);

initial
begin
	$display("Time	Clock	Reset	S	DA	DB	SW\n");
	$monitor($time, "%b	%b	%b	%b	%b	%b", Clock, Reset, S, DA, DB, SW);
end

initial
begin
	Clock = 1'b0;
	forever #10 Clock = ~Clock;
end

initial
begin
	repeat (2) @(negedge Clock); Reset = 1'b1;
	repeat (1) @(negedge Clock); Reset = 1'b0;
end

initial
begin
	// Train A passing through shared track, B on its own track
	repeat (5) @(negedge Clock); S = 5'b00000;
	repeat (2) @(negedge Clock); S = 5'b10000;
	repeat (5) @(negedge Clock); S = 5'b00000;
	repeat (2) @(negedge Clock); S = 5'b00010;

	// Train B passing through shared track, A on its own track
	repeat (5) @(negedge Clock); S = 5'b00000;
	repeat (2) @(negedge Clock); S = 5'b01000;
	repeat (5) @(negedge Clock); S = 5'b00000;
	repeat (2) @(negedge Clock); S = 5'b00100;

	// Train A passing through shared track, B trying to pass
	repeat (5) @(negedge Clock); S = 5'b00000;
	repeat (2) @(negedge Clock); S = 5'b10000;
	repeat (2) @(negedge Clock); S = 5'b00000;
	repeat (3) @(negedge Clock); S = 5'b01000;
	repeat (2) @(negedge Clock); S = 5'b01010;
	repeat (2) @(negedge Clock); S = 5'b00000;
	repeat (2) @(negedge Clock); S = 5'b00100;

	// Train B passing through shared track, A trying to pass
	repeat (5) @(negedge Clock); S = 5'b00000;
	repeat (2) @(negedge Clock); S = 5'b01000;
	repeat (2) @(negedge Clock); S = 5'b00000;
	repeat (3) @(negedge Clock); S = 5'b10000;
	repeat (2) @(negedge Clock); S = 5'b10100;
	repeat (2) @(negedge Clock); S = 5'b00000;
	repeat (2) @(negedge Clock); S = 5'b00010;	

	// Trains A and B arriving at the shared track simultaneously
	repeat (5) @(negedge Clock); S = 5'b00000;
	repeat (2) @(negedge Clock); S = 5'b11000;
	repeat (5) @(negedge Clock); S = 5'b01000;
	repeat (2) @(negedge Clock); S = 5'b01010;
	repeat (5) @(negedge Clock); S = 5'b00000;
	repeat (5) @(negedge Clock); S = 5'b00100;

	// Nonsense sensor readings
	repeat (2) @(negedge Clock); S = 5'b10010;
	repeat (1) @(negedge Clock); S = 5'b00000;
	repeat (2) @(negedge Clock); Reset = 1'b1;
	repeat (1) @(negedge Clock); Reset = 1'b0;
	repeat (2) @(negedge Clock); S = 5'b01100;
	repeat (1) @(negedge Clock); S = 5'b00000;
	repeat (2) @(negedge Clock); Reset = 1'b1;
	repeat (5) @(negedge Clock); Reset = 1'b0;
	repeat (2) @(negedge Clock); S = 5'b00001;
	repeat (5) @(negedge Clock); S = 5'b00000;

	$stop;
end


endmodule
