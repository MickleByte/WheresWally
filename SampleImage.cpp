#include "SampleImage.h"

SampleImage::SampleImage(int width, int height, std::string filename)
{
	SetWidth(width); // set width as given width
	SetHeight(height); // set image height as given height
	data = new double*[height]; // data is pointer to height number of pointers

	// nested fors traverse matrix visiting every pixel
	for (int y = 0; y < height; y++) {
		data[y] = new double[width]; // each pointer that the pointer data points to points to a double
		for (int x = 0; x < width; x++) {
			data[y][x] = 0.0; // initialize every pixel as 0, actualy vals will be stored in InputData(), but for now 0 used as placeholder
		}
	}
	InputData(filename); // get pixel values from file and store it in data
	mean = CalcMean(); // calc mean and store it in mean
	variance = CalcVariance(); // calc variance and store it
}