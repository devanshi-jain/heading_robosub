<!-- Overview of the modules and their relationships in the context of implementing the TDOA calculation and hydrophone data processing on an FPGA:

Top-Level Module:

This module acts as the entry point for your design and coordinates the interactions between different modules.
It instantiates and connects the various components of your design, including the ADC interface, TDOA calculation module, data processing modules, and AUV control modules.
ADC Interface Module:

This module handles the communication with the ADC modules connected to the hydrophones.
It manages the configuration, control, and data acquisition from the ADCs.
It interfaces with the hydrophone data processing modules to provide the acquired data for further processing.

TDOA Calculation Module:

This module implements the TDOA calculation algorithm using the acquired time-stamped data from the hydrophones.
It calculates the time differences between pairs of hydrophones and converts them to distances using the speed of sound in water.
The TDOA result is provided as an output to be used by the data processing modules.

Data Processing Modules:

These modules receive the TDOA result and perform further processing and analysis of the hydrophone data.
They may include modules for signal conditioning, filtering, timestamping, or other data manipulation techniques.
These modules prepare the data for triangulation calculations and other subsequent processing stages.

Triangulation Module:

This module utilizes the distances obtained from the TDOA values to perform triangulation calculations.
It applies mathematical formulas or algorithms to estimate the precise location of the pinger in 3D space.
The triangulation result, such as the pinger's position, can be passed to the AUV control modules.

AUV Control Modules:

These modules receive the triangulation result and calculate the appropriate heading for the AUV.
They consider the AUV's initial position, orientation, and the estimated pinger location to determine the heading.
The calculated heading is used to control the AUV's propulsion system or steering mechanisms to navigate towards the pinger location. -->
