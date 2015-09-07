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

void ProgramDescription();
void readDataFile1(string inputFileName, string studentID[], char studentClassLevel[], int credits[]);

void StoreUndergradData (string[], int[]);
void covertCredits(int inputCredit);

const int MAX_ENTRIES = 10; // Max number of student profiles that can be stored
const int FRESHMAN_BOUNDARY = 32; 
const int SOPHOMORE_BOUNDARY = 63;
const int JUNIOR_BOUNDARY = 95;
const int SENIOR_BOUNDARY = 95;


const string FILE_1_NAME = "CREDITS.txt"; // File name for input file

int main()
{
	string StudentIDList[MAX_ENTRIES];
	char ClassLevelList[MAX_ENTRIES];
	int CreditsList[MAX_ENTRIES];

	
	ProgramDescription();
	readDataFile1(FILE_1_NAME, StudentIDList, ClassLevelList, CreditsList);




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
void readDataFile1(string inputFileName, string studentID[], char studentClassLevel[], int credits[])
{
	ifstream inputFile;                      // input file stream variable
	bool fileOpenSuccess;

	string tempStudentID;
	char tempStudentClassLevel;
	int tempCredits;

	int studentIndex = 0;
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
			studentIndex++;
		}

		 if (studentIndex >= MAX_ENTRIES)
		{
			cout << "Alert! Maximum number of Entries (" << MAX_ENTRIES << ") has been reached" << endl << endl;
		}



	}


	
	for (int index = 0; index < studentIndex; index++)
	{
		cout << "student id        " << studentID[index] << endl;
		cout << "class Level       " << studentClassLevel[index] << endl;
		cout << "student Credits   " << credits[index] << endl;
		cout << endl;
	}


		inputFile.close();

}
void covertCredits(int inputCredit)
{
	enum classLevel { Freshman, Sophomore, Junior, Senior };

	classLevel classDesignation; 

	if (inputCredit < FRESHMAN_BOUNDARY)
	{
		classDesignation = Freshman;
	}


}