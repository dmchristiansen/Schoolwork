module task2_1(out, data, sel);

output logic out; // output declarations

input logic data; // input declarations
input logic sel;

logic w1, w2, w3, w4, w5, w6;  // wire declarations

buf B_0(w1,data);	// buffer B_0	
buf B_1(w2,data);   // buffer B_1 

mux_task2 m1(w3,sel,w2,w1);    // mux declaration m1

buf B_2(w5,w3);    // buffer B_2
buf B_3(w6,w3);    // buffer B_3

not I_0(w4,sel);   // inverter I_0

mux_task2 m2(out,w4,w5,w6);    // mux declaration m2

endmodule