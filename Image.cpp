#include "Image.h"

//Public Functions
Image::Image() {}

double Image::GetDataAt(int x, int y) // returns the value of the pixel located at position (x,y)
{

	return data[y][x];
}


double Image::GetMean() // getter for mean
{
	return mean;
}


double Image::GetVariance()  // getter for variance
{
	return variance;
}


Image::~Image() // destructor of image
{
	// deletes all vals in data
	for (int i = 0; i < height; ++i) {
		delete data[i];
	}
	delete[] data; // deletes data pointer
}




//Protected Functions

double Image::CalcMean() // called by constructor, calculates mean of values in data and stores in variable mean
{
	//mean = sum of pixels / number of pixels
	int sum = 0;
	int counter = 0;

	//nested for loops visit every pixel in image
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			sum += data[y][x]; // add together value of all pixels in image
			counter++; // count how many pixels are in image
		}
	}
	return (sum / counter); // mean  = sum of pixels / num of pixels
}


double Image::CalcVariance()// called by constructor, calculates the variance of values in data and stores in variable variance
{
	//variance = (sum of (each pixel - mean)^2) / number of pixels - 1
	int value = 0;
	double sum = 0;

	//nested for loops traverse all pixels in matrix
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			value = data[y][x] - mean; // calculate for each pixel, its difference to the mean
			sum += pow(value, 2); // square that difference and sum it for all pixels
		}
	}
	return sum / ((width*height) - 1); // variance = sum / total number of pixels - 1
}


void Image::InputData(std::string Filename) // called by constructor, reads data from txt file and stores it in data
{
	std::ifstream myfile(Filename); // initiailize ifstream
	if (myfile.is_open()) // if file open it can be read from
	{
		while (myfile.good()) // whilst data can be read
		{
			// traverse image visiting every pixel
			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					myfile >> data[y][x]; // store the value for the pixel in the corresponding location in data
				}
			}
		}
		myfile.close(); // close file once done
	}
	else 
	{
		std::cout << "Unable to open file, ensure the file is in the local directory" << std::endl; // file cannot be read from = error message displayed
		system("pause");
		exit(1);
	}
		
}





