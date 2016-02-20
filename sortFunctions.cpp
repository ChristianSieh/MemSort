//This file contains the function definitions for sortFucntions.h

#include "sortFunctions.h"

//Author: Christian Sieh
//This function will take tape and put half of the numbers in tape2
//and the other half of the numbers in tape3. It will then
//rewind tape so we are at the beginning of the file
void splitTape(fstream& tape, fstream& tape2, fstream& tape3, char *arg)
{
	int temp;
	int tapeSwitch = 0;
	int length = 0;

	//Read all of the numbers from tape
	while(!tape.eof())
	{
		temp = read(tape);
		length++;
		if(!tape.eof())
		{
			//This if/else and mod is make
			//to switch writing every other number
			//to each file
			if(tapeSwitch % 2 == 0)
			{
				write(tape2, temp);
			}
			else
			{
				write(tape3, temp);
			}
			tapeSwitch++;
		}	
	}

	rewind(tape, arg, length);
}

//Author: Christian Sieh
//This function will read from tape2 and tape3 and write
//out the values in ascending order to tape. This will
//end up giving us a sorted array of numbers on tape.
void combineTape(fstream& tape, fstream& tape2, fstream& tape3,
	char* arg, int length)
{
	int temp2 = read(tape2);
	int temp3 = read(tape3);

	//Since the total number of numbers is split in
	//half we do length * 2 to put all the files
	//back into the main tape
	for(int i = 0; i < length * 2; i++)
	{
		//If temp2 is smaller then we want to write
		//it to tape
		if(temp2 < temp3)
		{
			write(tape, temp2);
			temp2 = read(tape2);
		}
		//Else if temp3 is smaller then we want to
		//write it to the tape		
		else
		{
			write(tape, temp3);
			temp3 = read(tape3);
		}
	}	
}

// Author: Christian Sieh
// This function is called before the sort function. This function
// gets the last value, the high value, the high value's index,
// and the length of the file which are all needed before we can
// begin sorting
void firstPass(fstream& tape, int& length, int& lastValue, int& highValue, 
	int& highIndex, char *arg)
{
	int temp = read(tape);
	int index = 0;
	while(!tape.eof())
	{
		lastValue = temp;
		if(!tape.eof())
		{
			if(temp > highValue)
			{
				highValue = temp;
				highIndex = length;
			}		
		}
		temp = read(tape);

		length++;
		index++;
	}

	rewind(tape, arg, index);
	length = length;
}

//Author: Christian Sieh
//This is the main function that will do all of the sorting.
//It will take in a file, the length of numbers in the file, the
//last value in the list of numbers, the highest value, the highest
//value's index, and the name of the tape. This function starts
//by assigning sortedIndex which we will use to keep track of how
//many numbers we have written. It starts at length and then will
//decrement once a length number of numbers are written which is
//how we will know to stop looping. Index is used to keep track of
//how far we have read or write into the file. This is used so we
//can get the next swapIndex and it's nicer to look at instead
//of putting everything in another for loop. The for loop will 
//iterate through the list of numbers, if the swapIndex is found
//then it will write out the lastValue and then the if statement
//after the write is used in case the lastValue we just wrote would
//end up being the highValue for this pass through the file. Else
//if it wasn't the swap index we will read the next number and then
//if the next number is larger then the current high number for this
//read we will set that as the new high number. Once we are up to
//sortedIndex - 1 through the file we then write the high number.
//The if statement after the write is to stop the function from
//accidently creating two of the same number which in turn would
//break the sort. Once sortedIndex is 0 then we have sorted all the
//numbers in the file.
void sort(fstream& tape, int& length, int& lastValue, int& highValue,
	int swapIndex, char* arg)
{
	int sortedIndex = length;
	int index = 0;

	//While the list isn't sorted	
	while(sortedIndex != 0)
	{
		int temp = 0;
		int nextHigh = 0;
		int nextIndex;

		//Read or write up to spot before where
		//we need to write the high number
		for(int i = 0; i < sortedIndex - 1; i++)
		{
			//If it's the swap index then
			//we need to write the lasValue
			if(i == swapIndex)
			{
				write(tape, lastValue);
				//If the lastValue will be the
				//highValue for this pass
				if(lastValue > nextHigh)
				{
					nextHigh = lastValue;
					nextIndex = swapIndex;
				}
			}
			//Read the next number
			else
			{
				temp = read(tape);
			}
			//If the number we just read is the new
			//highest value then store it
			if(temp > nextHigh)
			{
				nextHigh = temp;
				nextIndex = index;
			}	
			index++;
		}

		//Write the highest value at then end	
		write(tape, highValue);

		//If the swapIndex IS equal to the sortedIndex
		// - 2 then the swapValue and the lastValue will
		// be the same and we will end up with two of the
		// same number which would break the sort so this
		// is to avoid that problem.
		if(swapIndex != sortedIndex - 2)
		{
			lastValue = temp;
		}

		//Set up the high value and swapIndex
		//for the next pass		
		highValue = nextHigh;
		swapIndex = nextIndex;

		sortedIndex--;		
		
		//Rewind so we are back at the beginning of the file
		rewind(tape, arg, index);
	}
}

// Author: Christian Sieh
// This function will read and cout values up to length
// for the file name specified
void wholeTape(fstream& tape, int& length, char* arg)
{
	int temp;
	cout << "Final: ";
	//Read and print out the numbers
	for(int i = 0; i < length; i++)
	{
		temp = read(tape);			
		cout << temp << " ";
	}
	cout << endl;	
}

// Author: Dr. Karlsson
// Function to read a single element from the tape
int read(fstream& tape)
{
	int data;
	tape.read(reinterpret_cast<char*>(&data), sizeof(int));
	return data;
}

// Author: Dr. Karlsson
// Function to write a single element to the tape
void write(fstream& tape, int data)
{
	tape.write(reinterpret_cast<char*>(&data), sizeof(int));
}

// Dr. Karlsson
// Function to rewaind the tape to the beginning
void rewind(fstream& tape, char *arg, int& index)
{
	tape.close();
	tape.open(arg,ios::in | ios::out | ios::binary);
	index = 0;
}
