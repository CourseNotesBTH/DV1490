#include "CircularDoubleDirectedList.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
template <typename T>
void printList(CircularDoubleDirectedList<T>& list)
{
	for (int i=0; i<list.size(); i++)
	{
		cout<<list.getElementAtCurrent()<<" ";
		list.moveCurrent();
	}
}

int main()
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cout << endl<<endl<<"The program stops after each test part and continues when you press <enter>.\n"
		 << "Press <enter> to start the test"<<endl<<endl;
	getchar();
	CircularDoubleDirectedList<int> aList;

	cout<<"********** Testing addAtCurrent, get and move function: **********"<<endl;
	aList.addAtCurrent(100);
	cout << endl << "Expected output: 100" << endl << "Your output    : ";
	printList(aList);
	
	aList.moveCurrent();
	cout << endl;
	
	getchar();
	cout << endl << "Expected output: 100" << endl << "Your output    : ";
	printList(aList);

	aList.addAtCurrent(50);
	cout<<endl;
	
	getchar();
	cout<<endl<<"Expected output: 50 100"<<endl<<"Your output    : ";
	printList(aList);

	aList.addAtCurrent(10);

	aList.moveCurrent();

	cout<<endl;
	getchar();

	cout<<endl<<"Expected output: 100 50 10"<<endl<<"Your output    : ";
	printList(aList);

	cout<<endl;
	getchar();

	cout<<endl<<"**************  Adding test of changeDirection function: *************"<<endl;
	
	aList.changeDirection();
	aList.moveCurrent();
	
	cout<<endl<<"Expected output: 10 50 100"<<endl<<"Your output    : ";
	printList(aList);

	aList.changeDirection();
	
	cout<<endl;
	getchar();

	cout<<endl<<"Expected output: 10 100 50"<<endl<<"Your output    : ";
	printList(aList);
	
	cout<<endl;

	getchar();
	cout<<endl<<"**************  Adding test of remove function: *************"<<endl;
	
	aList.removeAtCurrent();

	cout<<endl<<"Expected output: 100 50"<<endl<<"Your output    : ";
	printList(aList);

	aList.removeAtCurrent();

	cout<<endl;
	getchar();

	cout<<endl<<"Expected output: 50 "<<endl<<"Your output    : ";
	printList(aList);
	
	aList.changeDirection();
	aList.moveCurrent();

	cout << endl;
	getchar();

	cout << endl << "Expected output: 50 " << endl << "Your output    : ";
	printList(aList);

	
	aList.removeAtCurrent();

	cout<<endl;
	getchar();
	cout<<endl<<"Expected output: "<<endl<<"Your output    : ";
	printList(aList);

	cout<<endl;
	getchar();

	cout<<endl<<"**************  Testing excpetion of get function: *************"<<endl;

	cout<<endl<<"Expected output: Exception: call of getElementAtCurrent on empty list"<<endl<<"Your output    : ";
	try
	{
		cout<<aList.getElementAtCurrent();
	}
	catch (char* e)
	{
		cout<<e<<endl;
	}

	cout<<endl;
	getchar();

	cout<<endl<<"**************  Testing exception of remove function: *************"<<endl;

	cout<<endl<<"Expected output: Exception: call of removeAtCurrent on empty list"<<endl<<"Your output    : ";
	try
	{
		aList.removeAtCurrent();
	}
	catch (char* e)
	{
		cout<<e<<endl;
	}

	cout<<endl;
	getchar();

	cout<<endl<<"**************  Testing directions: *************"<<endl;

	cout<<endl<<"Expected output: FORWARD  BACKWARD"<<endl<<"Your output    : ";
	aList.changeDirection();
	if (aList.getCurrentDirection() == FORWARD)
	{
		cout<<"FORWARD  ";
	}
	else
	{
		cout<<"BACKWARD  ";
	}
	
	aList.changeDirection();

	if (aList.getCurrentDirection() == FORWARD)
	{
		cout<<"FORWARD"<<endl;
	}
	else
	{
		cout<<"BACKWARD"<<endl;
	}

	cout << endl << "**************  Some more testing directions: *************" << endl;

	for (int i = 1; i < 7; i++)
	{
		aList.addAtCurrent(i*10);
		if (i % 3 == 0)
			aList.changeDirection();
		if (i % 2 == 0)
			aList.moveCurrent();
	}

	cout << endl;
	getchar();

	cout << endl << "Expected output: 50 10 40 30 20 60 " << endl << "Your output    : ";
	printList(aList);
	
	for (int i = 1; i < 6; i++)
	{
		aList.removeAtCurrent();
		if (i % 3 == 0)
			aList.changeDirection();
		if (i % 2 == 0)
			aList.moveCurrent();
	}

	cout << endl;
	getchar();

	cout << endl << "Expected output: 40 " << endl << "Your output    : ";
	printList(aList);

	aList.removeAtCurrent();

	cout << endl;
	getchar();

	cout << endl << "Expected output: " << endl << "Your output    : ";
	printList(aList);

	cout << endl;
	getchar();

	CircularDoubleDirectedList<int> bList;
	bList.changeDirection();
	bList.addAtCurrent(10);
	cout << endl << "Expected output: 10" << endl << "Your output    : ";
	printList(bList);
	cout << endl << endl;

	bList.addAtCurrent(20);
	cout << endl << "Expected output: 20 10" << endl << "Your output    : ";
	printList(bList);
	cout << endl << endl;

	bList.addAtCurrent(30);
	cout << endl << "Expected output: 30 10 20" << endl << "Your output    : ";
	printList(bList);
	cout << endl << endl;

	cout << "End of test" << endl;
	return 0;
}