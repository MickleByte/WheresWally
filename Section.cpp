#include "Section.h"

//Public Functions
Section::Section(int LowBoundX, int LowBoundY, int width, int height, int SampleImageWidth, int SampleImageHeight, double SampleImageMean, MainImage *M) // constructor only used to create top level Section
{
	this->SampleImageHeight = SampleImageHeight; // stores SampleImage height (min height a Section can be)
	this->SampleImageWidth = SampleImageWidth; // stores width of sampleimage (min width a Section can be)
	this->SampleImageMean = SampleImageMean;
	this->MainI = M; // MainImage pointer
	this->LowBoundX = LowBoundX; // gets X coordinate of top left corner
	this->LowBoundY = LowBoundY; // Y coordinate of top left corner
	this->width = width; // width of Section
	this->height = height; // height of Section
	double MeanVal = CalcMeanVal(); // calcs mean of pixels in Section and stores in MeanVal
	this->MeanValCompared = abs(MeanVal - SampleImageMean); // calculates what the absolute( Mean of SampleImage - Mean of Section) and stores in MeanValCompared
	AsignChildren(SampleImageWidth, SampleImageHeight); // assigns the Section its 4 children - when this constructor called it will also create these children calling the 2nd private constructor
}

//getter for top left corner X coordinate
int Section::GetLowBoundX()
{
	return LowBoundX;
}

//getter for top left corner Y coordinate
int Section::GetLowBoundY()
{
	return LowBoundY;
}

//getter for mean
double Section::GetComparedMeanVal()
{
	return MeanValCompared;
}

//setter for TakenAsBestMatch
void Section::MarkAsBestMatch(bool TorF)
{
	TakenAsBestMatch = TorF;
}

//getter for TakenAsBestMatch
bool Section::CheckBestMatchBool()
{
	return TakenAsBestMatch;
}



//getter for mainImage pointer
MainImage* Section::GetMainIPointer()
{
	return MainI;
}

// getter for the sampleImage mean
double Section::GetSampleImageMean() 
{
	return SampleImageMean;
}

//getter for the sample image width
double Section::GetSampleImageWidth()
{
	return SampleImageWidth;
}

//getter for the sample image height
double Section::GetSampleImageHeight()
{
	return SampleImageHeight;
}


//Private functions

Section::Section(int LowBoundX, int LowBoundY, int width, int height, Section *Parent) // constructor for sub Sections - called when top level Section created (see above constructor)
{
	this->SampleImageHeight = Parent->GetSampleImageHeight(); // stores SampleImage height (min height a Section can be)
	this->SampleImageWidth = Parent->GetSampleImageWidth(); // stores width of sampleimage (min width a Section can be)
	this->MainI = Parent->GetMainIPointer(); // stores pointer to MainImage as same as parent
	this->LowBoundX = LowBoundX; // x coordinate of top left corner
	this->LowBoundY = LowBoundY; // y coordinate of top left corner
	this->width = width; // width of Section
	this->height = height; // height of Section
	double MeanVal = CalcMeanVal(); // mean val of pixels in Section
	this->MeanValCompared = abs(MeanVal - Parent->GetSampleImageMean()); // calculates what the absolute( Mean of SampleImage - Mean of Section) and stores in MeanValCompared
	AsignChildren(Parent->GetSampleImageWidth(), Parent->GetSampleImageHeight()); // assign children - this continues until children are smaller or same size as SampleImage
}


void Section::AsignChildren(int MinX, int MinY) // MinX & MinY are dimmensions of SampleImage
{
	if (((width) >= MinX) && ((height) >= MinY)) // ensures that sub Sections keep being made until they are same size as Section
	{
		if (width >= height)
		{
			Child.push_back(new Section(GetLowBoundX(), GetLowBoundY(), GetWidth() / 2, GetHeight(), this)); //  Left child
			Child.push_back(new Section(GetWidth() / 2, GetLowBoundY(), GetWidth() / 2, GetHeight(), this)); //  right child
		}
		else if (height > width)
		{
			Child.push_back(new Section(GetLowBoundX(), GetLowBoundY(), GetWidth(), GetHeight() / 2, this)); // Top child
			Child.push_back(new Section(GetLowBoundX(), GetHeight() / 2, GetWidth(), GetHeight() / 2, this)); // bottom child

		}
	}	
}

double Section::CalcMeanVal() // calculate mean value of pixels in main image that the Section represents
{
	int sum = 0;
	int counter = 0;

	//nested for loops traverse the Section visiting every pixel
	for (int y = 0; y < height - 1; y++)
	{
		for (int x = 0; x < width - 1; x++)
		{
			sum += MainI->data[y + LowBoundY][x + LowBoundX]; // sum of pixel vals
			counter++; //count number of pixels
		}
	}
	return (sum / counter); // mean = sum of pixels / num pixels
}
