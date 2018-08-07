module GreaterThanNine(IN, OUT);
input [4:0] IN;
output OUT;

assign #10 OUT = IN[4]
		| IN[3] & IN[2]
		| IN[3] & IN[1];

endmodule