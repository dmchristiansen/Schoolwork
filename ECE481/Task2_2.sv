module Task2_2( out, a, b, c, d );

output logic out; // output declarations

input logic a, b, c, d; // input declarations 

logic O1_o, A1_o, A2_o, A3_o, O2_o, I1_o;  // wire declarations 

// Logic

not I1(I1_o, b);
or  O1(O1_o, a, I1_o);
and A1(A1_o, c, I1_o);
and A2(A2_o, d, A1_o);
and A3(A3_o, O1_o, A2_o);
or  O2(O2_o, O1_o, A3_o);

assign out = O2_o;

endmodule