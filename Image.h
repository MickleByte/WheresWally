#pragma once

#include "Matrix.h"

class Image : public Matrix // publicly inherits Matrix
{
public:
	Image(); //Default constructor
	double GetDataAt(int x, int y); // returns value of data stored in position (x,y) in image's data
	double GetMean();  // getter for the mean of values stored in data	
	double GetVariance(); // getter for variance of values stored in data	
	~Image(); // destructor - deletes data pointer
	double** data;
protected:
	
	double variance; // variances of values in data
	double mean; // mean of values in data
	double CalcMean(); // called by constructor, calculates mean of values in data and stores in variable mean
	double CalcVariance(); // called by constructor, calculates the variance of values in data and stores in variable variance
	void InputData(std::string Filename); // called by constructor, reads data from txt file and stores it in data
};