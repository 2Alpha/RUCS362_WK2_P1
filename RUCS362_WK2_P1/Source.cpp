//***************************************************************************
//  FILENAME:	 AllenAssn2.cpp
//  DESCRIPTION: Program that will implement the following. 
// 				 1. Read input file named CREDITS.txt
//				 2. Convert the number of completed credits for all Undergraduate students"
//				 3. create File called SORTED.TXT containing student ID and one corresponding class level per line.
//				 4. Display List of available student ID ready to be searched.
//				 5. Report a searchable student's class level in string form.
//
//  DATE:        9/4/15
//  CLASS/TERM:  CS362_X40_Data Structures - CU_CS362 - XIN_X40_15F8W1
//  DESIGNER:	 Andrae Allen
//  FUNCTIONS:	 main - reads values, performs calculations, & displays results
//               ProgramDescription - Displays a brief discription of the program
//				 readAndSaveData - reads and saves specified data from txt file CREDITS.TXT
//				 convertCredits - coverts the number of credits into a class level
//				 convertClassLevel2String - coverts enumerated class level in string type class level 
//				 sortStudentIDDesending - Sorts student ID's by decending order IE ZZ123456 to AA123456
//				 sortStudentIDAscending -  Sorts student ID's by ascending order IE AA123456 to ZZ123456 
//				 createSortedTextFile - Creates a data file containing student Id's and class levels in decending order
//				 StudentIDNumsOnFile - Displays a list of all the Student ID numbers on file
//				 studentIDSearch - reads user input for student ID to look up
//				 errorCheckStudentID - Checks if user input for student ID meets the specified parameters 
//				 runBinarySearch - runs binary search of student ID entered by user 
//				 sendResults2Console - sends search results to console
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
void readAndSaveData(string inputFileName, string studentID[], char studentClassLevel[], classLevel classLevelAsOrdinalValue[], string classLevelAsString[], int credits[], int& studentIndex);


void sortStudentIDDesending(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[], string classLevelAsString[]);
void sortStudentIDAscending(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[], string classLevelAsString[]);

void createSortedTextFile(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[]);
void StudentIDNumsOnFile(int numOfItems, string alphaNumericList[]);

string studentIDSearch();
bool errorCheckStudentID(string studentIDEntered);

int runBinarySearch(string target, string searchList[], int listSize);

void sendResults2Console(string StudentID, int dataLocation, string alphaNumericList[], string classLevelAsString[]);


const int MAX_ENTRIES = 1000; // Max number of student profiles that can be stored
const int FRESHMAN_BOUNDARY = 32; 
const int SOPHOMORE_BOUNDARY = 63;
const int JUNIOR_BOUNDARY = 95;
const int SENIOR_BOUNDARY = 95;
const int MAX_COLUMNS = 5; 
const int NOT_FOUND = -1;
const int ZERO = 0; 
const int IGNORE_AMOUNT = 100;
const int END_OF_LETTERS = 2; 
const int END_OF_NUMBERS = 8;
const int TWO = 2;
const int ONE = 1; 

const string INPUT_FILE_1_NAME = "CREDIT.txt"; // File name for input file, Assignment documentation refers to both "CREDIT.txt" amd  "CREDITS.txt";
const string OUTPUT_FILE_1_NAME = "SORTED.txt"; // File name for output file 

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
	readAndSaveData(INPUT_FILE_1_NAME, StudentIDList, ClassLevelList, classLevelAsOVList, clasLevelAsString, CreditsList, numOfEntries);
	

	sortStudentIDDesending(numOfEntries, StudentIDList, classLevelAsOVList, clasLevelAsString);
	createSortedTextFile(numOfEntries, StudentIDList, classLevelAsOVList);

	sortStudentIDAscending(numOfEntries, StudentIDList, classLevelAsOVList, clasLevelAsString);
	StudentIDNumsOnFile(numOfEntries, StudentIDList);

	string properlyFormatedStudentID = studentIDSearch(); 
	
	data2displayLocation = runBinarySearch(properlyFormatedStudentID, StudentIDList, numOfEntries);


	sendResults2Console(properlyFormatedStudentID, data2displayLocation, StudentIDList, clasLevelAsString);
	
	


	system("PAUSE");
	return ZERO;
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
	cout << "1. Read input file named CREDITS.txt " << endl;
	cout << "2. Convert the number of completed credits for all Undergraduate students" << endl; 
	cout << "3. create File called SORTED.TXT containing student ID and one corresponding class level per line." << endl;
	cout << "4. Display List of available student ID ready to be searched"  << endl;
	cout << "5. Report a searchable student's class level in string form" << endl; 
}

//*************************************************************************
//  FUNCTION:	  readAndSaveData
//  DESCRIPTION:  reads specified data from txt file CREDITS.TXT
//
//  INPUT:        Parameters: inputFileName - text file containing studend data 
//                            studentID - array of student ID's 
//                            studentClassLevel - array of student class Levels 
//                            classLevelAsOrdinalValue - class levels as ordinal values 
//                            classLevelAsString - class level as string
//                            credits - number of credits
//                            studentIndex - student index 
//
//  OUTPUT: 	  Return value: None
//*************************************************************************
void readAndSaveData(string inputFileName, string studentID[], char studentClassLevel[], classLevel classLevelAsOrdinalValue[], string classLevelAsString[], int credits[], int& studentIndex)
{
	ifstream inputFile;                      // input file stream variable
	bool fileOpenSuccess;					// file open success 

	string tempStudentID;					//  temp student id 
	char tempStudentClassLevel;				// temp student class level 
	int tempCredits;						// temp credits

	studentIndex = ZERO;
	inputFile.open(inputFileName.c_str());       // open the file

	// If cannot open file
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


	// while data remains to be read and max entries has not been reached
	while ((inputFile) && (studentIndex < MAX_ENTRIES))
	{
		inputFile >> tempStudentID;						// temp student Id 
		inputFile >> tempStudentClassLevel;				// temp Student Class Level
		inputFile >> tempCredits;						// temp credits
		inputFile.ignore(IGNORE_AMOUNT, '\n');


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


	// data capture debugging 
	/*
	for (int index = ZERO; index < studentIndex; index++)
	{
		cout << "student id                  " << studentID[index] << endl;
		cout << "class Level                 " << studentClassLevel[index] << endl;
		cout << "student Credits             " << credits[index] << endl;
		cout << "class level ordinal value   " << classLevelAsOrdinalValue[index] << endl;
		cout << classLevelAsString[index] << endl; 
		cout << endl;
	}
	*/
	// end debugging


		inputFile.close();

}

//*************************************************************************
//  FUNCTION:	  convertCredits
//  DESCRIPTION:  coverts the number of credits into a class level
//
//  INPUT:        Parameters: inputCredit- the number of credits a student has  
//
//  OUTPUT: 	  Return value: classlevel - The Class Level of a specified student
//*************************************************************************
classLevel convertCredits(int inputCredit)
{
	
	classLevel classDesignation;						// class Designation

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

//*************************************************************************
//  FUNCTION:	  convertClassLevel2String
//  DESCRIPTION:  coverts enumerated class level in string type class level 
//
//  INPUT:        Parameters: enumeratedTypeValue - enumerated value of data   
//
//  OUTPUT: 	  Return value: string, class level in plain text format 
//*************************************************************************
string convertClassLevel2String(classLevel enumeratedTypeValue)
{
	string classLevelAsString;									// class Level as String 

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

//*************************************************************************
//  FUNCTION:	  sortStudentIDDesending
//  DESCRIPTION:  Sorts student ID's by decending order IE ZZ123456 to AA123456  
//
//  INPUT:        Parameters: numOfItems - Number of student ID's 
//                            alphaNumericList - Alphanumeric list containing student ID's
//                            enumeratedTypeValue - class level in enumerated form  
//                            classLevelAsString -  class level in string form
//
//  OUTPUT: 	  Return value: None
//*************************************************************************
void sortStudentIDDesending(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[], string classLevelAsString[])
{
	int currentTop,            // Current top of unsorted list
		tryIndex,            // Position to compare value to
		minPosition;       // Position of smallest value
		
	string tempString;              // Temp value for swapping
	string tempClassLevelAsString;  // Temp value for swapping class level as string
	classLevel tempClassLevel;		// Temp value for swapping class level 


	// for each item in the list (top to bottom)
	for (currentTop = ZERO; currentTop < numOfItems - 1; currentTop++)
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

//*************************************************************************
//  FUNCTION:	  sortStudentIDAscending
//  DESCRIPTION:  Sorts student ID's by ascending order IE AA123456 to ZZ123456  
//
//  INPUT:        Parameters: numOfItems - Number of student ID's 
//                            alphaNumericList - Alphanumeric list containing student ID's
//                            enumeratedTypeValue - class level in enumerated form  
//                            classLevelAsString -  class level in string form
//
//  OUTPUT: 	  Return value: None
//*************************************************************************
void sortStudentIDAscending(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[], string classLevelAsString[])
{
	int currentTop,            // Current top of unsorted list
		tryIndex,            // Position to compare value to
		minPosition;       // Position of smallest value

	string tempString;              // Temp value for swapping
	string tempClassLevelAsString;		 // Temp value for swapping class level as string
	classLevel tempClassLevel;			 // Temp value for swapping class level


	// for each item in the list (top to bottom)
	for (currentTop = ZERO; currentTop < numOfItems - 1; currentTop++)
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

//*************************************************************************
//  FUNCTION:	  createSortedTextFile
//  DESCRIPTION:  Creates a data file containing student Id's and class levels in decending order
//
//  INPUT:        Parameters: inputFileName - text file containing studend data 
//                            numOfItems - Number of student ID's 
//                            alphaNumericList - Alphanumeric list containing student ID's
//                            enumeratedTypeValue - Class level in enumerated form
//
//  OUTPUT: 	  Return value: None
//*************************************************************************
void createSortedTextFile(int numOfItems, string alphaNumericList[], classLevel enumeratedTypeValue[])
{
	ofstream sortedList;							// output file steam name
	sortedList.open(OUTPUT_FILE_1_NAME.c_str());     // open file for writing
	char skip = ' ';

	for (int index = ZERO; index < numOfItems; index++)
	{
		//cout << "intList = " << alphaNumericList[index] << "    " << enumeratedTypeValue[index] << endl; // test line for debugging
		sortedList << alphaNumericList[index] << skip << enumeratedTypeValue[index] << endl;

	}

	sortedList.close();     // close output file


}

//*************************************************************************
//  FUNCTION:	  StudentIDNumsOnFile
//  DESCRIPTION:  Displays a list of all the Student ID numbers on file 
//
//  INPUT:        Parameters: numOfItems - Number of student ID's                           
//                            alphaNumericList - Alphanumeric list containing student ID's
//
//  OUTPUT: 	  Return value: None
//*************************************************************************
void StudentIDNumsOnFile (int numOfItems, string alphaNumericList[])
{
	//int numOfColums = MAX_COLUMNS;
	
	
	cout << "Student ID numbers on file are :" << endl;
	int index = ZERO; 

	int columns2Print;						// columns to print

	// if number of items less than Max columns
	if (numOfItems < MAX_COLUMNS)
	{
		columns2Print = numOfItems; 
	}

	else columns2Print = MAX_COLUMNS;

	// while index less than number of items
	while (index < numOfItems)
	{
		for (int columnPosition = 0; columnPosition < columns2Print; columnPosition++) // columnPosition = column position

		{
			cout << alphaNumericList[index] << "    ";
			index++;
		}
		cout << endl;
		
	} // end while


}

//*************************************************************************
//  FUNCTION:	  studentIDSearch
//  DESCRIPTION:  reads user input for student ID to look up 
//
//  INPUT:        Parameters: user input from console 
//
//  OUTPUT: 	  Return value: properlyFormatedStudentID - A properly Formated sudent ID 
//  CALLS TO      errorCheckStudentID
//*************************************************************************
string studentIDSearch()
{
	string look4StudentID;					// student Id to look up
	string properlyFormatedStudentID;		// properly formated student ID 
	bool errorDetected;						// error detection flag
	
	
	char c; 
	do
	{
		int i = ZERO;
		cout << endl;
		cout << "Enter ID number of student to find (or X to exit): ";
		cin >> look4StudentID;

		// while array not equal null terminated
		while (look4StudentID[i] != '\0')
		{
			// if character is a letter 
			if (isalpha(look4StudentID[i]))
			{
				c = look4StudentID[i];
				look4StudentID[i] = toupper(c);
				i++;
			}

			else
				i++; 
		} // end while loop
 
		errorDetected = errorCheckStudentID(look4StudentID);

	}

	while (errorDetected == true); // loop if error is detected in user input


	if (look4StudentID == "X")
	{
		cout << endl << "Exit Code recieved, Program will now exit. Thank you." << endl;
		system("PAUSE");       // Program Assignment does not specify exit code or method "Enter ID number of student to find (or X to exit):"
		exit(1);
	}

	else
	{
		properlyFormatedStudentID = look4StudentID; 
	}

	return properlyFormatedStudentID;


}

//*************************************************************************
//  FUNCTION:	  errorCheckStudentID
//  DESCRIPTION:  Checks if user input for student ID meets the specified parameters 
//
//  INPUT:        Parameters: studentIDEntered - student ID entered by user                          
//
//  OUTPUT: 	  Return value: loopUserInput - should user input be repeated 
//*************************************************************************
bool errorCheckStudentID(string studentIDEntered)
{
	bool IDEntered2short;				// ID Entered too short flag
	bool IDEntered2Long;				// ID Entered too long flag
	bool IDEnteredFit;					// ID Entered fit flag
	bool loopUserInput;					// Loop user input flag
	bool userWants2Exit;				// user wants to exit flag

	int alphaPlacementError = ZERO;		//alphabet letter placement error counter
	int integerPlacementError = ZERO;	// digit placemnet error counter
	int length;							// length of user input

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

		for (int index = ZERO; index < END_OF_LETTERS; index++)         // Used Loops for error checking 
		{
			if (!(isalpha(studentIDEntered[index])))
			{
				alphaPlacementError++;

			}

		}

		for (int index = END_OF_LETTERS; index < END_OF_NUMBERS; index++)        // used loops for error checking 
		{
			if (!(isdigit(studentIDEntered[index])))
			{
				integerPlacementError++;
			}


		}

	}


	if ((alphaPlacementError > ZERO) || (integerPlacementError > ZERO))
	{
		cout << endl;
		cout << "ERROR!" << endl;
		cout << "For Input \"" << studentIDEntered << "\", the letters and digits are not in the right places" << endl;
		cout << "ID must be exactly 8 characters long, and formatted as : XX######" << endl;
		cout << " 'X' equals Letter, '#' equals Number" << endl;

	}

	if ((IDEntered2short == true) || (IDEntered2Long == true) || (IDEnteredFit = false) || (alphaPlacementError > ZERO) || (integerPlacementError > ZERO))
	{
		loopUserInput = true; 
	}

	else if (userWants2Exit = true)
	{
		loopUserInput = false;
	}
	
	return loopUserInput;

}


//*************************************************************************
//  FUNCTION:	  runBinarySearch
//  DESCRIPTION:  runs binary search of student ID entered by user  
//
//  INPUT:        Parameters: target - item to search for 
//                            searchList - List to search for target in  
//
//  OUTPUT: 	  Return value: infoPlace - location where match was found
//*************************************************************************
int runBinarySearch(string target, string searchList[], int listSize)
{
	
	
	int infoPlace = NOT_FOUND;                   // index where target found
	int high, low, middle;

	low = ZERO;                                     // lower bound of area to search
	high = listSize - ONE;                         // upper bound of area to search

	while ((low <= high) &&                      // still places to search AND
		(infoPlace == NOT_FOUND)) {           // target not yet found

		middle = (low + high) / TWO;            // calculate middle index

		if (target < searchList[middle])      // target less than middle value
			high = middle - ONE;
		else if (target > searchList[middle]) //target more than middle value
			low = middle + ONE;
		else
			infoPlace = middle;               // target found
	}     // end while

	return infoPlace;
	



}

//*************************************************************************
//  FUNCTION:	  sendResults2Console
//  DESCRIPTION:  sends search results to console
//
//  INPUT:        Parameters: studentID - Student ID being searched for 
//                            dataLocation - index location of array where requested data is stored  
//                            alphaNumericList - list of student ID's
//                            classLevelAsString - class level as string
//
//  OUTPUT: 	  Return value: None
void sendResults2Console(string StudentID, int dataLocation, string alphaNumericList[], string classLevelAsString[])



{
	if (dataLocation != NOT_FOUND)
	{
		cout << "The student with ID " << alphaNumericList[dataLocation] << " is a " << classLevelAsString[dataLocation] << endl;
	}

	else
	{
		cout << "No student with ID " << StudentID << " was found" << endl;
	}

}