// Daniel Christiansen
// ECE 481
// Project 4: Part 1 - Clock Dividers

module Divider_TB ();

logic in_clk = 1'b0;
logic out_clk;

CD_8 DUT (.div_clk(out_clk), .ref_clk(in_clk));

always
begin
	#10 in_clk <= ~in_clk;
end

initial
begin
	#300; $stop;
end

endmodule

// Divide by 8, with 50% duty cycle
module CD_8 (output logic div_clk, input logic ref_clk);

logic [2:0] divider = 3'b000;

alway_ff @(posedge ref_clk)
	divider++;

assign div_clk = divider[2];

endmodule

// Divide by 5, with 50% duty cycle
module CD_5 ();

endmodule

// Divide by 3.5
module CD_3_5 ();

endmodule

// Divide by 5.5
module CD_5_5 ();

endmodule

