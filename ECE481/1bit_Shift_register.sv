// Daniel Christiansen
// ECE 481
// Project 3: Part 2 - 1 Bit Shift Register


// Model of an 8-bit Shift Register built from single bit-slice models
module SR_8bit (output logic [7:0] data_out, input logic [7:0] data_in, input logic [2:0] OP, input logic CLK);

SR_1bit SR_7 (.Q(data_out[7]), .data_in(data_in[7]), .a_right(data_out[6]), .a_left(data_out[7]), .s_right(data_out[6]), .s_left(data_out[0]), .OP(OP), .CLK(CLK));
SR_1bit SR_6 (.Q(data_out[6]), .data_in(data_in[6]), .a_right(data_out[5]), .a_left(data_out[7]), .s_right(data_out[5]), .s_left(data_out[7]), .OP(OP), .CLK(CLK));
SR_1bit SR_5 (.Q(data_out[5]), .data_in(data_in[5]), .a_right(data_out[4]), .a_left(data_out[6]), .s_right(data_out[4]), .s_left(data_out[6]), .OP(OP), .CLK(CLK));
SR_1bit SR_4 (.Q(data_out[4]), .data_in(data_in[4]), .a_right(data_out[3]), .a_left(data_out[5]), .s_right(data_out[3]), .s_left(data_out[5]), .OP(OP), .CLK(CLK));
SR_1bit SR_3 (.Q(data_out[3]), .data_in(data_in[3]), .a_right(data_out[2]), .a_left(data_out[4]), .s_right(data_out[2]), .s_left(data_out[4]), .OP(OP), .CLK(CLK));
SR_1bit SR_2 (.Q(data_out[2]), .data_in(data_in[2]), .a_right(data_out[1]), .a_left(data_out[3]), .s_right(data_out[1]), .s_left(data_out[3]), .OP(OP), .CLK(CLK));
SR_1bit SR_1 (.Q(data_out[1]), .data_in(data_in[1]), .a_right(data_out[0]), .a_left(data_out[2]), .s_right(data_out[0]), .s_left(data_out[2]), .OP(OP), .CLK(CLK));
SR_1bit SR_0 (.Q(data_out[0]), .data_in(data_in[0]), .a_right(1'b0), .a_left(data_out[1]), .s_right(data_out[7]), .s_left(data_out[1]), .OP(OP), .CLK(CLK));

endmodule

// Model of a single bit slice Shift Register
module SR_1bit 
	(output logic Q, 
	input logic data_in,
	input logic a_right,
	input logic a_left,
	input logic s_right,
	input logic s_left,
	input logic [2:0] OP, 
	input logic CLK);

logic D;

always_comb
begin
	casez (OP)
		3'b000: D = Q;
		3'b001: D = a_left;
		3'b010: D = a_right;
		3'b011: D = s_left;
		3'b100: D = s_right;
		3'b101: D = 1'b0;
		3'b110: D = data_in;
		3'b111: D = Q;
	endcase
end

always_ff @(posedge CLK)
	Q <= D;

endmodule
