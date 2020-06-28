#include "Queue.h"
#include <iostream>
#include <cassert>

using namespace std;

void testOfCopyConstructor(Queue<int> theQueueCopy)
{
	if (!theQueueCopy.isEmpty())
		theQueueCopy.dequeue();
	if (!theQueueCopy.isEmpty())
		theQueueCopy.dequeue();
	theQueueCopy.enqueue(99);
}

int main()
{
	Queue<int> aQueue;
	Queue<int> bQueue;

	cout << "**** Test of copy constructor ****" << endl << endl;
	
	testOfCopyConstructor(aQueue);

	aQueue.enqueue(10);
	aQueue.enqueue(30);

	bQueue.enqueue(55);
	
	cout<<"Expected output: 10 30 55"<<endl<<endl;
	cout<<"Your output:     ";

	while (!aQueue.isEmpty())
	{
		cout << aQueue.front() << " ";
		aQueue.dequeue();
	}
	while (!bQueue.isEmpty())
	{
		cout << bQueue.front() << " ";
		bQueue.dequeue();
	}
	cout<<endl;
	getchar();
	cout<<endl;

	aQueue.enqueue(10);
	aQueue.enqueue(20);
	Queue<int> cQueue = aQueue;

	cQueue.dequeue();

	cout<<endl<<"Expected output: 10 20 20 "<<endl<<endl;
	cout<<"Your output:     ";

	while (!aQueue.isEmpty())
	{
		cout << aQueue.front() << " ";
		aQueue.dequeue();
	}
	while (!cQueue.isEmpty())
	{
		cout << cQueue.front() << " ";
		cQueue.dequeue();
	}
	cout<<endl;

	cout<<endl;
	getchar();
	cout<<endl;
	cout<<endl<<" **** Test of assignment operator *****"<<endl<<endl;

	Queue<int> dQueue;
	Queue<int> eQueue;

	dQueue.enqueue(30);
	dQueue.enqueue(20);
	dQueue.enqueue(10);

	eQueue.enqueue(50);
	eQueue.enqueue(40);

	dQueue = eQueue;

	cout<<endl<<"Expected output: 50 40 50 40"<<endl<<endl;
	cout<<"Your output:     ";

	while (!dQueue.isEmpty())
	{

		cout << dQueue.front() << " ";
		dQueue.dequeue();
	}
	while (!eQueue.isEmpty())
	{
		cout << eQueue.front() << " ";
		eQueue.dequeue();
	}
	cout<<endl;

	Queue<int> fQueue;
	fQueue.enqueue(10);
	fQueue.enqueue(30);

	return 0;
}