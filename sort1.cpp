#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

void firstPass(fstream& tape, int& length, int& lastValue, int& highValue, 
	int& highIndex, int& calcTotal, char* arg);
void sort(fstream& tape, int& length, int& lastValue, int& highValue,
	int& highIndex, int& calcTotal, char* arg);
void wholeTape(fstream& tape, int& length, int& calcTotal, int& index, char* arg);
int read(fstream& tape, int& calcTotal);
void write(fstream& tape, int data, int& calcTotal);
void rewind(fstream& tape, char *arg, int& calcTotal, int& index);

int main( int argc, char * argv[])
{
	fstream tape;
	int length = 0;
	int highValue = 0;
	int highIndex = -1;
	int lastValue = 0;
	int calcTotal = 0;

	cout << argv[1] << endl;

	tape.open(argv[1], ios::binary | ios::in | ios::out);

	if(!tape)
	{
		cout << "Input file failed to open" << endl;
	}

	firstPass(tape, length, lastValue, highValue, highIndex, calcTotal, argv[1]);

	sort(tape, length, lastValue, highValue, highIndex, calcTotal, argv[1]);

	cout << "Calculation Total: " << calcTotal << endl;

	for(int i = 0; i < length; i++)
	{
		int temp = read(tape, calcTotal);
		cout << "Final: " << temp << endl;
		write(tape, temp, calcTotal);	
	}

	tape.close();
}

void firstPass(fstream& tape, int& length, int& lastValue, int& highValue, 
	int& highIndex, int& calcTotal, char *arg)
{
	int temp = read(tape, calcTotal);
	int index = 0;
	while(!tape.eof())
	{
		lastValue = temp;
		if(!tape.eof())
		{
			if(temp > highValue)
			{
				highValue = temp;
				cout << "High Value: " << highValue << endl;
				highIndex = length;
				cout << "High Index: " << highIndex << endl;
			}		
		}
		temp = read(tape, calcTotal);
		cout << "Temp: " << temp << endl;

		cout << "Length: " << length << endl;
		length++;
		index++;
	}

	cout << "LastValue: " << lastValue << endl;

	rewind(tape, arg, calcTotal, index);
	cout << "Length firstPass: " << length << endl;
	length = length;
}

void sort(fstream& tape, int& length, int& lastValue, int& highValue,
	int& highIndex, int& calcTotal, char* arg)
{
	cout << "Length sort: " << length << endl;
	int sortedIndex = length;
	int index = 0;
	int swapIndex = highIndex;
	
	while(sortedIndex != 0)
	{
		int temp = 0;
		cout << "Sorted Index: " << sortedIndex << endl;
		for(int i = 0; i < sortedIndex - 1; i++)
		{	
			if(i == swapIndex)
			{
				write(tape, lastValue, calcTotal);
				cout << "Write Swap: " << lastValue << endl;
				i++;
				index++;
				if(lastValue > highValue)
				{
					highValue = lastValue;
					highIndex = swapIndex;
				}
			}


			temp = read(tape, calcTotal);
			cout << "Read Value: " << temp << endl;

			if(temp > highValue)
			{
				highValue = temp;
				cout << "High Value: " << highValue << endl;
				highIndex = index;
				cout << "High Index: " << highIndex << endl;
			}		
			
			index++;
		}
	
		lastValue = temp;
		swapIndex = highIndex;
		cout << "Last Value: " << lastValue << endl;
		cout << "Write High Value: " << highValue << endl;
		write(tape, highValue, calcTotal);

		highValue = 0;
		highIndex = -1;
		sortedIndex--;		

		rewind(tape, arg, calcTotal, index);

		wholeTape(tape, length, calcTotal, index, arg);
	}

}

void wholeTape(fstream& tape, int& length, int& calcTotal, int& index, char* arg)
{
	int temp;
	cout << "Whole tape: ";
	for(int i = 0; i < length; i++)
	{
		temp = read(tape, calcTotal);			
		cout << temp << " ";
	}
	cout << endl;	
	rewind(tape, arg, calcTotal, index);		
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
	calcTotal += ceil((float)index/8);
	tape.close();
	tape.open(arg,ios::in | ios::out | ios::binary);
	index = 0;
}
