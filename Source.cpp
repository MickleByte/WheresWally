#include "Section.h"
#include "SampleImage.h"
#include "MainImage.h"


struct Result // used to store
{
	double total;
	int Xpos;
	int Ypos;
	bool Match = false;
};



int GetComparisonMetric() // prints menu to ask user for comparison metric and returns a choice
{
	//print options
	std::cout << std::endl;
	std::cout << "Choose Comparison Metric:" << std::endl;
	std::cout << "1. Difference" << std::endl;
	std::cout << "2. Sum of Squared Difference" << std::endl;
	std::cout << "3. Normalised Correlation" << std::endl;

	//as input validation, input is a string
	std::string input;
	std::cin >> input;
	int choice;
	if ((input == "1") || (input == "2") || (input == "3")) // if the string inputted is not one of the options (1,2 or 3) then GetComparisonMetric Called again
	{
		choice = std::stoi(input); // cast to int
		return choice; // return valid input
	}
	else
	{
		std::cout << "Incorrect input"; // print error message
		return GetComparisonMetric(); // call again to get valid input
	}	
}

int GetSearchMethod() // prints menu to ask user for search method + returns their input
{

	//print menu
	std::cout << std::endl;
	std::cout << "Menu:" << std::endl;
	std::cout << "1. Linear Search (slower)" << std::endl;
	std::cout << "2. Binary Search (faster)" << std::endl;
	std::cout << "9. Exit Program" << std::endl;

	//input as string for validation
	std::string input;
	std::cin >> input;
	int choice;
	if ((input == "1") || (input == "2") || (input == "9")) // only procede if a valid input
	{
		choice = std::stoi(input); // cast to int
		return choice; // return valid input
	}
	else // if non valid input
	{
		std::cout << "Incorrect input"; // print error message
		return GetSearchMethod(); // call again to get valid input
	}
}

int GetAccuracy() // prints menu to get accuracy of search and returns user input
{
	//print menu
	std::cout << std::endl;
	std::cout << "Choose comparison accuracy:" << std::endl;
	std::cout << "1. High Accuracy (compare each pixel) - Runtime should be around a 1 minute 30 seconds" << std::endl;
	std::cout << "2. Medium Accuracy (compare every third pixel) - Runtime should be a dozen seconds" << std::endl;
	std::cout << "3. Low Accuracy (compare every 5th pixel) - Runtime should be a few seconds" << std::endl;

	//input stored as string
	std::string input;
	std::cin >> input;
	int choice;
	if ((input == "1") || (input == "2") || (input == "3")) // if input is valid (equals 1, 2 or 3)
	{
		choice = std::stoi(input); //cast input to int
	}
	else
	{
		std::cout << "Incorrect input"; // print error message
		return GetAccuracy(); // get valid input
	}


	//the val inputed by the user is the menu choice, however we want to return to the program the number of steps taken after each search
	if (choice == 2) // menu choice 2 is 3 steps so 3 is returned
	{
		return 3;
	}
	else if (choice == 3) // meny choice 3 = 5 steps
	{
		return 5;
	}
	else // menu choice 1 is 1 step
	{
		return choice;
	}


}

int GetGoalMatches() // prints menu for num of matches the user wants and gets input
{
	//print menu
	std::cout << std::endl;
	std::cout << "Enter an integer 1-9 inclusive for N, where N is the desired number of best matches:" << std::endl;

	//store input as string
	std::string input;
	std::cin >> input;
	int choice;
	if ((input == "1") || (input == "2") || (input == "3") || (input == "4") || (input == "5") || (input == "6") || (input == "7") || (input == "8") || (input == "9")) // if input is not a valid string it will go to else
	{
		choice = std::stoi(input); // cast input to int
		return choice; // return input as int
	}
	else
	{
		std::cout << "Incorrect input"; // print error message
		return GetGoalMatches(); // recall function to get valid input
	}
	
}





double difference(int MaxY, int MaxX, int CurrentX, int CurrentY, MainImage *M, SampleImage *S, int accuracy)
{
	double sum = 0; // current total of mapping

	// goes through main image starting at position (CurrentX, CurrentY) using IndexX and IndexX as counters. Accuracy is num of steps taken after each comparison
	for (int IndexY = 0; IndexY < MaxY; IndexY += accuracy) 
	{
		for (int IndexX = 0; IndexX < MaxX; IndexX += accuracy)
		{
			sum += abs(M->GetDataAt(CurrentX + IndexX, CurrentY + IndexY) - S->GetDataAt(IndexX, IndexY)); // gets absolute difference of pixel in MainArr & pixel in SampleArr and adds it to sum
		}
	}
	return sum; // return sum of mapping
}

double SSD(int MaxY, int MaxX, int CurrentX, int CurrentY, MainImage *M, SampleImage *S, int accuracy)
{
	double sum = 0; // current total of mapping
	for (int IndexY = 0; IndexY < MaxY; IndexY += accuracy) // goes through main image starting at position (CurrentX, CurrentY) using IndexX and IndexX as counters
	{
		for (int IndexX = 0; IndexX < MaxX; IndexX += accuracy)
		{
			sum += pow((M->GetDataAt(CurrentX + IndexX, CurrentY + IndexY) - S->GetDataAt(IndexX, IndexY)), 2); // gets absolute difference of pixel in MainArr & pixel in SampleArr and adds it to sum
		}
	}
	return sum; // return sum of mapping
}

double NCC(double MaxY, double MaxX, int CurrentX, int CurrentY, MainImage *M, SampleImage *S, int accuracy)
{
	// for matrices X (MainImage) and Y (SampleImage)
	//NCC = (1/N) * (  (Sum( (xi - Mx)(yi - My) )  ) / (VarX^2 * VarY^2) 
	//xi = elements in matrix x, yi = elements in matrix y
	//Mx and My = mean of vals in matrices x and y respectively
	//VarX = variance for vals in matrix x, and VarY = variance for vals in matrix y
	// and N = number of elemenets in matrix Y


	double result = 0;
	double sum = 0;

	// goes through main image starting at position (CurrentX, CurrentY) using IndexX and IndexX as counters
	for (int IndexY = 0; IndexY < MaxY; IndexY += accuracy)
	{
		for (int IndexX = 0; IndexX < MaxX; IndexX += accuracy)
		{
			sum += ((M->GetDataAt(CurrentX + IndexX, CurrentY + IndexY) - M->GetMean()) * (S->GetDataAt(IndexX, IndexY) - S->GetMean())); // calculating NCC
		}
	}
	sum = sum / (pow(M->GetVariance(), 2) * pow(S->GetVariance(), 2)); // calculating NCC
	result = sum * (1 / (MaxX * MaxY)); // calculating NCC
	return result; // return NCC for that mapping
}


void ExecuteLinearSearch(MainImage *MainImage, SampleImage *SampleImage, std::vector <Result> &vals, int ComparisonMetric, int accuracy, int StartX, int StartY, int LimitX, int LimitY, int NumDesiredMatches) // conducts the actual linear search ( stepping throught the matrix)
{

	Result Temp; // temp instance of Result structure to store outcome of mapping - is pushed onto vals vector which is later used to find the N best mappings.

	for (int X = StartX; X <= LimitX; X++)//Nested fors that traverse from top left to bottom right of mainImage
	{
		for (int Y = StartY; Y <= LimitY; Y++) // same as other for loop but in the y direction
		{

			// whatever comparison metric user selected is used
			if (ComparisonMetric == 1) //difference comparison
			{
				Temp.total = difference(SampleImage->GetHeight(), SampleImage->GetWidth(), X, Y, MainImage, SampleImage, accuracy);
			}
			else if (ComparisonMetric == 2) //sum squared difference comparison
			{
				Temp.total = SSD(SampleImage->GetHeight(), SampleImage->GetWidth(), X, Y, MainImage, SampleImage, accuracy);
			}
			else if (ComparisonMetric == 3) //normalised correlation comparison
			{
				Temp.total = NCC(SampleImage->GetHeight(), SampleImage->GetWidth(), X, Y, MainImage, SampleImage, accuracy);
			}

			//stores results of mapping
			Temp.Xpos = X;
			Temp.Ypos = Y;
			Temp.Match = false;

			vals.push_back(Temp); // result pushed onto vector
		}

	}

}

void LinearSearch(MainImage *ClutteredScene, SampleImage *WallyGrey)
{
	int ComparisonMetric = GetComparisonMetric(); // retrieves user input on choice of comparison metric (absolute difference, sum of squared difference, normalised correlation)

	int accuracy = GetAccuracy(); // gets accuracy with which user wants to compare images (what fraction of total comparisons does user want (all possible, 1/3, 1/5))

	int NumberDesiredMatches = GetGoalMatches(); // gets input from user on the number of matches they want

	//output so user knows what program is doing as some of the higher accuracy searches can take a few minutes to run 
	std::cout << "Searching for Wally..." << std::endl;
	std::cout << std::endl;

	// vector that will store the results and locations of all of the mappings done - it is passed by ref so the data is accesible in this function
	std::vector <Result> vals;
	ExecuteLinearSearch(ClutteredScene, WallyGrey, vals, ComparisonMetric, accuracy, 0, 0, (ClutteredScene->GetWidth() - WallyGrey->GetWidth()), (ClutteredScene->GetHeight() - WallyGrey->GetHeight()), NumberDesiredMatches); // actual mappings performed here

	// vectors that will store the N X and Y coordinates of the top left corner of the N best matches
	std::vector <int> Xcor;
	std::vector <int> Ycor;

	int MatchesFound = 0; // matches found so far - begins at 0

	//keeps searching until N best matches are found
	while (MatchesFound < NumberDesiredMatches) 
	{
		double LowestVal = 100000000000; // sets LowestVal found so far as extremely high as it needs to be overwritten by the first mapping but cannot be left uninitialized
		int BestXLocation = 0; // stores the current best X location
		int BestYLocation = 0; // stores the current best Y location

		// traverse vector vals looking for the lowest mapping value
		for (int i = 0; i < vals.size(); i++)
		{
			if ((vals[i].total < LowestVal)&&(vals[i].Match == false))
			{
				LowestVal = vals[i].total; // if a value is lower than the current lowest
				BestYLocation = vals[i].Ypos; // store its X and Y coordinates
				BestXLocation = vals[i].Xpos;
				vals[i].Match = true; // mark it as being looked at
			}
		}
		MatchesFound++; // increase matches found by 1
		Xcor.push_back(BestXLocation); // push the coordinates for the best match from that pass of vals vector onto Xcor and Ycor vectors 
		Ycor.push_back(BestYLocation);
	}
	
	//generates an appropriate filename based on the users choice of accuracy, comparisonmetric and search method to aid user in finding the correct output file
	std::string Filename;
	Filename = "OutputLinear"; // begins with output linear as this is the output of linear search

	//different suffix appended onto end depending on comparison metric chosen
	if (ComparisonMetric == 1)
	{
		Filename += "Difs";
	}
	else if (ComparisonMetric == 2)
	{
		Filename += "SSD";
	}
	else if (ComparisonMetric == 3)
	{
		Filename += "NC";
	}


	// different accuracy suffic appended on end depending on user accuracy choice
	if (accuracy == 1)
	{
		Filename += "High";
	}
	else if (accuracy == 3)
	{
		Filename += "Medium";
	}
	else if (accuracy == 5)
	{
		Filename += "Low";
	}

	
	Filename += ".pgm";//append with file type


	std::cout << "Outputing to file " << Filename << "..." << std::endl; // prints to console name of file so user can find it more easily

	// calls the output function of ClutteredScene, passes to it the vectors Xcor and Ycor which mark top lefts of best match boxes. as well as WallyGrey height and width which are the boxes dimmensions
	ClutteredScene->OutputDataToPGM(Filename, Xcor, Ycor, WallyGrey->GetHeight(), WallyGrey->GetWidth());
	
	//output succesful message
	std::cout << "Success!" << std::endl;
	std::cout << std::endl;
}





void ExecuteBinS(Section *Parent, MainImage *M, int goalWidth, int goalHeight, int MatchesFound, int GoalMatches, std::vector <int> &Xcor, std::vector <int> &Ycor) // performs the search recursively
{
		if ((Parent->GetWidth() > goalWidth) && (Parent->GetHeight() > goalHeight))	// whilst the passed Section (parent) is larger than the dimmensions of the sample (goalWidth, GoalHeight) search must continue
		{		
	
			if (Parent->Child[0]->GetComparedMeanVal() <= Parent->Child[1]->GetComparedMeanVal()) // if child 0 has a lower meanVal it is more likely to contain the best match
			{
				ExecuteBinS(Parent->Child[0], M, goalWidth, goalHeight, MatchesFound, GoalMatches, Xcor, Ycor); // recursively call function but this time pass the child 0 section
			}
			else //  child 1 must therefore have the lower mean value
			{
				ExecuteBinS(Parent->Child[1], M, goalWidth, goalHeight, MatchesFound, GoalMatches, Xcor, Ycor); // recursively call function but this time on child 1
			}				
		}
		else // once the sections are as small as (or smaller than) the sample
		{		
			// to be able to find the N best matches this section would need some sort of if to check which sections have been MarkedAsBest and call their sibilings to be searched instead
			Parent->MarkAsBestMatch(true);
			
			//store location of best match in Xcor, Ycor
			Xcor.push_back(Parent->GetLowBoundX());
			Ycor.push_back(Parent->GetLowBoundY());
		}
}

void BinarySearch(MainImage *ClutteredScene, SampleImage *WallyGrey) // sets up the binary search
{
	//updates user on what program is doing
	std::cout << "Searching for Wally..." << std::endl;

	//vectors that store top left coordinate(s) of best match(s)
	std::vector <int> Xcor;
	std::vector <int> Ycor;

	int GoalMatches = 1; // currently BinarySearch only finds best match, not N best but there is the possibility to add that functionality - here the GetGoalMatches() function could be called for example
	
	Section clutt(0, 0, ClutteredScene->GetWidth(), ClutteredScene->GetHeight(), WallyGrey->GetWidth(), WallyGrey->GetHeight(), WallyGrey->GetMean() , ClutteredScene); // creates local instance of Section which represents the Main Image
	Section* PtrMainImage = &clutt; // creates pointer to that Main Image representation

	//loop for desired number of matches
	for (int i = 0; i < GoalMatches; i++)
	{
		ExecuteBinS(PtrMainImage, ClutteredScene, WallyGrey->GetWidth(), WallyGrey->GetHeight(), 0, GoalMatches, Xcor, Ycor); // runs the search by passing the main image pointer, and dimmensions of sample
	}

	//tells user file name to aid them in finding it later
	std::cout << "Outputing result to OutputBinarySearch.pgm..." << std::endl;

	//outputs clutteredscene with best match marked as box. Vectors Xcor and Ycor store coordinates for top left of best match box and WallyGrey Width and height are used as the dimmensions of the box
	ClutteredScene->OutputDataToPGM("OutputBinarySearch.pgm", Xcor, Ycor, WallyGrey->GetHeight(), WallyGrey->GetWidth());
	
	// Tells user that program was succesful
	std::cout << "Output Complete" << std::endl;
	std::cout << std::endl;
	
}





int main()
{
	//Read txt files into instances of MainImage and SampleImage, pointed to by *ClutteredScene and *WallyGrey
	std::cout << "Reading in Files..." << std::endl;
	MainImage *ClutteredScene = new MainImage(1024, 768, "Cluttered_scene.txt");
	SampleImage *WallyGrey = new SampleImage(36, 49, "Wally_grey.txt");



	int MainMenuInput = GetSearchMethod(); // Prints Main menu and gets input

	while (MainMenuInput != 9)  // if input is 9 (exit) program leaves loop and ends
	{
		if (MainMenuInput == 1) // if input = 1 user wants a linear search
		{
			LinearSearch(ClutteredScene, WallyGrey); // go to corrisponding sub routine
		}
		else if (MainMenuInput == 2) // if input = 2 user wants nearest neighbour search
		{
			BinarySearch(ClutteredScene, WallyGrey); // go to corrisponding sub routine
		}
		MainMenuInput = GetSearchMethod();
	}



	//delete pointers for cluttered + wally
	delete ClutteredScene;
	delete WallyGrey;


	return 0;
}