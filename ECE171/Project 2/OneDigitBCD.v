module OneDigitBCD(X, Y, Cin, Sum, Cout);

input [3:0] X;
input [3:0] Y;
input Cin;

output [3:0] Sum;

output Cout;

wire [3:0] X;
wire [3:0] Y; //from input to first adder
wire Cin; //from input to first adder
wire [3:0] S1;
wire C1; //'Sum' and 'Cout' from first adder
wire G; //output wire of GTN curcuit
wire [3:0] S2; //final sum from second adder
wire C2; //Cout from second adder, leads nowhere

Adder4Bit Add1(X, Y, Cin, S1, C1);
GreaterThanNine GTN({C1, S1}, G);
Adder4Bit Add2({1'b0, G, G, 1'b0}, S1, 1'b0, S2, C2);

assign #10 Sum = {G, S2};

assign #10 Cout = G;

endmodule