#include "HashTable.h"
#include <iostream>
#include <string>
#include "TestElement.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>


using namespace std;

int main()
{
	cout << "Expected output" << endl;
	cout << setw(8) << right << 123456 << " at subscript 6" << endl;
	cout << setw(8) << right << 67543 << " at subscript 3" << endl;
	cout << setw(8) << right << 98999 << " at subscript 9" << endl;
	cout << setw(8) << right << 16 << " at subscript 7" << endl;
	cout << setw(8) << right << 6547 << " at subscript 8" << endl;
	cout << setw(8) << right << 777 << " at subscript 0" << endl;
	cout << endl << endl;

	cout << "16 is allready in the table and can not be duplicated" << endl;
	cout << "123456 is allready in the table and can not be duplicated" << endl;
	cout << endl;
	cout << "press enter to continue and check your output "<<endl;
	getchar();
	cout << "Your output: " << endl;

	long arr[] = {123456, 67543, 98999, 656, 6547, 777};
	HashTable<TestElement> hashTable(10);

	for (int i = 0; i < 6; i++)
	{
		hashTable.insert(TestElement(arr[i]));
	}

	hashTable.remove(TestElement(656)); 

	hashTable.insert(TestElement(16));

	arr[3] = 16;


	for (int i = 0; i < 6; i++)
	{
		cout <<setw(8)<<right<< arr[i] << " at subscript " << hashTable.contains(TestElement(arr[i])) << endl;
	}
	cout << endl << endl;

	if (!hashTable.insert(16))
	{
		cout << "16 is allready in the table and can not be duplicated" << endl;
	}
	if (!hashTable.insert(123456))
	{
		cout << "123456 is allready in the table and can not be duplicated" << endl;
	}
	return 0;
}