#include "sortFunctions.h"

void splitTape(fstream& tape, fstream& tape2, fstream& tape3, 
	char *arg, int& calcTotal)
{
	int temp;
	int tapeSwitch = 0;
	int length = 0;

	while(!tape.eof())
	{
		temp = read(tape, calcTotal);
		length++;
		if(!tape.eof())
		{
			if(tapeSwitch % 2 == 0)
			{
				write(tape2, temp, calcTotal);
			}
			else
			{
				write(tape3, temp, calcTotal);
			}
			tapeSwitch++;
		}	
	}

	rewind(tape, arg, calcTotal, length);
}

void combineTape(fstream& tape, fstream& tape2, fstream& tape3,
	char* arg, int& calcTotal, int length)
{
	int temp2 = read(tape2, calcTotal);
	int temp3 = read(tape3, calcTotal);

	for(int i = 0; i < length * 2; i++)
	{
		if(temp2 < temp3)
		{
			write(tape, temp2, calcTotal);
			temp2 = read(tape2, calcTotal);
		}		
		else
		{
			write(tape, temp3, calcTotal);
			temp3 = read(tape3, calcTotal);
		}
	}	
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
				//cout << "High Value: " << highValue << endl;
				highIndex = length;
				//cout << "High Index: " << highIndex << endl;
			}		
		}
		temp = read(tape, calcTotal);
		//cout << "Temp: " << temp << endl;

		//cout << "Length: " << length << endl;
		length++;
		index++;
	}

	//cout << "LastValue: " << lastValue << endl;

	rewind(tape, arg, calcTotal, index);
	//cout << "Length firstPass: " << length << endl;
	length = length;
}

void sort(fstream& tape, int& length, int& lastValue, int& highValue,
	int& highIndex, int& calcTotal, char* arg)
{
	//cout << "Length sort: " << length << endl;
	int sortedIndex = length;
	int index = 0;
	int swapIndex = highIndex;

	
	while(sortedIndex != 0)
	{
		int temp = 0;
		int nextHigh = 0;
		int nextIndex;

		//cout << "Sorted Index: " << sortedIndex << endl;
		for(int i = 0; i < sortedIndex - 1; i++)
		{
			//cout << "Index: " << index << endl;
			if(i == swapIndex)
			{
				write(tape, lastValue, calcTotal);
				//cout << "Write Swap: " << lastValue << endl;
				//cout << "Swap Index: " << swapIndex << endl;
				//i++;
				//index++;
				if(lastValue > nextHigh)
				{
					nextHigh = lastValue;
					nextIndex = swapIndex;
				}
			}
			else
			{
			temp = read(tape, calcTotal);
			//cout << "Read Value: " << temp << endl;
			}
			if(temp > nextHigh)
			{
				nextHigh = temp;
				//cout << "Next High: " << nextHigh << endl;
				nextIndex = index;
				//cout << "Next Index: " << nextIndex << endl;
			}	
			index++;
		}
	
		//cout << "Write High Value: " << highValue << endl;
		//cout << "Write Index: " << index << endl;
		write(tape, highValue, calcTotal);

		if(swapIndex != sortedIndex - 2)
		{
			lastValue = temp;
		}
		//cout << "Last Value: " << lastValue << endl;
		highValue = nextHigh;
		swapIndex = nextIndex;

		sortedIndex--;		

		rewind(tape, arg, calcTotal, index);

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
