`timescale 1ns / 1ps

////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer:
//
// Create Date:   14:35:58 08/29/2022
// Design Name:   wrapper
// Module Name:   H:/Siddhartha/Hardware Security Course/combinational_reg/test.v
// Project Name:  combinational_reg
// Target Device:  
// Tool versions:  
// Description: 
//
// Verilog Test Fixture created by ISE for module: wrapper
//
// Dependencies:
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
////////////////////////////////////////////////////////////////////////////////

module test;

	// Inputs
	reg clk;
	reg rst;
	reg [4:0] in1;
	reg [4:0] in2;

	// Outputs
	wire [4:0] out;

	// Instantiate the Unit Under Test (UUT)
	wrapper uut (
		.clk(clk), 
		.rst(rst), 
		.in1(in1), 
		.in2(in2), 
		.out(out)
	);

	initial begin
		// Initialize Inputs
		clk <= 0;
		rst <= 1'd1;
		in1 <= 0;
		in2 <= 0;
	end
	
	always #10 clk=~clk;
	
	initial begin
		#100 rst <= 1'd0;
		in1<=5'd3;
		in2<=5'd4;
	end
      
endmodule

