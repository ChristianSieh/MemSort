#include "sortFunctions.h"

int main(int argc, char * argv[])
{
	fstream tape;
	string name2 = "tape2.bin";
	string name3 = "tape3.bin";
	fstream tape2;
	fstream tape3;
	char *tape2name = new char[name2.length() + 1];
	char *tape3name = new char[name3.length() + 1];
	strcpy(tape2name, name2.c_str());
	strcpy(tape3name, name3.c_str());

	int length = 0;
	int highValue = 0;
	int highIndex = -1;
	int lastValue = 0;
	int calcTotal = 0;	

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
	
	splitTape(tape, tape2, tape3, argv[1], calcTotal);

	rewind(tape2, tape2name, calcTotal, length);
	rewind(tape3, tape3name, calcTotal, length);
	
	firstPass(tape2, length, lastValue, highValue, highIndex, calcTotal, tape2name);
	sort(tape2, length, lastValue, highValue, highIndex, calcTotal, tape2name);

	length = 0;

	firstPass(tape3, length, lastValue, highValue, highIndex, calcTotal, tape3name);
	sort(tape3, length, lastValue, highValue, highIndex, calcTotal, tape3name);

	combineTape(tape, tape2, tape3, argv[1], calcTotal, length);

	rewind(tape, argv[1], calcTotal, lastValue);

	length = length * 2;
	wholeTape(tape, length, calcTotal, lastValue, argv[1]);

	cout << "CalcTotal: " << calcTotal << endl;
	
	tape.close();
	tape2.close();
	tape3.close();
}
