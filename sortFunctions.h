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


