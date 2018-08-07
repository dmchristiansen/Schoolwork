module mux_task2( out, sel, in0, in1 );

output logic out; //output declarations 

input logic in0, in1; // input declarations
input logic sel; //// Input declarations

assign out = sel ? in1 : in0;   // mux declaration 

endmodule


