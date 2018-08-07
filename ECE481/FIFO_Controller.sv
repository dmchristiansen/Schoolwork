// Daniel Christiansen
// ECE 481
// Fall 02017
// Project 2: Task 2 - FIFO Controller

module FIFO_Controller 
	(output reg wr_en = 1'b0,
	output reg rd_en = 1'b0,
	output reg [4:0] wr_ptr = 5'b00000,
	output reg [4:0] rd_ptr = 5'b00000,
	output logic emp,
	output logic full,
	input logic wr,
	input logic rd,
	input logic rst,
	input logic clk);

// Pointers retain an extra bit to track full/empty states
reg [5:0] write = 6'b000000;
reg [5:0] read = 6'b000000;

always_ff @(posedge clk, posedge rst)
begin
	if (rst)
	begin
		wr_en <= 1'b0;
		rd_en <= 1'b0;
		write <= 6'b000000;
		read <= 6'b000000;
		wr_ptr <= 5'b00000;
		rd_ptr <= 5'b00000;
	end
	else
	begin
		// write logic
		if (wr & !full)
		begin
			wr_en <= 1'b1;
			wr_ptr <= write[4:0];
			write <= write + 1;
		end else
			wr_en <= 1'b0;
		// read logic
		if (rd & !emp)
		begin
			rd_en <= 1'b1;
			rd_ptr <= read[4:0];
			read <= read + 1;
		end else
			rd_en <= 1'b0;
	end
end

// FIFO is full if LSBs are the same and MSB is opposite
assign full = (write[5] ^ read[5]) & (~|(write[4:0] ^ read[4:0]));
// FIFO is empty if all bits are the same
assign emp = (~|(write ^ read));

endmodule


