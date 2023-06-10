#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <fftw3.h>

#define PI 3.14159265358979323846
#define DATA_SIZE 100
#define THRESHOLD 100 // Threshold for applying gain control
#define GAIN_FACTOR 2 // Factor by which to increase signal under threshold
#define FREQ_INTEREST 50.0 // Specific frequency we're interested in analyzing
#define FS 1000.0 // Sample rate of our data
#define WINDOW_SIZE 250000 // This is our window size



double data[DATA_SIZE]; // The array to hold our input data

// ... (Other function definitions)

/*
 * Function to calculate RMS
 * It takes array of data and its size as input
 * Returns the RMS value
 */
double calculate_rms(double* data, int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += data[i] * data[i];
    }
    return sqrt(sum / size);
}

/*
 * Function to calculate moving RMS
 * It takes array of data, its size and window size as input
 * Prints the RMS value for each window
 */
void calculate_moving_rms(double* data, int size, int window_size) {
    for (int i = 0; i <= size - window_size; i += window_size / 2) { // Here, we are stepping by window_size / 2 for 50% overlap
        double sum = 0;
        for (int j = i; j < i + window_size; j++) {
            sum += data[j] * data[j];
        }
        double rms = sqrt(sum / window_size);
        printf("The RMS of window starting at index %d is %.2f\n", i, rms);
    }
}

/*
 * Function to calculate the DFT using the FFTW library.
 * It takes an array of real-valued data and its size as input, and an array of complex numbers as output.
 * The input data is copied into an array of complex numbers (with zero imaginary parts), and the FFTW library is used to compute the DFT.
 * The result array is filled with the DFT values.
 */
void calculate_dft(double* data, int size, fftw_complex* result) {
    fftw_complex *in;
    fftw_plan p;

    // Allocate memory for input and output data
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * size);
    
    // Copy data to the input array
    for (int i = 0; i < size; i++) {
        in[i][0] = data[i];  // Real part
        in[i][1] = 0;  // Imaginary part
    }

    // Create a plan
    p = fftw_plan_dft_1d(size, in, result, FFTW_FORWARD, FFTW_ESTIMATE);
    
    // Execute the plan
    fftw_execute(p);

    // Destroy the plan
    fftw_destroy_plan(p);
    fftw_free(in);
}

/*
 * Function to apply gain control
 * It takes array of data, its size and gain factor as input
 * Multiplies the data with the gain factor
 */
void apply_gain_control(double* data, int size, double gain_factor) {
    for(int i = 0; i < size; i++) {
        data[i] *= gain_factor;
    }

    // #TODO: Add logic here to write the new gain factor to your AD5263
    // Usually this would involve a function provided by the manufacturer's library
    // e.g., write_gain_to_AD5263(gain_factor);
}


int main() {
    // TODO: Insert your logic here to fill the 'data' array with your actual data

    // Calculate the Root Mean Square (RMS) of the data
    double rms = calculate_rms(data, DATA_SIZE);
    printf("The RMS of the given numbers is %.2f\n", rms);

    // Calculate the Discrete Fourier Transform (DFT) of the data
    fftw_complex dft_result[DATA_SIZE];
    calculate_dft(data, DATA_SIZE, dft_result);
    printf("DFT of the given array is:\n"); // Print the real and imaginary parts of the DFT result
    for (int i = 0; i < DATA_SIZE; i++) {
        printf("DFT[%d] = %.2f %+.2fi\n", i, creal(dft_result[i]), cimag(dft_result[i]));
    }

    // Calculate the index 'k' in the DFT result that corresponds to the frequency of interest
    int k = round(FREQ_INTEREST * DATA_SIZE / FS);

    // Calculate the magnitude and phase of the DFT result at the frequency of interest
    double magnitude = cabs(dft_result[k]); // absolute value of a complex number
    double phase = carg(dft_result[k]); // phase angle of a complex number in radians

    // Print the magnitude and phase of the DFT result at the frequency of interest
    printf("Magnitude of DFT[%d] = %.2f\n", k, magnitude);
    printf("Phase of DFT[%d] = %.2f rad\n", k, phase);

    // *apply gain control to the original data*
    // If the magnitude of the DFT result at the frequency of interest is less than the threshold,
    if (magnitude < THRESHOLD) {
        apply_gain_control(data, DATA_SIZE, GAIN_FACTOR);
        printf("Gain control applied. Gain factor: %.2f\n", GAIN_FACTOR);
    }

    return 0;
}