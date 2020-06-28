#include "DisjointSets.h"

DisjointSets::DisjointSets(int size)
{
	this->set = nullptr;
	this->size = 0;
	this->count_steps = 0;

	if (size != 0) {
		this->set = new int[size];
		for (int i = 0; i < size; i++)
			this->set[i] = -1;
	}
}

DisjointSets::DisjointSets(const DisjointSets & orig)
{
	this->set = nullptr;
	this->size = orig.size;
	this->count_steps = orig.count_steps;

	if (orig.size != 0)
		this->set = new int[orig.size];

	for (int i = 0; i < orig.size; i++)
		this->set[i] = orig.set[i];
}

DisjointSets::~DisjointSets()
{
	if (this->set != nullptr)
		delete[] this->set;
}

DisjointSets & DisjointSets::operator=(const DisjointSets & orig)
{
	if (this != &orig) {
		if (this->set != nullptr)
			delete[] this->set;

		this->set = nullptr;
		this->size = orig.size;
		this->count_steps = orig.count_steps;

		if (orig.size != 0)
			this->set = new int[orig.size];

		for (int i = 0; i < orig.size; i++)
			this->set[i] = orig.set[i];
	}

	// Convention
	return *this;
}

int DisjointSets::find(int x, bool count) const
{
	if (this->set[x] < 0) {
		return x;
	} else {
		if (count)
			this->count_steps++;
		return this->find(this->set[x]);
	}
}

int DisjointSets::findCompress(int x, bool count)
{
	if (this->set[x] < 0) {
		return x;
	} else {
		if (count)
			this->count_steps++;
		return this->set[x] = this->findCompress(this->set[x]);
	}
}

void DisjointSets::unionSets(int root1, int root2)
{
	this->set[root2] = root1;
}

void DisjointSets::unionSetsRank(int root1, int root2)
{
	if (this->set[root2] < this->set[root1]) {
		this->set[root1] = root2;
	} else {
		if (this->set[root1] == this->set[root2])
			this->set[root1]--;
		this->set[root2] = root1;
	}
}

int DisjointSets::totalNumberStepsForFinds() const
{
	return this->count_steps;
}
