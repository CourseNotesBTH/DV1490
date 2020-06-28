#include <iostream>
#include <iomanip> 
#include <random>
#include <string>
#include <chrono>
#include <thread>

#ifdef _WIN32
#include <windows.h>
#endif

#include "DisjointSets.h"

using namespace std;

/*
I en annan fil innehållande main-funktionen implementerar du testerna. Här skapar du fyra
objekt av typen DisjointSets; ett objekt för var och en av de kombinationer av find och
union som ska undersökas. Definiera en konstant för antalet element vilken sätts till
10000. (Varje element ska läggas i en egen mängd vid initialiseringen.)
Operationen find ska utföras 5000 gånger för element som slumpas fram. Operationen
union ska också göras 5000 gånger med slumpmässigt valda element. Du väljer hur du
”blandar” dessa 10000 operationer (enklast är kanske att göra find varannan gång och
union varannan gång). För att få jämförbara testresultat ska varje slumpad serie användas
för de fyra objekten (dvs, de fyra olika kombinationerna av heuristiker för find och union).
Givetvis är det enbart disjunkta mängder som ska ”slås ihop” med union. Använd värden
returnerade av find(…) respektive findCompress(…) för att undersöka detta.

Som mått på ”tid” ska ditt program räkna totala antalet trädnoder som besöks av find(…)
respektive findCompress(…). Använd medlemsvariabeln count_steps för detta.
Testerna ska upprepas 100 gånger. Medelvärdet av de hundra testernas antal besökta noder
för respektive DisjontSet objekt ska beräknas. Resultaten ska presenteras i en tabell med
två rader (union utan och med rank) och två kolumner (find utan och med
stigkomprimering). Även standardavvikelsen ska beräknas och presenteras i en tabell.
*/

// Set size of disjoint sets
const int SET_SIZE = 10000;
// Amount of executions of the find and union functions. Each find and union function is ran half of the time
const int METHOD_EXECUTIONS = 10000;
// Amount of executions of the entire test
const int TEST_EXECUTIONS = 100;

// An unbiased PRNG functor
struct PRNG {
private:
	random_device seeder;
	mt19937 engine;
	uniform_int_distribution<int> distribution;
public:
	PRNG() : engine(seeder()), distribution(0, SET_SIZE - 1) {};
	int operator()() { return distribution(engine); }
};

// A simple progress animation
struct ProgressIndicator {
private:
	string states = "-\\|/";
	int state = 0;
	int test = 0;
public:
	ProgressIndicator() {};
	void draw() { test++; state = (state + 1) % 4; cout << string(5, '\b') << states.at(state) << " " << (int)(((float)test / TEST_EXECUTIONS) * 100) << "%" << flush; }
};

// A somewhat portable clear screen function
void clear() {
#ifdef __linux__ 
	system("clear");
#elif _WIN32
	system("cls");
#endif
}

// A somewhat portable move cursor function
void moveCursor(int x, int y)
{
#ifdef __linux__ 
	printf("%c[%d;%df", 0x1B, y, x);
#elif _WIN32
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
}

int* randomArray(int SET_SIZE, PRNG& randomInt) {
	int* array = new int[SET_SIZE];
	for (int i = 0; i < SET_SIZE; i++)
		array[i] = randomInt();
	return array;
}

void printTable(float averages[], float deviation[]) {
	// Array indexes:
	// 0: find() & unionSets()
	// 1: find() & unionSetsRank()
	// 2: findCompress() & unionSets()
	// 3: findCompress() & unionSetsRank()

	cout << "+--------------------------------------------------------------------------+" << endl;
	cout << "| Test Results:                                                            |" << endl;
	cout << "+--------------------------------------------------------------------------+" << endl;
	cout << "| union type | w/o compression               | w/ compression              |" << endl;
	cout << "|            |-------------------------------------------------------------+" << endl;
	cout << "|            | average | standard deviation | average | standard deviation |" << endl;
	cout << "+--------------------------------------------------------------------------+" << endl;
	cout << "| w/o rank   |";
	cout << setw(9) << averages[0] << "|" << setw(20) << deviation[0] << "|";
	cout << setw(9) << averages[2] << "|" << setw(20) << deviation[2] << "|" << endl;
	cout << "+--------------------------------------------------------------------------+" << endl;
	cout << "| w/  rank   |";
	cout << setw(9) << averages[1] << "|" << setw(20) << deviation[1] << "|";
	cout << setw(9) << averages[3] << "|" << setw(20) << deviation[3] << "|" << endl;
	cout << "+--------------------------------------------------------------------------+" << endl;
	cout << endl;
	cout << "+---------------------------+" << endl;
	cout << "| Constants:                |" << endl;
	cout << "+---------------------------+" << endl;
	cout << "| name              | value |" << endl;
	cout << "+---------------------------+" << endl;
	cout << "| SET_SIZE          |" << setw(7) << SET_SIZE << "|" << endl;
	cout << "+---------------------------+" << endl;
	cout << "| METHOD_EXECUTIONS |" << setw(7) << METHOD_EXECUTIONS << "|" << endl;
	cout << "+---------------------------+" << endl;
	cout << "| TEST_EXECUTIONS   |" << setw(7) << TEST_EXECUTIONS << "|" << endl;
	cout << "+---------------------------+" << endl;
}

void yyyyyyyyy(){int y=13;const char yy[]={0x20,0x20,0x20,0x20,0x20,0x20,0x5f,0x2e,0x2d,0x27,0x27,0x27,0x27,0x27,0x2d,0x2e,0x5f,0x0d,0x0a,0x20,0x20,0x20,0x20,0x2e,0x27,0x20,0x20,0x5f,0x20,0x20,0x20,0x20,0x20,0x5f,0x20,0x20,0x27,0x2e,0x0d,0x0a,0x20,0x20,0x20,0x2f,0x20,0x20,0x20,0x28,0x6f,0x29,0x20,0x20,0x20,0x28,0x6f,0x29,0x20,0x20,0x20,0x5c,0x0d,0x0a,0x20,0x20,0x7c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x7c,0x0d,0x0a,0x20,0x20,0x7c,0x20,0x20,0x5c,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x2f,0x20,0x20,0x7c,0x0d,0x0a,0x20,0x20,0x20,0x5c,0x20,0x20,0x27,0x2e,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x2e,0x27,0x20,0x20,0x2f,0x0d,0x0a,0x20,0x20,0x20,0x20,0x27,0x2e,0x20,0x20,0x60,0x27,0x2d,0x2d,0x2d,0x27,0x60,0x20,0x20,0x2e,0x27,0x0d,0x0a,0x20,0x20,0x20,0x20,0x20,0x20,0x27,0x2d,0x2e,0x5f,0x5f,0x5f,0x5f,0x5f,0x2e,0x2d,0x27};moveCursor(40,y);for(int i=0;i<168;i++){if(yy[i]==0x0d){moveCursor(40,++y);}else if(yy[i]!=0x0a){cout<<yy[i];}}chrono::milliseconds yyyyyy(200);chrono::milliseconds yyy(3300);chrono::milliseconds yyyy(5500);chrono::milliseconds yyyyy(1140);int time=0;while(true){moveCursor(40+8,15);cout<<"_";moveCursor(40+8+6,15);cout<<"_";this_thread::sleep_for(yyyyyy);moveCursor(40+8,15);cout<<"O";moveCursor(40+8+6,15);cout<<"O";moveCursor(0,24);time++;if (time%3==0){this_thread::sleep_for(yyy);}if(time%3==1){this_thread::sleep_for(yyyy);}if(time%3==2){this_thread::sleep_for(yyyyy);}}}

int calculateSum(int array[], int setSize) {
	int sum = 0;
	for (int i = 0; i < setSize; i++)
		sum += array[i];
	return sum;
}

float calculateAverage(int array[], int setSize) {
	return (float)calculateSum(array, setSize) / setSize;
}

// Expects setSize > 1
float calculateStandardDeviation(int array[], int setSize, float average) {
	float deviationSum = 0;
	for (int i = 0; i < setSize; i++)
		deviationSum += powf(array[i] - average, 2);
	return deviationSum / (setSize - 1);
}

int main() {
#ifdef _WIN32
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	ProgressIndicator indicator;

	// find() & unionSets()
	int stepsA[TEST_EXECUTIONS];
	// find() & unionSetsRank()
	int stepsB[TEST_EXECUTIONS];
	// findCompress() & unionSets()
	int stepsC[TEST_EXECUTIONS];
	// findCompress() & unionSetsRank()
	int stepsD[TEST_EXECUTIONS];

	// For each test
	for (int testIndex = 0; testIndex < TEST_EXECUTIONS; testIndex++) {
		// Draw the loading indicator - once per test
		indicator.draw();

		// Initialize functor with new seed for each test
		PRNG generateInt;

		// find() & unionSets()
		DisjointSets setA(SET_SIZE);
		// find() & unionSetsRank()
		DisjointSets setB(SET_SIZE);
		// findCompress() & unionSets()
		DisjointSets setC(SET_SIZE);
		// findCompress() & unionSetsRank()
		DisjointSets setD(SET_SIZE);

		DisjointSets** sets = new DisjointSets*[4]{ &setA, &setB, &setC, &setD };

		int* inputSeries = randomArray(METHOD_EXECUTIONS, generateInt);	

		// For each combination of methods (for each set)
		for (int setIndex = 0; setIndex < 4; setIndex++) {
			int rootA = -1;

			// For each call to find and union functions
			for (int methodExecution = 0; methodExecution < METHOD_EXECUTIONS; methodExecution++) {

				// Execute find every other time (executed first)
				if (methodExecution % 2 == 0) {
					if		(setIndex == 0)	rootA = setA.find(generateInt(), true);
					else if (setIndex == 1) rootA = setB.find(generateInt(), true);
					else if (setIndex == 2) rootA = setC.findCompress(generateInt(), true);
					else if (setIndex == 3) rootA = setD.findCompress(generateInt(), true);

				// Execute union every other time
				} else {
					int rootB = generateInt();
					do {
						rootB = generateInt();
					} while (rootB == rootA || sets[setIndex]->find(rootB) == rootA);

					if		(setIndex == 0)	setA.unionSets(rootA, rootB);
					else if (setIndex == 1) setB.unionSetsRank(rootA, rootB);
					else if (setIndex == 2) setC.unionSets(rootA, rootB);
					else if (setIndex == 3) setD.unionSetsRank(rootA, rootB);
				}
			}

			if		(setIndex == 0)	stepsA[testIndex] = setA.totalNumberStepsForFinds();
			else if (setIndex == 1) stepsB[testIndex] = setB.totalNumberStepsForFinds();
			else if (setIndex == 2) stepsC[testIndex] = setC.totalNumberStepsForFinds();
			else if (setIndex == 3) stepsD[testIndex] = setD.totalNumberStepsForFinds();
		}

		delete[] inputSeries;
		delete[] sets;
	}

	// 0: find() & unionSets()
	// 1: find() & unionSetsRank()
	// 2: findCompress() & unionSets()
	// 3: findCompress() & unionSetsRank()
	float averages[4] = { calculateAverage(stepsA, TEST_EXECUTIONS), 
						  calculateAverage(stepsB, TEST_EXECUTIONS), 
						  calculateAverage(stepsC, TEST_EXECUTIONS), 
						  calculateAverage(stepsD, TEST_EXECUTIONS) };

	float deviations[4] = { calculateStandardDeviation(stepsA, TEST_EXECUTIONS, averages[0]), 
							calculateStandardDeviation(stepsB, TEST_EXECUTIONS, averages[1]), 
							calculateStandardDeviation(stepsC, TEST_EXECUTIONS, averages[2]), 
							calculateStandardDeviation(stepsD, TEST_EXECUTIONS, averages[3]) };

	clear();
	printTable(averages, deviations);
	yyyyyyyyy();

	getchar();

	return 0;
}