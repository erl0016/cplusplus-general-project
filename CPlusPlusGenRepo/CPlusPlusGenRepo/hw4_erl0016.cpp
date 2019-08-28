/*
Eric LaPorte
erl0016
hw4_erl0016.cpp
12 Apr 2019
The program takes two input files full of numbers, compiles them into a single array, sorts them in order and places them in an output file.
Functions and IO format provided by homework outline on Canvas.
Compile using filename and 'hw4_erl0016.out' for execution.
Merge sort source: application of merge sort algorithm learned from COMP 2210.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdio.h>
using namespace std;

int readFile(int inputArray[], ifstream& infstrm);
int sort(int inArray1[], int inArray2[], int inArray1Size, int inArray2Size, int outArray[]);
void writeFile(int outArray[], int outArraySize, string fileName);

const int MAX_SIZE = 100;

int main04()
{
	ifstream infstrm;
	string fileName1;
	string fileName2;
	int inArray1[MAX_SIZE] = { 0 };
	int inArray2[MAX_SIZE] = { 0 };
	int outArray[MAX_SIZE * 2] = { 0 };
	int inArray1Size = 0;
	int inArray2Size = 0;
	int outArraySize = 0;
	string outputName = "output.txt";
	string fileError = "Encountered an error while attempting to open the input file.";
	
	cout << "*** Welcome to Eric LaPorte's sorting program ***" << endl << "Enter the first input file name: ";
	cin >> fileName1;

	infstrm.open((char*)fileName1.c_str());
	if (infstrm.fail())
	{
		cout << fileError << endl;
		exit(1);
	}

	inArray1Size = readFile(inArray1, infstrm);
	cout << "The list of " << inArray1Size << " numbers in file " << fileName1 << " is:" << endl;
	for (int i = 0; i < inArray1Size; i++)
	{
		cout << inArray1[i] << endl;
	}
	infstrm.close();

	cout << endl << "Enter the second input file name: ";
	cin >> fileName2;
	infstrm.open((char*)fileName2.c_str());
	if (infstrm.fail())
	{
		cout << fileError << endl;
		exit(1);
	}

	inArray2Size = readFile(inArray2, infstrm);
	cout << "The list of " << inArray2Size << " numbers in file " << fileName2 << " is:" << endl;
	for (int i = 0; i < inArray2Size; i++)
	{
		cout << inArray2[i] << endl;
	}
	infstrm.close();

	outArraySize = sort(inArray1, inArray2, inArray1Size, inArray2Size, outArray);

	cout << endl << "The sorted list of " << outArraySize << " numbers is: ";
	for (int i = 0; i < outArraySize; i++)
	{
		cout << outArray[i] << " ";
	}

	// output the complete sorted output array in a line.
	writeFile(outArray, outArraySize, outputName);

	return 0;
}

// reads the inputs of the file and pulls them into an array.
int readFile(int inputArray[], ifstream& infstrm)
{
	int index = 0;

	infstrm >> inputArray[index];
	while (!infstrm.eof())
	{
		index++;
		infstrm >> inputArray[index];
	}

	// this part adds the last entry in the file before returning the size.
	infstrm >> inputArray[index];
	index++;

	return index;
}

// sorts the input arrays and produces a sorted output array.
int sort(int inArray1[], int inArray2[], int inArray1Size, int inArray2Size, int outArray[])
{
	int arraySize = inArray1Size + inArray2Size;

	// pulls values from first input array into output array.
	for (int i = 0; i < inArray1Size; i++)
	{
		outArray[i] = inArray1[i];
	}

	// pulls from second input array into output array.
	for (int j = 0; j < inArray2Size; j++)
	{
		outArray[inArray1Size + j] = inArray2[j];
	}

	// setup to check the relation of two adjecent values and swap if they are not in order.
	int t = 0;
	for (int i = 0; i < arraySize; i++)
	{
		for (int j = i + 1; j < arraySize; j++)
		{
			if (outArray[j] < outArray[i])
			{
				t = outArray[i];
				outArray[i] = outArray[j];
				outArray[j] = t;
			}
		}
	}

	return arraySize;
}

// writes the output array to the output file.
void writeFile(int outArray[], int outArraySize, string fileName)
{
	ofstream outfstrm;
	outfstrm.open((char*)fileName.c_str());

	for (int i = 0; i < outArraySize; i++)
	{
		outfstrm << outArray[i] << endl;
	}
	outfstrm.close();
}
