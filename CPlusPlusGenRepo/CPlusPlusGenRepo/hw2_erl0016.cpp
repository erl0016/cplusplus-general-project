/*
Eric LaPorte
erl0016
hw2_erl0016.cpp
26 Feb 2019
The program calculates the monthly payments for a loan, given an annual interest rate and monthly payment size.
Loan and payment calculations and IO format provided by homework outline on Canvas.
Compile using filename and 'hw2_erl0016.out' for execution.
Referenced c++ api site to use precision formating method.
*/

#include <cstdlib>
#include <cmath>
#include <string> //https://stackoverflow.com/questions/332111/how-do-i-convert-a-double-into-a-string-in-c
#include <iostream>
#include <iomanip> //https://stackoverflow.com/questions/5907031/printing-the-correct-number-of-decimal-points-with-cout
using namespace std;

string formatCurrentBalance(double cb);

int main_02()
{
	double loanAmount;
	double interestRate;
	double monthlyPayment;

	int month = 0;
	double currentBalance = 0;
	//total payment made per month
	double currentPayment = 0;
	double ratePerMonth = 0;
	//what is owed on the interest
	double currentInterest = 0;
	//what is owed on the debt itself
	double currentPrincipal = 0;
	//the total interest paid on the loan
	double totalInterest = 0;

	cout << "Loan Amount: ";
	cin >> loanAmount;

	cout << "Interest Rate (% per year): ";
	cin >> interestRate;

	cout << "Monthly Payments: ";
	cin >> monthlyPayment;

	ratePerMonth = interestRate / 12;
	currentBalance = loanAmount;
	currentPayment = monthlyPayment;

	//format output table of values
	cout << endl << "***************************************************************" << endl;
	cout << "\tAmortization Table" << endl;
	cout << "***************************************************************" << endl;
	//column headers
	cout << "Month\tBalance \tPayment\tRate\tInterest\tPrincipal" << endl;

	//computes values for first iteration
	if (currentBalance == loanAmount)
	{
		currentInterest = currentBalance * (ratePerMonth * 0.01);
		currentPrincipal = monthlyPayment - currentInterest;
		cout << fixed << setprecision(2) << month << "\t$" << currentBalance << "\tN/A\tN/A\tN/A\tN/A" << endl;
		month++;
	}

	//calculates values for majority of iterations
	while (currentBalance > 0)
	{
		currentInterest = currentBalance * (ratePerMonth * 0.01);
		currentPrincipal = currentPayment - currentInterest;
		currentBalance = currentBalance - currentPrincipal;
		cout << fixed << setprecision(2) << month << "\t$" << currentBalance << "\t$" << currentPayment
			<< "\t" << ratePerMonth << "\t$" << currentInterest << "\t$" << currentPrincipal << "\n";
		month++;
		totalInterest += currentInterest;

		//handles when the current balance is less than the current payment
		if (currentBalance < currentPayment)
		{
			currentInterest = currentBalance * (ratePerMonth * 0.01);
			currentPrincipal = currentPayment - currentInterest;
			currentBalance = currentBalance - currentPrincipal;
			if (currentBalance < 0)
			{
				currentBalance = 0;
			}
			cout << fixed << setprecision(2) << month << "\t$" << currentBalance << "\t$" << currentPayment
				<< "\t" << ratePerMonth << "\t$" << currentInterest << "\t$" << currentPrincipal << "\n";
			totalInterest += currentInterest;
		}

		if (currentPayment < currentInterest)
		{
			break;
		}
	}

	cout << "***************************************************************\n";
	cout << "\nIt takes " << month << " months to pay off the loan.\n"
		<< "Total interest paid is: $" << totalInterest;

	system("PAUSE");
	return 0;
}

/* Allows for formatting control over balance values, 
   depending on how long the final output is.
   Ref: https://stackoverflow.com/questions/332111/how-do-i-convert-a-double-into-a-string-in-c
*/ 
string formatCurrentBalance(double cb)
{
	string balance = to_string(cb);
	int pntIndex = balance.find("."); //http://www.cplusplus.com/reference/string/string/

	if (balance.length() <= 7)
	{
		int tabNeeded = 8 - balance.length();
		for (int i = 8; i >= tabNeeded; i--)
		{
			balance + " ";
		}
	}

	return balance;
}