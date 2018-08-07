module BrailleDisplay(IN, B1, B2, B3, B4, B5, B6);
input [3:0] IN; //4 digit BCD
output B1, B2, B3, B4, B5, B6;

assign #10 B1 = IN[3] & ~IN[1] & ~IN[0]
		| ~IN[3] & IN[0]
		| IN[2]
		| IN[1];

assign #10 B2 = ~IN[2] & ~IN[0]
		| IN[2] & IN[1]
		| IN[3] & IN[0];

assign #10 B3 = 0;

assign #10 B4 = ~IN[3] & ~IN[1] & ~IN[0]
		| IN[2] & IN[1]
		| IN[3] & IN[0]
		| IN[1] & IN[0];

assign #10 B5 = ~IN[1] & ~IN[0]
		| IN[2] & IN[0];

assign #10 B6 = 0;

endmodule
