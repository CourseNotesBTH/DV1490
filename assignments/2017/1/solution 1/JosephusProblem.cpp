#include "Queue.h"
#include "CircularDoubleDirectedList.h"
#include <string>
#include <iostream>
using namespace std;

void addPersons(CircularDoubleDirectedList<string> &list);
void outputTheListFromCurrent(CircularDoubleDirectedList<string> &list); // used while testing
void removeOnePersonFromList(const int counter, CircularDoubleDirectedList<string> &list, Queue<string> &queue);
int main()
{
	int counter;
	CircularDoubleDirectedList<string> execList;
	Queue<string> queueOfPersons;
	addPersons(execList);
	execList.moveCurrent();

	cout << "Input the size of the counter ";
	cin >> counter;
	while (execList.size() > 1)
	{
		removeOnePersonFromList(counter, execList, queueOfPersons);
		execList.changeDirection();
	}
	cout << "The person that got lucky and is released is " << execList.getElementAtCurrent() << endl;
	cout << "The other persons was executed in the order: ";
	while (!queueOfPersons.isEmpty())
	{
		cout << queueOfPersons.front() << ", ";
		queueOfPersons.dequeue();
	}
	return 0;
}

void addPersons(CircularDoubleDirectedList<string> &list)
{
	int nrOfPersons;
	string name;
	cout << "Input the number of persons: ";
	cin >> nrOfPersons;
	cin.ignore();
	cout << "Input the name of the persons separated by return" << endl;
	for (int i = 0; i<nrOfPersons; i++)
	{
		getline(cin, name);
		list.addAtCurrent(name);
	}
}

void outputTheListFromCurrent(CircularDoubleDirectedList<string> &list)
{
	int i = 0;
	while (i < list.size())
	{
		cout << list.getElementAtCurrent() << endl;
		list.moveCurrent();
		i++;
	}
}

void removeOnePersonFromList(const int counter, CircularDoubleDirectedList<string> &list, Queue<string> &queue)
{
	int i = 1;
	while (i < counter)
	{
		list.moveCurrent();
		i++;
	}
	queue.enqueue(list.getElementAtCurrent());
	list.removeAtCurrent();
}