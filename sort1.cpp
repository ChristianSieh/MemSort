#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int read(fstream& tape);
void write(fstream& tape, int data);
void rewind(fstream& tape, char *arg);

int main( int argc, char * argv[])
{
	fstream tape;
	int length = 0;
	int low1;
	int low1Index;
	int low2;
	int low2Index;
	int index;
	int calcTotal = 0;
	

	cout << argv[1] << endl;

	tape.open(argv[1], ios::binary | ios::in | ios::out);

	if(!tape)
	{
		cout << "Input file failed to open" << endl;
	}

	while(!tape.eof())
	{
		int temp = read(tape);
			
		if(temp != 0)
		{
			cout << temp << endl;
		
		}
	}
}

// User defined functions
// Function to read a single element from the tape
int read(fstream& tape, int& calcTotal)
{
	calcTotal += 1;
	int data;
	tape.read(reinterpret_cast<char*>(&data), sizeof(int));
	return data;
}

// Function to write a single element to the tape
void write(fstream& tape, int data, int& calcTotal)
{
	calcTotal += 1;
	tape.write(reinterpret_cast<char*>(&data), sizeof(int));
}

// Function to rewaind the tape to the beginning
void rewind(fstream& tape, char *arg, int& calcTotal, int& index)
{
	//finish
	float temp; 	
	calcTotal += index;
	tape.close();
	tape.open(arg,ios::in | ios::out | ios::binary);
}
