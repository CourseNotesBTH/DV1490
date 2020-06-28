#ifndef TESTELEMENT_H
#define TESTELEMENT_H

#include "Hash.h"
#include <iostream>
using namespace std;
class TestElement
{
private:
	long number;
public:
	TestElement(long number = 0) { this->number = number; }
	long getNumber() const { return this->number; }
	bool operator==(const TestElement& aWord) { return this->number == aWord.number; }
	bool operator!=(const TestElement& aWord) { return this->number != aWord.number; }
};

template<>
class Hash<TestElement>
{

public:
	unsigned int operator()(const TestElement& elem) const // not sofisticated and just intended for testing
	{
		unsigned int hashKey = elem.getNumber();
	
		return hashKey;
	}
};

#endif