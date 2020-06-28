#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "Hash.h"

// Could well be 0.5 would it not be for the test file not permitting such a load balance.
// Closer to 0 yields faster insertions, higher memory usage
// Closer to 1 yields slower insertions, lower memory usage
const double LOAD_THRESHOLD = 0.9;

template <typename T>
class HashTable
{
private:
	struct Entry {
		T element;
		bool removed;
		Entry() : removed(false) {};
		Entry(T element) : removed(false), element(element) {};
	};
	
	Entry** entries;

	int nrOfEntries;
	int hashTableSize;

	unsigned int hash(const T& elem, int size) const 
	{ 
		static Hash<T> hashFunc; 
		return hashFunc(elem) % size;
	}

	void expand();
	// Helper functions to insert or search for elements in any array
	bool insert(Entry** entries, const T& elem, int size);
	int contains(Entry** entries, const T& elem, int size) const;
public:
	HashTable(int hashTableSize = 101);
	HashTable(const HashTable& aTable) = delete;
	virtual ~HashTable();
	HashTable& operator=(const HashTable& aTable) = delete;
	// Returns the index if element is found, -1 otherwise
	int contains(const T& elem) const;
	bool insert(const T& elem);
	bool remove(const T& elem);

	const T& get(int index) const; 
	void makeEmpty();
	double loadFactor() const;
	int getNrOfEntries() const;
	int getHashTableSize() const;
};

#endif

template<typename T>
inline HashTable<T>::HashTable(int hashTableSize)
{
	this->nrOfEntries = 0;
	this->hashTableSize = hashTableSize;
	this->entries = new Entry*[hashTableSize];
	for (int i = 0; i < this->hashTableSize; i++)
		this->entries[i] = nullptr;
}

template<typename T>
inline HashTable<T>::~HashTable()
{
	this->makeEmpty();
	delete[] this->entries;
}

template<typename T>
inline void HashTable<T>::expand()
{
	int newSize = this->hashTableSize * 2;
	int newCount = 0;
	Entry** rehashedEntries = new Entry*[newSize];
	for (int i = 0; i < newSize; i++)
		rehashedEntries[i] = nullptr;

	for (int i = 0; i < this->hashTableSize; i++) {
		if (this->entries[i] != nullptr && !this->entries[i]->removed) {
			bool inserted = this->insert(rehashedEntries, this->entries[i]->element, newSize);
			if (inserted)
				newCount++;
		}
	}

	this->makeEmpty();
	delete[] this->entries;

	this->entries = rehashedEntries;
	this->nrOfEntries = newCount;
	this->hashTableSize = newSize;
}

template<typename T>
inline bool HashTable<T>::insert(Entry ** entries, const T & elem, int size)
{
	int index = this->hash(elem, size);
	bool inserted = false;
	bool duplicate = this->contains(entries, elem, size) != -1;

	if (!duplicate) {
		for (int i = 0; i < size && !inserted; i++) {
			int currentIndex = (index + i) % size;
			if (entries[currentIndex] == nullptr || entries[currentIndex]->removed) {
				entries[currentIndex] = new Entry(elem);
				inserted = true;
			}
		}
	}

	return inserted;
}

template<typename T>
inline int HashTable<T>::contains(Entry ** entries, const T & elem, int size) const
{
	int allegedIndex = this->hash(elem, size);
	int index = -1;

	// Since "break" is not allowed - such fancy, much readable, very better
	for (int i = 0; i < size && entries[(allegedIndex + i) % size] != nullptr && index == -1; i++) {
		int currentIndex = (allegedIndex + i) % size;
		if (entries[currentIndex]->element == elem)
			index = currentIndex;
	}

	return index;
}

template<typename T>
inline int HashTable<T>::contains(const T & elem) const
{
	return this->contains(this->entries, elem, this->hashTableSize);
}

template<typename T>
inline bool HashTable<T>::insert(const T & elem)
{
	if (this->loadFactor() > LOAD_THRESHOLD)
		this->expand();

	bool inserted = this->insert(this->entries, elem, this->hashTableSize);
	if (inserted)
		this->nrOfEntries++;

	return inserted;
}

template<typename T>
inline bool HashTable<T>::remove(const T & elem)
{
	int index = this->contains(elem);
	if (index != -1) {
		delete this->entries[index];
		// Using "lazy deletion"
		Entry* entry = new Entry();
		entry->removed = true;
		this->entries[index] = entry;
	}

	return index != -1;
}

template<typename T>
inline const T & HashTable<T>::get(int index) const
{
	return this->entries[index]->element;
}

template<typename T>
inline void HashTable<T>::makeEmpty()
{
	for (int i = 0; i < this->hashTableSize; i++) {
		if (this->entries[i] != nullptr)
			delete this->entries[i];
	}

	this->nrOfEntries = 0;
}

template<typename T>
inline double HashTable<T>::loadFactor() const
{
	return (float)this->nrOfEntries / this->hashTableSize;
}

template<typename T>
inline int HashTable<T>::getNrOfEntries() const
{
	return this->nrOfEntries;
}

template<typename T>
inline int HashTable<T>::getHashTableSize() const
{
	return this->hashTableSize;
}
