#pragma once

#include "Image.h"

class MainImage : public Image // publicly inherits image
{
public:
	MainImage(int width, int height, std::string filename); // constructor
	void OutputDataToPGM(std::string filename, std::vector <int> BoxStartX, std::vector <int> BoxStartY, int BoxHeight, int BoxWidth); // calls drawbox to put box around best match, and then outputs the image to a PGM file with the box
private:
	void DrawBox(std::vector <int> StartX, std::vector <int> StartY, int BoxHeight, int BoxWidth, std::vector< std::vector<double> > &DataCopy); // draws box around best match for output
	std::vector< std::vector<double> > AsignData(); // used to transfer data to a new copy when drawing on box for output to pgm (don't want to permanently change data)
};