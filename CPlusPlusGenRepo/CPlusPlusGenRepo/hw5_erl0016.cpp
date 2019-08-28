/*
Eric LaPorte
erl0016
hw5_erl0016.cpp
26 April 2019
The program a quiz of trivia questions in a linked list data structure.
Functions and IO format provided by homework outline on Canvas.
*Jake Galanopoulos helped me figure out the design outline for how to add a node to the list.*
Compile using filename and 'hw5_erl0016.out' for execution.
*/

//#define UNIT_TESTING //used for debugging purposes
#include <cstdlib>
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

class TriviaList
{
	struct TriviaNode
	{
		string question;
		string answer;
		int pts;
		TriviaNode* next;
	};

	public: 

		TriviaNode* head;
		TriviaNode* tail;

		// Constructor for TrivaiNode object.
		TriviaList()
		{
			head = NULL;
			tail = NULL;
		}

		// Adds a new node to the trivia list.
		void addTriviaNode(string questionIn, string answerIn, int ptsIn)
		{
			if (head == NULL)
			{
				TriviaNode* node = new TriviaNode();
				node->question = questionIn;
				node->answer = answerIn;
				node->pts = ptsIn;
				node->next = NULL;
				head = node;
				tail = node;
				return;
			}

			TriviaNode* node = new TriviaNode();
			node->question = questionIn;
			node->answer = answerIn;
			node->pts = ptsIn;
			tail->next = node;
			tail = node;
			node->next = NULL;
		}

		// Runs actual trivia after it has been built.
		void runQuiz(TriviaList list)
		{
			string userAnswer;
			int totalPoints = 0;
			TriviaNode* node = list.head;

			// iterates through each trivia node per question.
			while (list.tail != NULL)
			{
				cout << node->question << endl;
				cin >> userAnswer;
				if (userAnswer.compare(node->answer) == 0)
				{
					totalPoints += node->pts;
					cout << "Your answer is correct. You recieved " << node->pts << " points." << endl;
					cout << "Your total points: " << totalPoints << endl << endl;
				}
				else
				{
					cout << "Your answer is wrong. The correct answer is: " << node->answer << endl;
					cout << "Your total points: " << totalPoints << endl << endl;
				}
				
				node = node->next;
			}

			// iterates through the last trivia node in the list.
			if (list.tail == NULL)
			{
				cout << node->question << endl;
				cin >> userAnswer;
				if (userAnswer.compare(node->answer) == 0)
				{
					totalPoints += node->pts;
					cout << "Your answer is correct. You recieved " << node->pts << " points." << endl;
					cout << "Your total points: " << totalPoints << endl << endl;
				}
				else
				{
					cout << "Your answer is wrong. The correct answer is: " << node->answer << endl;
					cout << "Your total points: " << totalPoints << endl << endl;
				}
			}

			cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***";
		}

		// Runs a test client of the trivia quiz game to run unit test cases against.
		void runQuizDebug(TriviaList list, double test)
		{
			string question1, question2, question3;
			string answer1, answer2, answer3;
			int pts;
			string userAnswer;
			int totalPoints = 0;
			TriviaNode* node = list.head;

			// Test case 1
			if (list.head == NULL && test == 1)
			{
				cout << "Warning - The number of trivia to be asked must be equal to or larger than 1." << endl;
				return;
			}

			question1 = "Question: How long was the shortest war on record? (Hint: how many minutes)";
			answer1 = "38";
			pts = 100;
			list.addTriviaNode(question1, answer1, pts);

			question2 = "Question: What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
			answer2 = "Bank of Italy";
			pts = 50;
			list.addTriviaNode(question2, answer2, pts);

			question3 = "Question: What is the best-selling game of all time? (Hint: Minecraft or Tetris)";
			answer3 = "Tetris";
			pts = 20;
			list.addTriviaNode(question3, answer3, pts);

			while (list.tail != NULL)
			{
				// Test case 2.1
				if (node->question == question1 && test == 2.1)
				{
					cout << node->question << endl;
					cout << "Answer: ";
					cin >> userAnswer;
					if (userAnswer.compare(node->answer) != 0)
					{
						cout << "Case 2.1 passed..." << endl;
						return;
					}
				}

				// Test case 2.2
				if (node->question == question3 && test == 2.2)
				{
					cout << node->question << endl;
					cout << "Answer: ";
					cin >> userAnswer;
					if (userAnswer.compare(node->answer) == 0)
					{
						cout << "Case 2.2 passed..." << endl;
						return;
					}
				}

				// Test case 3
				if (list.tail->next == NULL && node->question == question3 && test == 3)
				{
					cout << node->question << endl;
					cout << "Answer: ";
					cin >> userAnswer;
					if (userAnswer.compare(node->answer) == 0)
					{
						cout << "Case 3 passed..." << endl;
						return;
					}
				}

				// Test case 4
				if (list.tail->next == NULL && test == 4)
				{
					cout << "Warning - There are only three trivia in the list." << endl;
					return;
				}

				node = node->next;
			}

			cout << "*** End of the Debug Version ***";
		}
};

void createQuiz();
void runDebug();

// Main driver method for program.
int main()
{
#ifdef UNIT_TESTING
	runDebug();
#else
	createQuiz();
#endif

	return 0;
}

// Creates trivia quiz for normal run.
void createQuiz()
{
	string questionIn;
	string answerIn;
	string clear;
	int ptsIn;
	string doContinueIn;
	TriviaList list;

	if (list.head == NULL)
	{
		cout << "*** Welcome to Eric's trivia quiz game ***" << endl;
		cout << "Enter a question: ";
		getline(cin, questionIn);
		cout << "Enter an answer: ";
		getline(cin, answerIn);
		cout << "Enter award points: ";
		cin >> ptsIn;
		cout << "Continue? (Yes/No): ";
		getline(cin, clear);
		getline(cin, doContinueIn);

		list.addTriviaNode(questionIn, answerIn, ptsIn);
	}

	bool doContinue = true;

	while (doContinue)
	{
		cout << "Enter a question: ";
		getline(cin, questionIn);
		cout << "Enter an answer: ";
		getline(cin, answerIn);
		cout << "Enter award points: ";
		cin >> ptsIn;
		cout << "Continue? (Yes/No): ";
		getline(cin, clear);
		getline(cin, doContinueIn);

		list.addTriviaNode(questionIn, answerIn, ptsIn);

		if (doContinueIn == "No" || doContinueIn == "n")
		{
			doContinue = false;
			cout << endl;
			break;
		}
	}

	list.runQuiz(list);
}

// Executes trivia quiz in debug state.
void runDebug()
{
	string question;
	string answer;
	int pts;
	double testNum;
	TriviaList list;

	cout << "*** this is a debug version ***" << endl;

	cout << "Unit Test Case 1: Ask no questions. The program should give a warning message." << endl;
	testNum = 1;
	list.runQuizDebug(list, testNum);

	question = "Question: How long was the shortest war on record? (Hint: how many minutes)";
	answer = "38";
	pts = 100;
	list.addTriviaNode(question, answer, pts);

	question = "Question: What was Bank of America's original name? (Hint: Bank of Italy or Bank of Germany)";
	answer = "Bank of Italy";
	pts = 50;
	list.addTriviaNode(question, answer, pts);

	question = "Question: What is the best-selling game of all time? (Hint: Minecraft or Tetris)";
	answer = "Tetris";
	pts = 20;
	list.addTriviaNode(question, answer, pts);

	cout << "Unit Test Case 2.1: Ask 1 question in the linked list. The tester enters an incorrect answer." << endl;
	testNum = 2.1;
	list.runQuizDebug(list, testNum);

	cout << "Unit Test Case 2.2: Ask 1 question in the linked list. The tester enters a correct answer." << endl;
	testNum = 2.2;
	list.runQuizDebug(list, testNum);

	cout << "Unit Test Case 3: Ask the last trivia in the linked list." << endl;
	testNum = 3;
	list.runQuizDebug(list, testNum);

	cout << "Unit Test Case 4: Ask five questions in the linked list." << endl;
	testNum = 4;
	list.runQuizDebug(list, testNum);
}