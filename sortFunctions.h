//This file contains the prototypes for sortFunctions.cpp to be used
//with sort1.cpp and sort2.cpp
//
//Author: Christian Sieh

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstring>

using namespace std;

void splitTape(fstream& tape, fstream& tape2, fstream& tape3, 
	char *arg);
void combineTape(fstream& tape, fstream& tape2, fstream& tape3,
	char* arg, int length);
void firstPass(fstream& tape, int& length, int& lastValue, int& highValue, 
	int& highIndex, char* arg);
void sort(fstream& tape, int& length, int& lastValue, int& highValue,
	int highIndex, char* arg);
void wholeTape(fstream& tape, int& length, char* arg);
int read(fstream& tape);
void write(fstream& tape, int data);
void rewind(fstream& tape, char *arg, int& index);
