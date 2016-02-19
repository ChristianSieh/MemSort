#include "sortFunctions.h"

int main( int argc, char * argv[])
{
	fstream tape;
	int length = 0;
	int highValue = 0;
	int highIndex = -1;
	int lastValue = 0;
	int calcTotal = 0;
	
	tape.open(argv[1], ios::binary | ios::in | ios::out);

	if(!tape)
	{
		cout << "Input file failed to open" << endl;
	}

	firstPass(tape, length, lastValue, highValue, highIndex, calcTotal, argv[1]);

	sort(tape, length, lastValue, highValue, highIndex, calcTotal, argv[1]);

	wholeTape(tape, length, calcTotal, lastValue, argv[1]);

	cout << "Calculation Total: " << calcTotal << endl;

	tape.close();
}
