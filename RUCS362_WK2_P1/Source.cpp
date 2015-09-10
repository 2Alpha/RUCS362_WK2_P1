//***************************************************************************
//  FILENAME:	 AllenAssn2.cpp
//  DESCRIPTION: 
//  DATE:        9/4/15
//  CLASS/TERM:  CS362_X40_Data Structures - CU_CS362 - XIN_X40_15F8W1
//  DESIGNER:	 Andrae Allen
//  FUNCTIONS:	 main - reads values, performs calculations, & displays results
//***************************************************************************

#include <iostream> 
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

enum classLevel { Freshman, Sophomore, Junior, Senior, TooKool4Skool };
classLevel convertCredits(int inputCredit); 

string convertClassLevel2String(classLevel enumeratedTypeValue);

void ProgramDescription();
void readDataFile1(string inputFileName, string studentID[], char studentClassLevel[], classLevel classLevelAsOrdinalValue[], string classLevelAsString[], int credits[], int& studentIndex);

void StoreUndergradData (string[], int[]);

void sortStudentIDDesending(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[]);
void sortStudentIDAscending(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[]);

void createSortedTextFile(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[]);
void StudentIDNumsOnFile(int numOfItems, string alphaNumericList[]);
int runBinarySearch(string target, string searchList[], int listSize);

string studentIDSearch();
bool errorCheckStudentID(string studentIDEntered);


const int MAX_ENTRIES = 10; // Max number of student profiles that can be stored
const int FRESHMAN_BOUNDARY = 32; 
const int SOPHOMORE_BOUNDARY = 63;
const int JUNIOR_BOUNDARY = 95;
const int SENIOR_BOUNDARY = 95;
const int MAX_COLUMNS = 5; 
const int NOT_FOUND = -1;


const string INPUT_FILE_1_NAME = "CREDITS.txt"; // File name for input file
const string OUTPUT_FILE_1_NAME = "SORTED.txt";

int main()
{
	string StudentIDList[MAX_ENTRIES];
	string clasLevelAsString[MAX_ENTRIES];
	char ClassLevelList[MAX_ENTRIES];
	classLevel classLevelAsOVList[MAX_ENTRIES];
	int CreditsList[MAX_ENTRIES];
	int numOfEntries;
	int data2displayLocation; 


	
	ProgramDescription();
	readDataFile1(INPUT_FILE_1_NAME, StudentIDList, ClassLevelList, classLevelAsOVList, clasLevelAsString, CreditsList, numOfEntries);
	
	sortStudentIDDesending(numOfEntries, StudentIDList, classLevelAsOVList);
	createSortedTextFile(numOfEntries, StudentIDList, classLevelAsOVList);

	
	
	
	sortStudentIDAscending(numOfEntries, StudentIDList, classLevelAsOVList);
	StudentIDNumsOnFile(numOfEntries, StudentIDList);

	data2displayLocation = runBinarySearch(studentIDSearch(), StudentIDList, numOfEntries);
	
	


	system("PAUSE");
	return 0;
}

//*************************************************************************
//  FUNCTION:	  ProgramDescription
//  DESCRIPTION:  Displays a brief discription of the program
//  INPUT:        Parameters:  None
//  OUTPUT: 	  Return value: None
//*************************************************************************

void ProgramDescription()
{
	cout << "Program to implement the following:" << endl;
	cout << "1. Convert the number of completed credits for all Undergraduate students" << endl; 
	cout << "   to class levels" << endl;
	cout << "2. Make the data mentioned above searchable by student ID number" << endl; 
}

//*************************************************************************
//  FUNCTION:	  Attempt2OpenFile
//  DESCRIPTION:  

//  INPUT:        Parameters:  
//  OUTPUT: 	  Return value: fileOpenSuccess
//*************************************************************************
void readDataFile1(string inputFileName, string studentID[], char studentClassLevel[], classLevel classLevelAsOrdinalValue[], string classLevelAsString[], int credits[], int& studentIndex)
{
	ifstream inputFile;                      // input file stream variable
	bool fileOpenSuccess;

	string tempStudentID;
	char tempStudentClassLevel;
	int tempCredits;

	studentIndex = 0;
	inputFile.open(inputFileName.c_str());       // open the file

	if (!inputFile)
	{
		fileOpenSuccess = false;
		cout << endl;
		cerr << "Error Opening File named \"" << inputFileName << "\"" << endl;
		system("PAUSE");
		exit(5);
	}

	else
	{
		fileOpenSuccess = true;
		cout << endl;
		cout << "Success opening file named \"" << inputFileName << "\"" << endl;
		cout << endl;
	}



	while ((inputFile) && (studentIndex < MAX_ENTRIES))
	{
		inputFile >> tempStudentID;
		inputFile >> tempStudentClassLevel;
		inputFile >> tempCredits;
		inputFile.ignore(100, '\n');


		if ((tempStudentClassLevel == 'U') )
		{
			studentID[studentIndex] = tempStudentID;
			studentClassLevel[studentIndex] = tempStudentClassLevel; 
			credits[studentIndex] = tempCredits;
			classLevelAsOrdinalValue[studentIndex] = convertCredits(credits[studentIndex]);
			classLevelAsString[studentIndex] = convertClassLevel2String(convertCredits(credits[studentIndex]));
			studentIndex++;
		}

		 if (studentIndex >= MAX_ENTRIES)
		{
			cout << "Alert! Maximum number of Entries (" << MAX_ENTRIES << ") has been reached" << endl << endl;
		}



	}


	
	for (int index = 0; index < studentIndex; index++)
	{
		cout << "student id                  " << studentID[index] << endl;
		cout << "class Level                 " << studentClassLevel[index] << endl;
		cout << "student Credits             " << credits[index] << endl;
		cout << "class level ordinal value   " << classLevelAsOrdinalValue[index] << endl;
		cout << classLevelAsString[index] << endl; 
		cout << endl;
	}



		inputFile.close();


}

classLevel convertCredits(int inputCredit)
{
	
	classLevel classDesignation; 

	if (inputCredit < FRESHMAN_BOUNDARY)
	{
		classDesignation = Freshman;
	}

	else if ((inputCredit >= FRESHMAN_BOUNDARY) && (inputCredit <= SOPHOMORE_BOUNDARY))
	{
		classDesignation = Sophomore;
	}

	else if ((inputCredit > SOPHOMORE_BOUNDARY) && (inputCredit <= JUNIOR_BOUNDARY))
	{
		classDesignation = Junior;
	}

	else if (inputCredit > SENIOR_BOUNDARY)
	{
		classDesignation = Senior;
	}

	else
	{
		classDesignation = TooKool4Skool;
	}

	return classDesignation; 

}

string convertClassLevel2String(classLevel enumeratedTypeValue)
{
	string classLevelAsString; 

	switch (enumeratedTypeValue)
	{
	case Freshman:	classLevelAsString = "Freshman";
		break;
	case Sophomore:	classLevelAsString = "Sophmore";
		break;
	case Junior:	classLevelAsString = "Junior";
		break;
	case Senior:	classLevelAsString = "Senior";
	}

	return classLevelAsString; 


}

// Implementation of a selection sort
void sortStudentIDDesending(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[])
{
	int currentTop,            // Current top of unsorted list
		tryIndex,            // Position to compare value to
		minPosition;       // Position of smallest value
		
	string tempString;              // Temp value for swapping
	classLevel tempClassLevel;

	// for each item in the list (top to bottom)
	for (currentTop = 0; currentTop < numOfItems - 1; currentTop++)
	{

		minPosition = currentTop;      // start with current top as smallest value

		// find smallest value from currentTop down
		for (tryIndex = currentTop + 1; tryIndex < numOfItems; tryIndex++)
			if (alphaNumericList[tryIndex] > alphaNumericList[minPosition]) // Flip Sign to invert sort order,  > = desending
				minPosition = tryIndex;

		// if smallest not at currentTop, swap with currentTop
		if (minPosition != currentTop)
		{
			tempString = alphaNumericList[currentTop];
			tempClassLevel = enumeratedTypeValue[currentTop];

			alphaNumericList[currentTop] = alphaNumericList[minPosition];
			enumeratedTypeValue[currentTop] = enumeratedTypeValue[minPosition];

			alphaNumericList[minPosition] = tempString;
			enumeratedTypeValue[minPosition] = tempClassLevel;


		}   // end swap

	}  // end for

	return;
} // end selectionSort


void sortStudentIDAscending(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[], string classLevelAsString[])
{
	int currentTop,            // Current top of unsorted list
		tryIndex,            // Position to compare value to
		minPosition;       // Position of smallest value

	string tempString;              // Temp value for swapping
	string tempClassLevelAsString;
	classLevel tempClassLevel;


	// for each item in the list (top to bottom)
	for (currentTop = 0; currentTop < numOfItems - 1; currentTop++)
	{

		minPosition = currentTop;      // start with current top as smallest value

		// find smallest value from currentTop down
		for (tryIndex = currentTop + 1; tryIndex < numOfItems; tryIndex++)
			if (alphaNumericList[tryIndex] < alphaNumericList[minPosition]) // Flip Sign to invert sort order,  < = assending
				minPosition = tryIndex;

		// if smallest not at currentTop, swap with currentTop
		if (minPosition != currentTop)
		{
			tempString = alphaNumericList[currentTop];
			tempClassLevel = enumeratedTypeValue[currentTop];
			tempClassLevelAsString = classLevelAsString[currentTop];

			alphaNumericList[currentTop] = alphaNumericList[minPosition];
			enumeratedTypeValue[currentTop] = enumeratedTypeValue[minPosition];
			classLevelAsString[currentTop] = classLevelAsString[minPosition];

			alphaNumericList[minPosition] = tempString;
			enumeratedTypeValue[minPosition] = tempClassLevel;
			classLevelAsString[minPosition] = tempClassLevelAsString;


		}   // end swap

	}  // end for

	return;
} // end selectionSort

void createSortedTextFile(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[])
{
	ofstream sortedList; 
	sortedList.open(OUTPUT_FILE_1_NAME.c_str());     // open file for writing
	char skip = ' ';

	for (int index = 0; index < numOfItems; index++)
	{
		cout << "intList = " << alphaNumericList[index] << "    " << enumeratedTypeValue[index] << endl;
		sortedList << alphaNumericList[index] << skip << enumeratedTypeValue[index] << endl;

	}

	sortedList.close();     // close output file


}

void StudentIDNumsOnFile (int numOfItems, string alphaNumericList[])
{
	int numOfColums = MAX_COLUMNS;
	
	cout << "Student ID numbers on file are :" << endl;
	int index = 0; 

	while (index < numOfItems)
	{
		for (int columnPosition = 0; columnPosition < MAX_COLUMNS; columnPosition++)

		{
			cout << alphaNumericList[index] << "    ";
			index++;
		}
		cout << endl; 
	}


}

string studentIDSearch()
{
	string look4StudentID;
	string validatedStudentID;
	bool errorDetected; 
	
	
	char c; 
	do
	{
		int i = 0;
		cout << endl;
		cout << "Enter ID number of student to find (or X to exit): ";
		cin >> look4StudentID;

		while (look4StudentID[i] != '\0')
		{
			if (isalpha(look4StudentID[i]))
			{
				c = look4StudentID[i];
				look4StudentID[i] = toupper(c);
				i++;
			}

			else
				i++; 
		}
 
		errorDetected = errorCheckStudentID(look4StudentID);

	}

	while (errorDetected == true);


	if (look4StudentID == "X")
	{
		system("PAUSE");       // Program Assignment does not specify exit code or method "Enter ID number of student to find (or X to exit):"
		exit(1);
	}

	else
	{
		validatedStudentID = look4StudentID; 
	}

	return validatedStudentID;


}

bool errorCheckStudentID(string studentIDEntered)
{
	bool IDEntered2short;
	bool IDEntered2Long;
	bool IDEnteredFit;
	bool loopUserInput;
	bool userWants2Exit; 

	int alphaPlacementError = 0;
	int integerPlacementError = 0;
	int length;

	length = studentIDEntered.length();

	if (studentIDEntered == "X")
	{
		IDEntered2short = false;
		IDEntered2Long = false;
		IDEnteredFit = false;
		userWants2Exit = true; 

	}

	
	
	else if (length < 8)
	{
		cout << "ERROR! Input " << studentIDEntered << " is not long enough. System Expected 8 characters." << endl << endl;
		IDEntered2short = true;
		IDEntered2Long = false;
		IDEnteredFit = false;
		userWants2Exit = false;
	}


	else if (length > 8)
	{
		cout << "ERROR! Input " << studentIDEntered << " is too long. System Expected 8 characters." << endl;
		IDEntered2Long = true;
		IDEntered2short = false;
		IDEnteredFit = false;
		userWants2Exit = false;
	}



	else if (length = 8)
	{
		IDEnteredFit = true;
		IDEntered2Long = false;
		IDEntered2short = false;
		userWants2Exit = false;
	}



	if (IDEnteredFit == true)
	{

		for (int index = 0; index < 2; index++)         // Used Loops for error checking 
		{
			if (!(isalpha(studentIDEntered[index])))
			{
				alphaPlacementError++;

			}

		}

		for (int index = 2; index < 8; index++)        // used loops for error checking 
		{
			if (!(isdigit(studentIDEntered[index])))
			{
				integerPlacementError++;
			}


		}

	}


	if ((alphaPlacementError > 0) || (integerPlacementError > 0))
	{
		cout << endl;
		cout << "ERROR!" << endl;
		cout << "For Input \"" << studentIDEntered << "\", the letters and digits are not in the right places" << endl;
		cout << "ID must be exactly 8 characters long, and formatted as : XX######" << endl;
		cout << " 'X' equals Letter, '#' equals Number" << endl;

	}

	if ((IDEntered2short == true) || (IDEntered2Long == true) || (IDEnteredFit = false) || (alphaPlacementError > 0) || (integerPlacementError > 0))
	{
		loopUserInput = true; 
	}

	else if (userWants2Exit = true)
	{
		loopUserInput = false;
	}
	
	return loopUserInput;

}

int runBinarySearch(string target, string searchList[], int listSize)
{
	
	
	int infoPlace = NOT_FOUND;                   // index where target found
	int high, low, middle;

	low = 0;                                     // lower bound of area to search
	high = listSize - 1;                         // upper bound of area to search

	while ((low <= high) &&                      // still places to search AND
		(infoPlace == NOT_FOUND)) {           // target not yet found

		middle = (low + high) / 2;            // calculate middle index

		if (target < searchList[middle])      // target less than middle value
			high = middle - 1;
		else if (target > searchList[middle]) //target more than middle value
			low = middle + 1;
		else
			infoPlace = middle;               // target found
	}     // end while

	return infoPlace;
	



}
void sendResults2Console(int datalocation, string searchList[])



{
	cout << "The student with ID <<  


}