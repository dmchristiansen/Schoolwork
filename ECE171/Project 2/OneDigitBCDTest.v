module OneDigitBCDTest();

reg [3:0] X, Y;
reg Cin;

wire [3:0] Sum;
//wire [4:0] Sum;

wire Cout;

OneDigitBCD OD(X, Y, Cin, Sum, Cout);
//OneDigitBCD OD(X, Y, Cin, Sum);

initial
begin
for (X = 0; X <= 9; X = X + 1)
	for(Y = 0; Y <= 9; Y = Y + 1)
	begin
		Cin = 0;
		#100;
		Cin = 1;
		#100;
	end
end

endmodule