`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 14.07.2022 01:05:32
// Design Name: 
// Module Name: wrapper
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module wrapper(input clk, input rst, input [4:0] in1, input [4:0] in2, output reg [4:0] out);

reg [4:0] in1_reg;
reg [4:0] in2_reg;
wire [4:0] out_net;
always @(posedge clk)
    begin
        if(rst)
            begin
                in1_reg<=5'd0;
                in2_reg<=5'd0;
					 out<=5'd0;
            end
        else
            begin
                in1_reg<=in1;
                in2_reg<=in2;
					 out<=out_net;
            end
    end

adder_struct add(in1_reg,in2_reg,out_net);

endmodule
