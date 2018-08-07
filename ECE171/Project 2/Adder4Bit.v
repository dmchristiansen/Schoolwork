module Adder4Bit(X, Y, Cin, Sum, Cout);
input [3:0] X,Y;
input Cin;
output [3:0] Sum;
output Cout;
assign #10 {Cout,Sum} = X + Y + Cin;
endmodule

