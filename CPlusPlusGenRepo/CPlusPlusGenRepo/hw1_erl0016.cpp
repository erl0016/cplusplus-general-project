/*
Eric LaPorte
erl0016
hw1_erl0016.cpp
The program calculates the fatal amount of diet coke. use 'a.out' for execution.
Fatal dosage calculation and IO format provided by homework outline on Canvas.
*/

#include <cstdlib>
#include <iostream>
using namespace std;

int main_01()
{
	float fatalHuman;
	float fatalMouse;
	float weightHuman;
	float weightMouse;
	const float sweetnerInCoke = 0.001;

	cout << "Please input the weight of the mouse in kg" << endl;
	cin >> weightMouse;

	cout << "Please input the fatal amount of sweetner for mouse in kg" << endl;
	cin >> fatalMouse;

	cout << "Please input the weight of your dear friend in kg" << endl;
	cin >> weightHuman;

	fatalHuman = ((fatalMouse*weightHuman) / (weightMouse*sweetnerInCoke));

	cout << "The fatal amount of Coke for your feidn is: " << fatalHuman << " kg" << endl;

	system("PAUSE");

	return 0;
}