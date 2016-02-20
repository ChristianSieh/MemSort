// 
// Program: B25 Program
// Class: Computer Organization & Architecture
// Professor: Dr. Karlsson
// Date: 2/19/2016
// Author: Christian Sieh
// Usage: sort1 tape.bin
//
// This program will open the file specified with argv[1] and
// then sort the numbers. This is accomplished by first callling
// the function firstPass which will get the length of the numbers
// in the file, the last number (lastValue) from the file, the
// highest number from the file, and the index for the highest
// number. Next the program calls sort which will use these
// values to increment through the file a length number of times
// and write the highest number at the end of the file each time.
// While incrementing through the numbers in the file it will
// also write the last value in the highIndex, essentially swapping
// the high value and the last value. Once all this is done
// wholeTape is called to write out the sorted file to console out

#include "sortFunctions.h"

int main( int argc, char * argv[])
{
	fstream tape;
	int length = 0;
	int highValue = 0;
	int highIndex = -1;
	int lastValue = 0;
	
	tape.open(argv[1], ios::binary | ios::in | ios::out);

	if(!tape)
	{
		cout << "Input file failed to open" << endl;
	}

	firstPass(tape, length, lastValue, highValue, highIndex, argv[1]);

	sort(tape, length, lastValue, highValue, highIndex, argv[1]);

	wholeTape(tape, length, argv[1]);

	tape.close();
}
