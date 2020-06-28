#include "CircularDoubleDirectedList.h"
#include <iostream>

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

template <typename T>
void test(CircularDoubleDirectedList<T> list)
{
	list.addAtCurrent(55);
}

int main()
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cout << endl << endl << "The program stops after each test part and continues when you press <enter>.\n"
		<< "Press <enter> to start the test" << endl << endl;
	getchar();
	
	CircularDoubleDirectedList<int> aList;
	
	cout<<"******** Testing copy constructor on empty list ********"<<endl;
	CircularDoubleDirectedList<int> bList = aList;
	cout<<endl<<"Expected output: \nElements in aList: \nElements in bList"<<endl<<endl<<"Your output: "<<endl;
	cout<<"Elements in aList ";
	printList(aList);

	cout<<endl<<"Elements in bList ";
	printList(bList);
	cout<<endl;
	getchar();;
	cout<<endl<<"******** Testing copy constructor on list with content ********"<<endl;
	
	aList.changeDirection();
	aList.addAtCurrent(10);
	aList.addAtCurrent(20);
	aList.addAtCurrent(30);

	CircularDoubleDirectedList<int> cList = aList;

	cList.moveCurrent();
	aList.moveCurrent();
	

	cout<<endl<<"Expected output: \nElements in aList 10 20 30\nElements in cList 10 20 30"<<endl<<endl<<"Your output: "<<endl;
	cout<<"Elements in aList ";
	printList(aList);

	cout<<endl<<"Elements in cList ";
	printList(cList);
	
	aList.changeDirection();
	cList.changeDirection();
	aList.removeAtCurrent();
	cList.addAtCurrent(5);
	
	cout<<endl<<endl<<"Expected output: \nElements in cList 5 30 20 10"<<endl<<endl<<"Your output: "<<endl;
	
	test(cList);
	cout<<"Elements in cList ";
	printList(cList);

	cout<<endl;
	getchar();
	
	CircularDoubleDirectedList<int> dList;
	CircularDoubleDirectedList<int> eList;


	cout<<endl<<endl<<"******** Testing assignment operator on empty list ********"<<endl;
	dList = eList;
	cout<<endl<<"Expected output: \nElements in dList \nElements in eList"<<endl<<endl<<"Your output: "<<endl;
	cout<<"Elements in dList ";
	printList(dList);

	cout<<endl<<"Elements in eList ";
	printList(eList);
	cout<<endl;
	getchar();
	
	cout<<endl<<endl<<"**** Testing assignment operator on list with content assigned empty list****"<<endl;
	eList.addAtCurrent(20);
	eList.addAtCurrent(10);

	eList = dList;

	cout<<endl<<"Expected output: \nElements in dList\nElements in eList"<<endl<<endl<<"Your output: "<<endl;
	cout<<"Elements in dList ";
	printList(dList);

	cout<<endl<<"Elements in eList ";
	printList(eList);
	cout<<endl;
	getchar();
	cout<<endl;

	cout<<endl<<"***** Testing assignment operator on empty list assigned list with content *****"<<endl;
	eList.addAtCurrent(20);
	eList.addAtCurrent(10);

	dList = eList;

	cout<<"Expected output: \nElements in dList 10 20 \nElements in eList 10 20"<<endl<<endl<<"Your output: "<<endl;
	cout<<"Elements in dList ";
	printList(dList);

	cout<<endl<<"Elements in eList ";
	printList(eList);
	cout<<endl;

	getchar();

	dList.addAtCurrent(5);
	eList.removeAtCurrent();
	cout<<endl<<"Expected output: \nElements in dList 5 20 10 \nElements in eList 20"<<endl<<endl<<"Your output: "
		<<endl;
	cout<<"Elements in dList ";
	printList(dList);

	cout<<endl<<"Elements in eList ";
	printList(eList);
	cout<<endl;
	getchar();

	cout<<endl<<"***** Testing assignment operator on lists with content *****"<<endl;
	
	eList = dList;

	cout<<"Expected output: \nElements in dList 5 20 10 \nElements in eList 5 20 10"<<endl<<endl<<"Your output: "<<endl;
	cout<<"Elements in dList ";
	printList(dList);

	cout<<endl<<"Elements in eList ";
	printList(eList);
	cout<<endl;

	getchar();

	eList.addAtCurrent(1);
	dList.removeAtCurrent();

	cout<<endl;
	cout<<"Expected output: \nElements in dList 20 10 \nElements in eList 1 20 10 5"<<endl<<endl<<"Your output: "<<endl;
	cout<<"Elements in dList ";
	printList(dList);

	cout<<endl<<"Elements in eList ";
	printList(eList);
	cout<<endl;

	getchar();

	cout<<endl<<"***** Testing assignment operator on a list assigned itself *****"<<endl;
	
	dList = dList;

	cout<<endl<<"Expected output: \nElements in dList 20 10 "<<endl<<endl<<"Your output: "<<endl;
	cout<<"Elements in dList ";
	printList(dList);
	cout<<endl;

	getchar();
	cout<<endl<<"***** Testing destructor of list *****"<<endl;
	

	ICircularDoubleDirectedList<int>* fList = new CircularDoubleDirectedList<int>();
	
	fList->addAtCurrent(100);
	fList->addAtCurrent(50);

	delete fList;
	cout << "destructor executed" << endl;
	cout << endl;
	getchar();
	cout << endl << "***** some more tests *****" << endl;

	CircularDoubleDirectedList<int> gList;
	gList.addAtCurrent(200);
	gList.addAtCurrent(300);

	CircularDoubleDirectedList<int> hList;
	hList.changeDirection();
	hList.addAtCurrent(300);

	gList = hList;
	hList.addAtCurrent(700);
	hList.addAtCurrent(400);

	gList.changeDirection();
	gList.removeAtCurrent();
	gList.addAtCurrent(900);
	
	cout << endl << "Expected output: \nElements in hList 400 300 700" << endl << endl << "Your output: " << endl;
	cout << "Elements in hList ";
	printList(hList);

	cout << endl;
	cout << endl << "Expected output: \nElements in gList 900 " << endl << endl << "Your output: " << endl;
	cout << "Elements in dList ";
	printList(gList);

	cout << endl;
	getchar();

	cout << endl << endl << "end of test" << endl;

	return 0;
}