#include "EngWord.h"

EngWord::EngWord()
{
	this->word = "";
}

EngWord::EngWord(const std::string& word)
{
	this->word = word;
}

EngWord::~EngWord()
{
}

bool EngWord::operator==(const EngWord & other) const
{
	return this->word == other.word;
}

bool EngWord::operator!=(const EngWord & other) const
{
	return !(*this == other);
}

std::string EngWord::getWord() const
{
	return this->word;
}

int EngWord::getLength() const
{
	return (int)this->word.length();
}

char EngWord::at(int index) const
{
	return this->word.at(index);
}
