`timescale 1ns / 1ps // Specify the time scale for the simulation (1ns time precision and 1ps time accuracy).

module adc_bram_module // Define the top-level module.
    #(
    parameter NUM_CHANNELS = 4 // Define a constant for the number of channels.
    )(
    input wire clk, // Clock signal, common to all channels.
    input wire rst_n, // Reset signal, common to all channels.
    input wire [NUM_CHANNELS-1:0] sda_n, // Array of differential data signals (negative) from the ADCs.
    input wire [NUM_CHANNELS-1:0] sda_p, // Array of differential data signals (positive) from the ADCs.
    output wire [NUM_CHANNELS-1:0] sck_p, // Array of differential clock signals (positive) to the ADCs.
    output wire [NUM_CHANNELS-1:0] sck_n, // Array of differential clock signals (negative) to the ADCs.
    output reg [NUM_CHANNELS-1:0] cnv_n, // Array of signals for controlling the ADC conversion process.
    output wire [15:0] data [NUM_CHANNELS-1:0], // 2D array of data from each ADC.
    output reg [NUM_CHANNELS-1:0] data_valid // Array of data valid signals from each ADC.
    );
    
    genvar i; // Generate variable used in generate loops.
    generate
        for (i = 0; i < NUM_CHANNELS; i = i + 1) begin : channel // Generate loop to create an instance of the adc_test module for each channel.
            // Instantiate each channel.
            adc_test #(1) adc ( // adc_test is a module you need to define elsewhere, representing your ADC's behavior.
                .clk(clk), // Connect the clock signal to the adc_test module.
                .rst_n(rst_n), // Connect the reset signal to the adc_test module.
                .ch1_sda_n(sda_n[i]), // Connect the negative data signal for channel i to the adc_test module.
                .ch1_sda_p(sda_p[i]), // Connect the positive data signal for channel i to the adc_test module.
                .sck_p(sck_p[i]), // Connect the positive clock signal for channel i to the adc_test module.
                .sck_n(sck_n[i]), // Connect the negative clock signal for channel i to the adc_test module.
                .cnv_n(cnv_n[i]), // Connect the conversion control signal for channel i to the adc_test module.
                .data(data[i]), // Connect the data signal for channel i to the adc_test module.
                .data_valid(data_valid[i]) // Connect the data valid signal for channel i to the adc_test module.
            );
        end
    endgenerate
endmodule
