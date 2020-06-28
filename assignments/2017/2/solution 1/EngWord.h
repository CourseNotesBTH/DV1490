#ifndef EngWord_H
#define EngWord_H

#include "Hash.h"

#include <string>

class EngWord
{
private:
	std::string word;
public:
	EngWord();
	EngWord(const std::string& word);
	virtual ~EngWord();

	bool operator == (const EngWord& other) const;
	bool operator != (const EngWord& other) const;

	std::string getWord() const;
	int getLength() const;
	char at(int index) const;
};

template<>
class Hash<EngWord>
{
public:
	// Calculate hash using DJB2
	// Chosen for its wide spread use. No need for a homebrew algo reinventing the wheel
	// Pretty collision resistent, but not exactly "crypto grade"
	unsigned int operator()(const EngWord& element) const
	{
		// 5381 is a Magic Number needed for the algorithm
		unsigned int hash = 5381;
		
		// 33 is a Magic Number needed for the algorithm
		for (int i = 0; i < element.getLength(); i++)
			hash = (hash * 33) + (int)element.at(i);

		return hash;
	}
};

#endif