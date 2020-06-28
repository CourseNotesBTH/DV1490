#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

class DisjointSets
{
private:
	// Array for representing the sets
	int* set;
	// Size of the array
	int size;
	// Counter for total number of steps taken by all find() alternatively all findCompress()
	mutable int count_steps;
public:
	// Size is the number of elements
	DisjointSets(int size);
	DisjointSets(const DisjointSets &orig);
	virtual ~DisjointSets();
	DisjointSets& operator=(const DisjointSets &orig);
	int find(int x, bool count = false) const;
	int findCompress(int x, bool count = false);
	void unionSets(int root1, int root2);
	void unionSetsRank(int root1, int root2);
	// Returns the value of count_steps
	int totalNumberStepsForFinds() const;
};

#endif