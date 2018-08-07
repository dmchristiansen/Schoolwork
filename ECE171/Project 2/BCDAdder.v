module BCDAdder(X1, X0, Y1, Y0, Cin, Sum1, Sum0, Cout);
input [3:0] X1, X0, Y1, Y0;
input Cin;
output [3:0] Sum1, Sum0;
output Cout;
wire [3:0] X1, X0, Y1, Y0;
wire Cin; //from the Cin port to the first adder
wire [3:0] Sum1, Sum0;
wire Cout;

OneDigitBCD Adder0(X0, Y0, Cin, Sum0, Carry);
OneDigitBCD Adder1(X1, Y1, Carry, Sum1, Cout);

endmodule