#include "Matrix.h"

int Matrix::GetWidth() // public getter for width
{
	return width;
}

int Matrix::GetHeight() // public getter for height
{
	return height;
}

void Matrix::SetWidth(int width) // protected setter for width
{
	this->width = width;
}

void Matrix::SetHeight(int height) // protected setter for height
{
	this->height = height;
}