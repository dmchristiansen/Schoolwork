// Daniel Christiansen
// ECE 481
// Project 1: Part 2b - Priority Encoder

module PE #(parameter n = 1) (output reg [n-1:0] OUT, output reg VALID, input wire [(2**n)-1:0] IN);

task print;
$display("Instantiating PE module, n = %d\n", n); 
endtask

genvar i;

// if n = 1, define a 2-to-1 encoder
// if n > 1, recursively instantiate two modules, with n - 1

generate
	if(n == 1)
	begin
		assign OUT = IN[1];
		assign VALID = (|IN);	
	end else
	begin
		wire [n-2:0] OUT_HIGH, OUT_LOW;
		wire V_HIGH, V_LOW;

		PE #(n - 1) PE_HIGH(OUT_HIGH, V_HIGH, IN[((2**n)-1):((2**n)/2)]);
		PE #(n - 1) PE_LOW(OUT_LOW, V_LOW, IN[(((2**n)/2)-1):0]);

		assign VALID = V_HIGH | V_LOW;
		assign OUT[n-1] = V_HIGH;

		always_comb
		begin
		case (V_HIGH)
		1'b0: OUT[n-2:0] <= OUT_LOW;
		1'b1: OUT[n-2:0] <= OUT_HIGH;
		endcase
		end

	end
endgenerate	

endmodule


