// Daniel Christiansen
// ECE 481
// Project 3: Part 1 - 8 Bit Shift Register

module Shift_Register_8_Bit (output logic [7:0] data_out, input logic [7:0] data_in, input logic [2:0] OP, input logic CLK);

logic [7:0] value;

always_ff @(posedge CLK)
begin
	casez (OP)
		3'b000: value <= value;
		3'b001: value[6:0] <= value[7:1];
		3'b010: value <= {value[6:0], 1'b0};
		3'b011: value <= {value[0], value[7:1]};
		3'b100: value <= {value[6:0], value[7]};
		3'b101: value <= 8'b00000000;
		3'b110: value <= data_in;
		3'b111: value <= value;
	endcase
end

assign data_out = value;

endmodule
