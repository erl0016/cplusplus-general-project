/*
Eric LaPorte
erl0016
hw3_erl0016.cpp
25 Mar 2019
The program simulates a dueling match between three individuals in a bid to become the "Greatest Puzzle-Solver of All Time".
Functions and IO format provided by homework outline on Canvas.
Compile using filename and 'hw3_erl0016.out' for execution.
Referenced c++ api site to use precision formating method.
*/

#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <ctime>
using namespace std;

bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
void Aaron_shoots1(bool& B_alive, bool& C_alive);
void Bob_shoots1(bool& A_alive, bool& C_alive);
void Charlie_shoots1(bool& A_alive, bool& B_alive);
void Aaron_shoots2(bool& B_alive, bool& C_alive);
double duelsWonPercentage(int duelsWon, int duelsTotal);
void getUserResponse();
void getStrategyComparison(int duelsWonStratOne, int duelsWonStratTwo);
bool isTargetHit(char shooter, int accuracy);
int computeStratOne();
int computeStratTwo();

void test_at_least_two_alive();

int main03()
{
	int duelsAaronWonStratOne = 0;
	int duelsAaronWonStratTwo = 0;
	int duelsBobWon = 0;
	int duelsCharlieWon = 0;

	srand(time(0));

	cout << "*** Welcome to the Duel Simulator ***" << endl;
	test_at_least_two_alive();
	getUserResponse();

	cout << "Ready to test strategy 1 (run 10000 times):" << endl;
	// compute strategy 1 here
	getUserResponse();
	duelsAaronWonStratOne = computeStratOne();
	// output results of strategy 1 simulation
	cout << endl;

	cout << "Ready to test strategy 2 (run 10000 times):" << endl;
	// compute strategy 2 here
	getUserResponse();
	duelsAaronWonStratTwo = computeStratTwo();
	// output results of strategy 2 simulation.
	cout << endl;

	// compare strategy 1 to strategy 2
	getStrategyComparison(duelsAaronWonStratOne, duelsAaronWonStratTwo);

	//test end line
	cout << "END PROGRAM EXECUTION";
	getUserResponse();

	return 0;
}

//Checks if at least two are still alive or not.
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive)
{
	bool isTwoPlusAlive = false;
	if ((A_alive && B_alive) || (B_alive && C_alive) || (A_alive && C_alive) || (A_alive && B_alive && C_alive))
	{
		isTwoPlusAlive = true;
	}
	return isTwoPlusAlive;
}

//Determines who Aaron shoots, following the first strategy.
void Aaron_shoots1(bool& B_alive, bool& C_alive)
{
	const int aaronAccuracy = 33;
	bool isShot = isTargetHit('a', aaronAccuracy);
	if (isShot && C_alive)
	{
		C_alive = false;
	}
	else if (isShot && B_alive)
	{
		B_alive = false;
	}
}

//Determines who Bob shoots.
void Bob_shoots1(bool& A_alive, bool& C_alive)
{
	const int bobAccuracy = 50;
	bool isShot = isTargetHit('b', bobAccuracy);
	if (isShot && C_alive)
	{
		C_alive = false;
	}
	else if (isShot && A_alive)
	{
		A_alive = false;
	}
}

//Determines who Charlie shoots.
void Charlie_shoots1(bool& A_alive, bool& B_alive)
{
	const int charlieAccuracy = 100;
	bool isShot = isTargetHit('c', charlieAccuracy);
	if (isShot && B_alive)
	{
		B_alive = false;
	}
	else if (isShot && A_alive)
	{
		A_alive = false;
	}
}

//Determines who Aaron shoots, following the second strategy.
void Aaron_shoots2(bool& B_alive, bool& C_alive)
{
	const int aaronAccuracy = 33;
	bool isShot = isTargetHit('a', aaronAccuracy);
	if (isShot && B_alive && C_alive)
	{
		//miss the shot intentionally.
	}
	else if (isShot && C_alive)
	{
		C_alive = false;
	}
	else if (isShot && B_alive)
	{
		B_alive = false;
	}
}

//Formats the number of duels won as a percentage.
double duelsWonPercentage(int duelsWon, int duelsTotal)
{
	double percentage = 0;
	percentage = (duelsWon / duelsTotal) * 100;
	return percentage;
}

//Test driver for at_least_two_alive() function.
void test_at_least_two_alive()
{
	cout << "Unit Testing 1: Function - at_least_two_alive()\n";

	cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(true, true, true));
	cout << "\tCase passed ...\n";

	cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
	assert(true == at_least_two_alive(false, true, true));
	cout << "\tCase passed ...\n";

	cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
	assert(true == at_least_two_alive(true, false, true));
	cout << "\tCase passed ...\n";

	cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
	assert(true == at_least_two_alive(true, true, false));
	cout << "\tCase passed ...\n";

	cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
	assert(false == at_least_two_alive(false, false, true));
	cout << "\tCase passed ...\n";

	cout << "\tCase 6: Aaron alive, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(true, false, false));
	cout << "\tCase passed ...\n";

	cout << "\tCase 7: Aaron dead, Bob alive, Charlie dead\n";
	assert(false == at_least_two_alive(false, true, false));
	cout << "\tCase passed ...\n";

	cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
	assert(false == at_least_two_alive(false, false, false));
	cout << "\tCase passed ...\n";
}

//Refactored method to handle user input for results.
void getUserResponse()
{
	cout << "Press Enter to continue...";
	cin.get();
}

//Show which strategy is better for Aaron.
void getStrategyComparison(int stratOne, int stratTwo)
{
	if (stratTwo > stratOne)
	{
		cout << "Strategy 2 is better than strategy 1." << endl;
	}
	else
	{
		cout << "Something went wrong..." << endl;
	}
}

//Determines if a shot hits a target or not.
bool isTargetHit(char shooter, int accuracy)
{
	bool isHit = false;

	int hitProb = rand() % 100;
	switch (shooter)
	{
	case 'a':
	{
		if (hitProb <= accuracy)
		{
			isHit = true;
		}
		break;
	}
	case 'b':
	{
		if (hitProb <= accuracy)
		{
			isHit = true;
		}
		break;
	}
	case 'c':
	{
		if (hitProb <= accuracy)
		{
			isHit = true;
		}
		break;
	}
	}

	return isHit;
}

//Compute all needed info for Strategy 1.
int computeStratOne()
{
	int duelsAaronWon = 0;
	int duelsBobWon = 0;
	int duelsCharlieWon = 0;
	int duelsTotal = 10000;
	bool isAaronAlive = true;
	bool isBobAlive = true;
	bool isCharlieAlive = true;

	int i = 0;
	while (i <= 10000)
	{
		//Aaron will shot if there is at least himself and someone else alive.
		if (at_least_two_alive(isAaronAlive, isBobAlive, isCharlieAlive) && isAaronAlive)
		{
			Aaron_shoots1(isBobAlive, isCharlieAlive);
			//If Aaron shoots someone and no one else is alive, then he wins the duel.
			if (!at_least_two_alive(isAaronAlive, isBobAlive, isCharlieAlive) && isAaronAlive)
			{
				duelsAaronWon++;
				i++;
				isAaronAlive = true;
				isBobAlive = true;
				isCharlieAlive = true;
				break;
			}
		}
		//Bob will shot if there is at least himself and someone else alive.
		if (at_least_two_alive(isAaronAlive, isBobAlive, isCharlieAlive) && isBobAlive)
		{
			Bob_shoots1(isAaronAlive, isCharlieAlive);
			//If Bob shoots someone and no one else is alive, then he wins the duel.
			if (!at_least_two_alive(isAaronAlive, isBobAlive, isCharlieAlive) && isBobAlive)
			{
				duelsBobWon++;
				i++;
				isAaronAlive = true;
				isBobAlive = true;
				isCharlieAlive = true;
				break;
			}
		}
		//Charlie will shot if there is at least himself and someone else alive.
		if (at_least_two_alive(isAaronAlive, isBobAlive, isCharlieAlive) && isCharlieAlive)
		{
			Charlie_shoots1(isAaronAlive, isBobAlive);
			//If Charlie shoots someone and no one else is alive, then he wins the duel.
			if (!at_least_two_alive(isAaronAlive, isBobAlive, isCharlieAlive) && isCharlieAlive)
			{
				duelsCharlieWon++;
				i++;
				isAaronAlive = true;
				isBobAlive = true;
				isCharlieAlive = true;
				break;
			}
		}

		i++;
	}

	cout << "Aaron won " << duelsAaronWon << "/10000 duels or " << duelsWonPercentage(duelsAaronWon, duelsTotal) << "%" << endl;
	cout << "Bob won " << duelsBobWon << "/10000 duels or " << duelsWonPercentage(duelsBobWon, duelsTotal) << "%" << endl;
	cout << "Charlie won " << duelsCharlieWon << "/10000 duels or " << duelsWonPercentage(duelsCharlieWon, duelsTotal) << "%" << endl;
	return duelsAaronWon;
}

//Compute all needed info for Strategy 2.
int computeStratTwo()
{
	int duelsAaronWon = 0;
	int duelsBobWon = 0;
	int duelsCharlieWon = 0;
	int duelsTotal = 10000;

	cout << "Aaron won " << duelsAaronWon << "/10000 duels or " << duelsWonPercentage(duelsAaronWon, duelsTotal) << "%" << endl;
	cout << "Bob won " << duelsBobWon << "/10000 duels or " << duelsWonPercentage(duelsBobWon, duelsTotal) << "%" << endl;
	cout << "Charlie won " << duelsCharlieWon << "/10000 duels or " << duelsWonPercentage(duelsCharlieWon, duelsTotal) << "%" << endl;
	return duelsAaronWon;
}