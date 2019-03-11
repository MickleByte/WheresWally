#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <string>


//Define bas class matrix with int vars width and height as well as setters and getters for with and height
class Matrix
{
public:
	int GetWidth();
	int GetHeight();
protected:
	int width;
	int height;
	void SetWidth(int Width);
	void SetHeight(int Height);
};