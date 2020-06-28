#include "Queue.h"
#include <iostream>

using namespace std;

int main()
{
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	cout<<"Expected output:\n0 1\nQueue is not empty.\nDequeued 1 2\nDequeued 3 4 5 6\nFront element 7\nDequeued until empty: 7\nQueue is empty \nException: empty Queue\nException: empty Queue\n\n";
	getchar();
	cout<<endl<<"Your output"<<endl;
	Queue<int> aQueue;

	for (int i=0; i<5; i++)
		aQueue.enqueue(i);

	cout << aQueue.front() << " ";
	aQueue.dequeue();
	cout << aQueue.front() << endl;

	if (!aQueue.isEmpty())
	{
		cout<<"Queue is not empty."<<endl;
	}

	cout << "Dequeued: ";
	cout << aQueue.front() << " ";
	aQueue.dequeue();
	cout << aQueue.front() << endl;
	aQueue.dequeue();

	aQueue.enqueue(5);
	aQueue.enqueue(6);
	aQueue.enqueue(7);

	cout << "Dequeued: ";
	cout << aQueue.front() << " ";
	aQueue.dequeue();
	cout << aQueue.front() << " ";
	aQueue.dequeue();
	cout << aQueue.front() << " ";
	aQueue.dequeue();
	cout << aQueue.front() << endl;
	aQueue.dequeue();

	cout << "Front element: ";
	cout << aQueue.front() << endl;

	cout << "Dequeued until empty: ";
	while (!aQueue.isEmpty())
	{
		cout << aQueue.front() << endl;
		aQueue.dequeue();
	}

	if (aQueue.isEmpty())
		cout<<"Queue is empty"<<endl;
	try
	{
		cout << aQueue.front();
	}
	catch(char* e)
	{
		cout<<e<<endl;
	}
	try
	{
		aQueue.dequeue();
	}
	catch(char* e)
	{
		cout<<e<<endl;
	}

	for (int i=0; i<200; i++)
		aQueue.enqueue(i);

	for (int i=0; i<190; i++)
		aQueue.dequeue();


	return 0;
}