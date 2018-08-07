module DisplayTest();

reg [3:0]IN;
wire B1, B2, B3, B4, B5, B6;

BrailleDisplay Braille(IN, B1, B2, B3, B4, B5, B6);

initial
begin

	#100 IN = 0;
	#100 IN = 1;
	#100 IN = 2;
	#100 IN = 3;
	#100 IN = 4;
	#100 IN = 5;
	#100 IN = 6;
	#100 IN = 7;
	#100 IN = 8;
	#100 IN = 9;
	#100;

$finish();
end

endmodule

	

