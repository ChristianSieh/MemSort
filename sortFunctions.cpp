#include "sortFunctions.h"

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
		wholeTape(tape, length, calcTotal, index, arg);		
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