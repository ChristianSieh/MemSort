// 
// Program: B25 Program
// Class: Computer Organization & Architecture
// Professor: Dr. Karlsson
// Date: 2/19/2016
// Author: Christian Sieh
// Usage: sort2 tape.bin
//
// This program will open the file specified with argv[1] and
// then sort the numbers. This is accomplished by first
// opening two other tapes tape2.bin and tape3.bin. Then the
// function splitTape is called to take the numbers in tape
// and write half of them to tape2 and the other half to tape3.
// After that firstPass and sort are called on tape2 and then
// on tape3 to end up with two sorted lists in each tape.
// Finally, these two tapes are combined back together
// in tape and in order to give us a fianl sorted
// file of numbers.

#include "sortFunctions.h"

int main(int argc, char * argv[])
{
	fstream tape;
	string name2 = "tape2.bin";
	string name3 = "tape3.bin";
	fstream tape2;
	fstream tape3;
	// The next 4 lines are used to convert the
	// string names into char * so they can be
	// passed into the firstPass and sort functions
	char *tape2name = new char[name2.length() + 1];
	char *tape3name = new char[name3.length() + 1];
	strcpy(tape2name, name2.c_str());
	strcpy(tape3name, name3.c_str());

	int length = 0;
	int highValue = 0;
	int highIndex = -1;
	int lastValue = 0;

	//Open all the tapes
	tape.open(argv[1], ios::binary | ios::in | ios::out);
	tape2.open(tape2name, ios::binary | ios::in | ios::out | ios::trunc);
	tape3.open(tape3name, ios::binary | ios::in | ios::out | ios::trunc);	

	if(!tape)
	{
		cout << "Input file failed to open" << endl;
	}

	if(!tape2)
	{
		cout << "Tape 2 failed to open" << endl;
	}

	if(!tape3)
	{
		cout << "Tape 3 failed to open" << endl;
	}
	
	//Split tape into two halves, one in tape2, and the
	//other in tape3
	splitTape(tape, tape2, tape3, argv[1]);

	//Rewind tape2 and tape3 now that they have been
	//written to
	rewind(tape2, tape2name, lastValue);
	rewind(tape3, tape3name, lastValue);
	
	//Sort tape2
	firstPass(tape2, length, lastValue, highValue, highIndex, tape2name);
	sort(tape2, length, lastValue, highValue, highIndex, tape2name);

	//Reset the length for sort() of tape3 will be twice as long
	//as it needs to be
	length = 0;

	//Sort tape3
	firstPass(tape3, length, lastValue, highValue, highIndex, tape3name);
	sort(tape3, length, lastValue, highValue, highIndex, tape3name);

	//Combine tape2 and tape3 back together into tape
	combineTape(tape, tape2, tape3, argv[1], length);

	//Rewind tape so we can read the values from it
	rewind(tape, argv[1], lastValue);

	//Write out he final sorted tape
	length = length * 2;
	wholeTape(tape, length, argv[1]);
	
	tape.close();
	tape2.close();
	tape3.close();
}
