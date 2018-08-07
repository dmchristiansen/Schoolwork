module GoodBCD(X1, X0, Y1, Y0, Cin, Sum1, Sum0, Cout);
input [3:0] X1, X0, Y1, Y0;
input Cin;
output [3:0] Sum1, Sum0;
output Cout;
reg [3:0] Sum1, Sum0;
reg Cout;
reg C1, C0;

always @(X1,X0,Y1,Y0,Cin)
  begin
  {C0,Sum0} = X0 + Y0 + Cin;
  if ({C0,Sum0} > 9)
    {C0, Sum0} = {C0, Sum0} + 6;
  {C1,Sum1} = X1 + Y1 + C0;
  if ({C1, Sum1} > 9)
    {C1,Sum1} = {C1,Sum1} + 6;
  Cout = C1;
  end
endmodule





module TestBCDAdder;
reg [3:0] X1, X0, Y1, Y0;
reg Cin;
wire [3:0] Sum1, Sum0;
wire Cout;

wire [3:0] GoodSum1, GoodSum0;
wire GoodCout;

reg Errors = 0;

BCDAdder B0(X1, X0, Y1, Y0, Cin, Sum1, Sum0, Cout);
GoodBCD B1(X1, X0, Y1, Y0, Cin, GoodSum1, GoodSum0, GoodCout);

initial
begin
for (X1 = 0; X1 <= 9; X1 = X1 + 1)
 for (X0 = 0; X0 <= 9; X0 = X0 + 1)
   for (Y1 = 0; Y1 <= 9; Y1 = Y1 + 1)
     for (Y0 = 0; Y0 <= 9; Y0 = Y0 + 1)
       begin
       Cin = 0;
       repeat (2)
         begin
         #100
         if ({Cout,Sum1,Sum0} !== {GoodCout,GoodSum1,GoodSum0})
           begin
           Errors = 1;
           $display("*** Error: Adding %d%d + %d%d + %b yielded %b %d%d, expected %b %d%d",X1,X0,Y1,Y0,Cin,Cout,Sum1,Sum0,GoodCout,GoodSum1,GoodSum0);
           end
         Cin = ~Cin;
         end
      end
if (Errors == 0)
  $display("*** Congratulations: no errors ***");
else
  $display("*** Errors occurred ***");
end
endmodule