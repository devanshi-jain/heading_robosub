module TDOA_Calculation (
  input wire clk,
  input wire [3:0] hydrophone_data[4], // 4 hydrophones
  output wire [3:0] tdoa_result[4]
);

  reg [3:0] time_delay;
  reg [3:0] distance;

  // Constants
  localparam SPEED_OF_SOUND_WATER = 1500; // Speed of sound in water in meters per second

  always @(posedge clk) begin
    // Calculate time differences
    time_delay[0] <= hydrophone_data[1] - hydrophone_data[0]; // Example for 2 hydrophones
    time_delay[1] <= hydrophone_data[2] - hydrophone_data[1]; // Example for 3 hydrophones //check
    time_delay[2] <= hydrophone_data[3] - hydrophone_data[2]; // Example for 4 hydrophones //check

    // Convert time differences to distances
    distance[0] <= time_delay[0] * SPEED_OF_SOUND_WATER;
    distance[1] <= time_delay[1] * SPEED_OF_SOUND_WATER;
    distance[2] <= time_delay[2] * SPEED_OF_SOUND_WATER;
    
    // Store the TDOA result
    tdoa_result[0] <= distance[0];
    tdoa_result[1] <= distance[1];
    tdoa_result[2] <= distance[2];  
  end
endmodule
