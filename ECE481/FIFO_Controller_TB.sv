// Daniel Christiansen
// ECE 481
// Fall 2017
// Project 2: Task 2 - FIFO Controller Test Bench

module FIFO_Controller_TB ();

reg clk = 1'b0;
reg rd = 1'b0;
reg wr = 1'b0;
reg rst = 1'b0;

wire wr_en, rd_en, emp, full;
wire [4:0] wr_ptr, rd_ptr;

FIFO_Controller DUT (.wr_en(wr_en), .rd_en(rd_en), .rd_ptr(rd_ptr), .wr_ptr(wr_ptr), .emp(emp), .full(full),
	.wr(wr), .rd(rd), .rst(rst), .clk(clk));

always
begin
	#10 clk <= ~clk;
end

initial
begin
	// reset controller
	repeat (1) @(negedge clk); rst = 1'b1;
	repeat (1) @(negedge clk); rst = 1'b0;
	// test read-when-empty rejection
	repeat (1) @(negedge clk); rd = 1'b1;
	repeat (1) @(negedge clk);
	// read 3 times, write 4 times
	wr = 1'b1;
	rd = 1'b1;
	repeat (4) @(negedge clk);
	// write 31 times (fill FIFO)
	wr = 1'b1;
	rd = 1'b0;
	repeat (31) @(negedge clk);
	// test write-when-full rejection
	 wr = 1'b1;
	repeat (1) @(negedge clk);
	// read 32 times (empty FIFO)
	wr = 1'b0;
	rd = 1'b1;
	repeat (32) @(negedge clk);
	// test read-when-empty rejection & empty signal
	rd = 1'b1;
	repeat (1) @(negedge clk);
	// issue no commands
	wr = 1'b0;
	rd = 1'b0;
	repeat (4) @(negedge clk);
	// reset
	rst = 1'b1;
	repeat (1) @(negedge clk);
	rst = 1'b0;

	$stop;
	
end


endmodule

