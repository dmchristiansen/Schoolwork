// Daniel Christiansen
// ECE 481
// Project 3: 8 bit Shift Register Testbench

module SR_8_TB ();
 
logic [7:0] data_in;
logic [7:0] data_out;
logic [2:0] OP;
logic CLK = 1'b0;

SR_8bit DUT (.data_out(data_out), .data_in(data_in), .OP(OP), .CLK(CLK));

always
begin
	#10 CLK <= ~CLK;
end

initial
begin
	//what?
	repeat (1) @(negedge CLK); OP = 3'b101; data_in = 8'b10101010;
	repeat (1) @(negedge CLK); OP = 3'b110;
	repeat (1) @(negedge CLK); OP = 3'b000;
	repeat (1) @(negedge CLK); OP = 3'b001;
	repeat (3) @(negedge CLK); OP = 3'b010;
	repeat (3) @(negedge CLK); OP = 3'b011;
	repeat (3) @(negedge CLK); OP = 3'b100;
	repeat (3) @(negedge CLK); OP = 3'b101;
	repeat (1) @(negedge CLK); $finish;
end

endmodule
