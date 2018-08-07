module BrailleDisplay(IN, B1, B2, B3, B4, B5, B6);
input [3:0]IN; //4 digit BCD
output B1, B2, B3, B4, B5, B6;

wire P1, P2, P3, P4, P5, P6, P7, P8, P9, P10, P11, P12, P13; //wires from AND to OR
wire IN3B, IN2B, IN1B, IN0B; //inputs through inverters


not #(17) //inverters
	U1a(IN3B, IN[3]),
	U1b(IN2B, IN[2]),
	U1c(IN1B, IN[1]),
	U1d(IN0B, IN[0]);

and #(28)
	U2a(P1, IN[3], IN1B, IN0B), 	//P1 = 3*~1*~0
	U2b(P2, IN3B, IN[0]);        	//P2 = ~3*0

and #(25)
	U3a(P3, IN2B, IN0B),        	//P3 = ~2*~0
	U3b(P4, IN[2], IN[1]),      	//P4 = 2*1
	U3c(P5, IN[3], IN[0]);      	//P5 = 3*0

and #(28)
	U4a(P6, IN3B, IN1B, IN0B),  	//P6 = ~3*~1*~0
	U4b(P7, IN[1], IN[0]);      	//P7 = 1*0

and #(25)
	U5a(P8, IN1B, IN0B),        	//P8 = ~1*~0
	U5b(P9, IN[2], IN[0]);      	//P9 = 2*0

or #(24)
	U6a(P10, P1, IN[2]),  		//B1 = (3*~1*~0)+(~3*0)+2+1
	U6b(P11, IN[1], P2),		//Using two 2-in OR gates into another
	U6c(B1, P10, P11);           	//OR gate to simulate a 4-in OR gate.

or #(24)
	U7a(B2, P3, P4, P5);		//B2 = (~2*~0)+(2*1)+3
	
or #(24)
	U8a(P12, P4, P5),        	//B4 = (~3*~1*~0)+(2*1)+(3*0)+(1*0)
	U8b(P13, P6, P7),		//Using two 2-in OR gates into another
	U8d(B4, P12, P13);		//OR gate to simulate a 4-in OR gate.

or #(24)
	U8c(B5, P8, P9);                //B5 = (~1*~0)+(2*0)

assign #(10) B3 = 0;

assign #(10) B6 = 0;

endmodule
