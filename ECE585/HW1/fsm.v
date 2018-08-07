// Daniel Christiansen
// ECE 585
// HW #1
// Train Control Logic

module TrainControl(Clock, Reset, S, DA, DB, SW);
input Clock, Reset;
input [1:5] S;
output [1:0] DA, DB;
output [1:3] SW;
reg [1:0] DA, DB;
reg [1:3] SW;

// defines values for one-hot FSM
parameter
	STATE1	= 6'b000001, // A & B on their own tracks
	STATE2	= 6'b000010, // A on shared track, B on own track
	STATE3	= 6'b000100, // A on shared track, B waiting
	STATE4	= 6'b001000, // A on own track, B on shared track
	STATE5	= 6'b010000, // A waiting, B on shared track
	STATE6	= 6'b100000; // Error

reg [5:0] State, NextState;

// Update State
always @(posedge Clock)
begin
	if (Reset)
		State <= STATE1; // assume that the reset button is magic
	else
		State <= NextState;
end

// Next State logic
always @(*)
begin
	case (State)
	STATE1: // Trains A & B are in their own sections of track
	begin
		if (S[5] || S[1] && S[4] || S[2] && S[3])
									NextState = STATE6;
		else if (S[1] && ~S[2])		NextState = STATE2;
		else if (S[1] && S[2])		NextState = STATE3;
		else if (~S[1] && S[2])		NextState = STATE4;
		else 						NextState = STATE1;
	end
	STATE2: // Train A is crossing the shared track, B is in its own section
	begin
		if (S[5] || S[1] && S[4] || S[2] && S[3])
									NextState = STATE6;
		else if	(~S[2] && S[4])		NextState = STATE1;
		else if (S[1] && ~S[2])		NextState = STATE2;
		else if (S[2])				NextState = STATE3;
		else if (S[2] && S[4])		NextState = STATE4;
	end
	STATE3: // Train A is crossing the shared track, B is waiting
	begin
		if (S[5] || S[1] && S[4] || S[2] && S[3] || ~S[2] && ~S[4])
									NextState = STATE6;
		else if (~S[2] && S[4])		NextState = STATE1;
		else if (S[2] && ~S[4])		NextState = STATE3;
		else if (S[2] && S[4])		NextState = STATE4;
	end
	STATE4: // Train A is in its own section, B is crossing shared track
	begin
		if (S[5] || S[1] && S[4] || S[2] && S[3])
									NextState = STATE6;
		else if (~S[1] && S[3])		NextState = STATE1;
		else if (S[1] && S[3])		NextState = STATE2;
		else if (~S[1] && ~S[3])	NextState = STATE4;
		else if (S[1] && ~S[3])		NextState = STATE5;

	end
	STATE5: // Train A is waiting, B is crossing shared track
	begin
		if (S[5] || S[1] && S[4] || S[2] && S[3] || ~S[1] && ~S[3])
									NextState = STATE6;
		else if (~S[1] && S[3])		NextState = STATE1;
		else if (S[1] && S[3])		NextState = STATE2;
		else if (S[1] && ~S[3])		NextState = STATE5;
	end
	STATE6: // Error state
	begin
		NextState = STATE6;
	end
	endcase
end

// Output values
 always @(State)
begin
	case (State)
	STATE1:
	begin
		DA <= 2'b01;
		DB <= 2'b01;
		SW <= 3'b000;
	end
	STATE2:
	begin
		DA <= 2'b01;
		DB <= 2'b01;
		SW <= 3'b000;
	end
	STATE3:
	begin
		DA <= 2'b01;
		DB <= 2'b00;
		SW <= 3'b000;
	end
	STATE4:
	begin
		DA <= 2'b01;
		DB <= 2'b01;
		SW <= 3'b110;
	end
	STATE5:
	begin
		DA <= 2'b00;
		DB <= 2'b01;
		SW <= 3'b110;
	end
	STATE6:
	begin
		DA <= 2'b00;
		DB <= 2'b00;
		SW <= 3'b110;
	end
	endcase
end

endmodule
