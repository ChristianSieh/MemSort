#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char * argv[])
{
	// Make sure we a commandline argument for file-name
	if ( argc != 2 )
	{   
		/* We print argv[0] assuming it is the program name */
		printf( "usage: %s <n>\n", argv[0] );
		printf( "    n:   number of elements in list\n");
		return(0);
	}

	vector<int> randomIndex;

	int n = strtol(argv[1], NULL, 10);

	for(int i = 1; i <= n; i++)
	{
		randomIndex.push_back(i);
	}

	random_shuffle(randomIndex.begin(), randomIndex.end());

	ofstream tape ("tape.bin",ios::out | ios::trunc | ios::binary );

	// Write the output data   
	if(!tape)
	{
		cout << "Can't open file" << endl;
	}

	cout << "Writing to file" << endl;
	for(int i = 0; i < n; i++)
	{
	        tape.write(reinterpret_cast<char*>(&randomIndex[i]), sizeof(int));	
	}

	tape.close();
}
