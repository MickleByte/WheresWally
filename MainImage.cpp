#include "MainImage.h"

//Public functions

MainImage::MainImage(int width, int height, std::string filename)
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


void MainImage::OutputDataToPGM(std::string filename, std::vector <int> BoxStartX, std::vector <int> BoxStartY, int BoxHeight, int BoxWidth)
{

	std::vector< std::vector<double> > DataCopy;
	DataCopy = AsignData(); // stores data in DataCopy so that pixels can be changed in DataCopy to draw the box without altering the core data

	DrawBox(BoxStartX, BoxStartY, BoxHeight, BoxWidth, DataCopy); // draws box around best match

	int NumElements = height * width; // num pixels in image = width * height
	int Q = 255; // 255 for greyscale

	unsigned char *image; 
	image = (unsigned char *) new unsigned char[NumElements];


	// traverse image visiting each pixel
	for (int y = 0; y < height; y++) 
	{
		for (int x = 0; x < width; x++) 
		{
			image[(y * width) + x] = (unsigned char)DataCopy[y][x]; // store value for pixel in unsigned char array so it can be outputed to pgm
		}
	}

	std::ofstream myfile;
	myfile.open(filename, std::ios::out | std::ios::binary | std::ios::trunc);

	//error message for if file cannot be opened
	if (!myfile) {
		std::cout << "Can't open file: " << filename << std::endl;
		system("pause");
		exit(1);
	}

	// image metadata
	myfile << "P5" << std::endl;
	myfile << width << " " << height << std::endl;
	myfile << Q << std::endl;

	myfile.write(reinterpret_cast<char *>(image), (NumElements) * sizeof(unsigned char)); // write to file

	//error message
	if (myfile.fail()) {
		std::cout << "Can't write image " << filename << std::endl;
		system("pause");
		exit(0);
	}

	myfile.close(); // close file once done

	delete[] image; // delete image pointer

}





//Private functions

void MainImage::DrawBox(std::vector <int> StartX, std::vector <int> StartY, int BoxHeight, int BoxWidth, std::vector< std::vector<double> > &DataCopy) // draws box on image with top left corner (StartX, StartY) and dimensions BoxWidth x BoxHeight
{
	// box is 3 pixels wide
	for (int i = 0; i < StartX.size(); i++) 
	{
		for (int x = StartX[i]; x <= (BoxWidth + StartX[i]); x++) // draw horizontal line by incrementing by one and changing vals to 0
		{
			// top edge
			DataCopy[StartY[i]][x] = 0;
			DataCopy[StartY[i] + 1][x] = 0;
			DataCopy[StartY[i] + 2][x] = 0;

			// bottom edge
			DataCopy[StartY[i] + BoxHeight][x] = 0;
			DataCopy[StartY[i] + BoxHeight - 1][x] = 0;
			DataCopy[StartY[i] + BoxHeight - 2][x] = 0;
		}
		for (int y = StartY[i]; y <= (BoxHeight + StartY[i]); y++) // draw vertical lines
		{
			//left hand side
			DataCopy[y][StartX[i]] = 0;
			DataCopy[y][StartX[i] + 1] = 0;
			DataCopy[y][StartX[i] + 2] = 0;

			//right hand side
			DataCopy[y][StartX[i] + BoxWidth] = 0;
			DataCopy[y][StartX[i] + BoxWidth - 1] = 0;
			DataCopy[y][StartX[i] + BoxWidth - 2] = 0;
		}
	}
	
}


std::vector< std::vector<double> > MainImage::AsignData() // used to move data to a new copy so it can be drawn on without fear of contaminating data for later searches
{
	std::vector< std::vector<double> > DataCopy;
	for (int y = 0; y < height; y++)
	{
		std::vector <double> temp;
		for (int x = 0; x < GetWidth(); x++)
		{
			temp.push_back(data[y][x]);
		}
		DataCopy.push_back(temp);
	}
	return DataCopy;
}

