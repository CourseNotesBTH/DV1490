/*
	The size of the table is initially 101 elements (per spec).
	When the load balance is above 0.9 the table doubles in size (common practice) and is rehashed.

	The hash algo chosen is DJB2.
	It was chosen for its wide spread use. No need for a homebrew algo reinventing the wheel
	Pretty collision resistent, but not exactly "crypto grade"
*/

#include "HashTable.h"
#include "EngWord.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

// Size of file in lines
const int FILE_SIZE = 1000;

const std::string FILE_PATH = "C:\\temp\\engWords.txt";

void read(EngWord* words, std::string filename) {
	std::ifstream file(filename);
	int lineNumber = 0;
	std::string line;

	if (!file.is_open()) {
		std::cout << "Can't seem to open the file - make sure it exists in C:\\temp\\engWords.txt" << std::endl;
		exit(1);
	}

	//Read line by line
	while (getline(file, line))
	{
		words[lineNumber] = EngWord(line);
		lineNumber++;
	}
	file.close();
}

void createHashTable(HashTable<EngWord>& table, EngWord* words) {
	for (int i = 0; i < FILE_SIZE; i++)
		table.insert(words[i]);

	std::cout << "Load factor: " << table.loadFactor() << std::endl;
}

void checkWords(const HashTable<EngWord>& table, std::string words) {
	std::stringstream stream;
	stream.str(words);
	std::string word = "";
	bool foundWords = false;
	while (stream >> word) {
		if (table.contains(word) == -1) {
			std::cout << word << ",";
			foundWords = true;
		}
	}
	if(foundWords)
		std::cout << " does not exist" << std::endl;
	else
		std::cout << "all words existed" << std::endl;
}

void addWords(HashTable<EngWord>& table, std::string words) {
	std::stringstream stream;
	stream.str(words);
	std::string word = "";
	bool foundDuplicate = false;
	// Note: the method for reading space seperated strings is not fault tolerant.
	// Not needed for the assignment, but beware of possible infinite loops if input
	// is not formatted correctly
	while (stream >> word) {
		if (!table.insert(word)) {
			std::cout << word << ",";
			foundDuplicate = true;
		}
	}
	if (foundDuplicate)
		std::cout << " already existed" << std::endl;
	else
		std::cout << "all words were new" << std::endl;
}

void removeWords(HashTable<EngWord>& table, std::string words) {
	std::stringstream stream;
	stream.str(words);
	std::string word = "";
	bool nonExistent = false;
	while (stream >> word) {
		if (!table.remove(word)) {
			std::cout << word << ",";
			nonExistent = true;
		}
	}
	if (nonExistent)
		std::cout << " did not exist" << std::endl;
	else
		std::cout << "all words were removed" << std::endl;
}

std::string inputString() {
	std::string input = "";

	std::cout << "Space seperated lowercase words: ";
	getchar();
	getline(std::cin, input);

	return input;
}

void aaaaaaaaaaaa() {
	const int aaaaaaaaaaaaaa = (3 * 20 + 8) / 2 - 2;
	//const int aaaaaaaaaaaaa = aaaaaaaaaaaaaa;
	char aaaaaaaaa[] = { aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x2f, 0x27, 0x3d, 0x2d, 0x2d, 0x2d, 0x2d, 0x3d, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x0d, 0x0a, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x28, 0x28, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x7c, 0x7c, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x22, 0x2d, 0x2d, 0x2e, 0x5f, 0x5f, 0x2e, 0x22, 0x0d, 0x0a, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x22, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x40, 0x3e, 0x7c, 0x7c, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x2f, 0x2f, 0x0d, 0x0a, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, aaaaaaaaaaaaaa, 0x2f, 0x5e, 0x5c, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x2f, 0x2f, 0x5c, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x29, 0x0d, 0x0a, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x5f, 0x2d, 0x2d, 0x22, 0x22, 0x22, 0x2d, 0x2d, 0x2f, 0x2d, 0x2e, aaaaaaaaaaaaaa, 0x22, 0x5c, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x2f, 0x2f, aaaaaaaaaaaaaa, 0x5f, 0x5c, 0x2d, 0x3a, 0x3a, 0x3a, 0x2d, 0x2f, 0x5f, 0x2d, 0x2e, 0x0d, 0x0a, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x2e, 0x22, aaaaaaaaaaaaaa, 0x2e, 0x2d, 0x22, 0x22, 0x22, 0x2d, 0x2f, aaaaaaaaaaaaaa, 0x22, 0x5f, 0x5c, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x22, 0x5c, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x3d, 0x3d, aaaaaaaaaaaaaa, 0x2f, 0x2f, aaaaaaaaaaaaaa, 0x3b, 0x3a, 0x3a, 0x5c, 0x3a, 0x3a, 0x3a, 0x2f, 0x3a, 0x3a, 0x22, 0x2e, 0x5c, 0x0d, 0x0a, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x3b, aaaaaaaaaaaaaa, 0x2f, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x5f, 0x2f, aaaaaaaaaaaaaa, 0x22, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x5c, 0x5c, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x22, 0x5c, 0x2d, 0x2b, 0x2f, 0x2f, 0x2d, 0x2d, 0x2e, 0x2e, 0x2e, 0x5f, 0x5c, 0x5f, 0x2f, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x5c, 0x5c, 0x0d, 0x0a, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x2e, aaaaaaaaaaaaaa, 0x3b, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x6f, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x2e, aaaaaaaaaaaaaa, 0x7c, 0x7c, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x28, aaaaaaaaaaaaaa, 0x28, 0x29, 0x2f, 0x29, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x3d, 0x28, 0x6f, 0x29, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x2e, 0x0d, 0x0a, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x2e, aaaaaaaaaaaaaa, 0x5c, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x3b, aaaaaaaaaaaaaa, 0x2e, 0x7c, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x2d, 0x7c, 0x2e, 0x3b, 0x5f, 0x5f, 0x5f, 0x5f, 0x2e, 0x2e, 0x2e, 0x2e, 0x22, 0x62, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3b, 0x0d, 0x0a, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x2e, aaaaaaaaaaaaaa, 0x2d, 0x2e, 0x5f, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x5f, aaaaaaaaaaaaaa, 0x2d, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x3b, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x3d, 0x3d, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3b, 0x0d, 0x0a, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x22, 0x2d, 0x2e, 0x2e, 0x5f, 0x5f, 0x5f, 0x5f, 0x2e, 0x27, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x6c, 0x73, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, aaaaaaaaaaaaaa, 0x22, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x3a, 0x27 };
	for (int aaaaaaaaaa = 0; aaaaaaaaaa < sizeof(aaaaaaaaa) / sizeof(*aaaaaaaaa); aaaaaaaaaa++)
		std::cout << (char)aaaaaaaaa[aaaaaaaaaa];
	std::cout << std::endl;
	getchar();
}

// Somewhat portable clear screen
void cls() {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	system("cls");
#else
	system("clear");
#endif
}

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Uncomment for surprise
	//aaaaaaaaaaaa();

	EngWord* words = new EngWord[FILE_SIZE];
	read(words, FILE_PATH);
	HashTable<EngWord> table;
	createHashTable(table, words);

	bool shouldRun = true;

	do {
		cls();
		std::cout << "1. Check words\n2. Add words\n3. Remove words\n4. Quit" << std::endl;

		int choice = -1;
		do {
			std::cout << "Your choice: ";
			std::cin >> choice;
		} while (choice < 1 || choice > 4);

		switch (choice) {
		case 1:
			checkWords(table, inputString());
			break;
		case 2:
			addWords(table, inputString());
			break;
		case 3:
			removeWords(table, inputString());
			break;
		case 4:
			shouldRun = false;
			break;
		}
		
		std::cout << "Press any key to continue" << std::endl;
		getchar();
	} while (shouldRun);

	delete[] words;

	return 0;
}