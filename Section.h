#pragma once

#include "Matrix.h"
#include "SampleImage.h"
#include "MainImage.h"

class Section : public Matrix // publicly inherit Matrix
{
public:
	Section(int LowBoundX, int LowBoundY, int width, int height, int SampleImageWidth, int SampleImageHeight, double SampleImageMean, MainImage *M); // constructor that takes a MainImage, SampleImage as well as dimensions of Section and top left corner of Section - used for top level Section only

	int GetLowBoundX(); // getter for top left corner x coordinate
	int GetLowBoundY(); // getter for top left corner y coordinate
	double GetComparedMeanVal(); // getter for MeanValCompared
	void MarkAsBestMatch(bool TorF); // Setter for boolean TakenAsBestMatch
	bool CheckBestMatchBool();	 // getter for TakenAsBestMatch
	MainImage* GetMainIPointer(); // getter for MainImage pointer
	double GetSampleImageMean();
	double GetSampleImageWidth();
	double GetSampleImageHeight();
	std::vector<Section*> Child; // vector of Sections used for pointing to the Sections 4 possible children
	Section *Parent;
private:
	Section(int LowBoundX, int LowBoundY, int width, int height, Section *Parent); // constructor used only when creating a sub Section of a current Section therefore private

	int LowBoundX; // stores top left corner x coordinate
	int LowBoundY; // stores top left corner y coordinate
	bool TakenAsBestMatch; // boolean to identify whether this Section has been taken as a best match - used in finding N best matches
	double MeanValCompared; // abs(MeanVal - mean of sample)
	
	// minimum width and height a Section could be
	int SampleImageWidth;
	int SampleImageHeight;
	double SampleImageMean;
	MainImage *MainI; // main image of which the Section points to its data
	
	void AsignChildren(int MinX, int MinY); // assigns Section with its 4 children
	double CalcMeanVal(); // calculate mean  val of pixels of main image in area represented by Section
};