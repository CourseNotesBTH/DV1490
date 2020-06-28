#ifndef CDDLIST_H
#define CDDLIST_H

#include "ICircularDoubleDirectedList.h"

template <typename T>
class CircularDoubleDirectedList : public ICircularDoubleDirectedList<T>
{
private:
	struct Node {
		T data;
		Node* previous;
		Node* next;
		Node(const T data, Node* previous, Node* next) : data(data), previous(previous), next(next) {};
	};

	Node* current;
	int nrOfElements;
	direction currentDirection;

	void free();
	void deepCopy(const CircularDoubleDirectedList& other);
public:
	CircularDoubleDirectedList();
	CircularDoubleDirectedList(const CircularDoubleDirectedList& other);
	~CircularDoubleDirectedList();

	CircularDoubleDirectedList<T>& operator = (const CircularDoubleDirectedList& other);

	void addAtCurrent(const T& element);
	// May throw string exception (missing from interface)
	T getElementAtCurrent() const;
	// May throw string exception (missing from interface)
	void removeAtCurrent();
	int size() const;
	void changeDirection();
	// May throw string exception (missing from interface)
	void moveCurrent();
	direction getCurrentDirection() const;
};

template<typename T>
inline void CircularDoubleDirectedList<T>::free()
{
	if (this->size() == 0)
		return;

	Node* nodeToRemove = this->current->previous;
	for (int i = 0; i < this->nrOfElements - 1; i++)
	{
		nodeToRemove = nodeToRemove->next;
		delete nodeToRemove->previous;
	}

	delete nodeToRemove;
	this->current = nullptr;
}

template<typename T>
inline void CircularDoubleDirectedList<T>::deepCopy(const CircularDoubleDirectedList & other)
{
	this->current = nullptr;
	this->nrOfElements = other.nrOfElements;
	this->currentDirection = other.currentDirection;

	if (other.size() != 0) {
		Node* walker1 = new Node(other.current->data, nullptr, nullptr);
		Node* walker2 = other.current->next;

		this->current = walker1;

		for (int i = 0; i < other.nrOfElements - 1; i++) {
			walker1->next = new Node(walker2->data, walker1, nullptr);
			walker1 = walker1->next;
			walker2 = walker2->next;
		}

		this->current->previous = walker1;
		walker1->next = this->current;
	}
}

template<typename T>
inline CircularDoubleDirectedList<T>::CircularDoubleDirectedList()
{
	this->current = nullptr;
	this->nrOfElements = 0;
	this->currentDirection = direction::FORWARD;
}

template<typename T>
inline CircularDoubleDirectedList<T>::CircularDoubleDirectedList(const CircularDoubleDirectedList& other)
{
	this->deepCopy(other);
}

template<typename T>
inline CircularDoubleDirectedList<T>::~CircularDoubleDirectedList()
{
	this->free();
}

template<typename T>
inline CircularDoubleDirectedList<T>& CircularDoubleDirectedList<T>::operator=(const CircularDoubleDirectedList& other)
{
	if (this == &other)
		return *this;

	this->free();
	
	this->deepCopy(other);

	return *this;
}

template<typename T>
inline void CircularDoubleDirectedList<T>::addAtCurrent(const T & element)
{
	/*Om listan är tom skapas en nod för element vilken blir den enda noden i listan.
		Den nya noden är därefter aktuell nod.
		o En ny nod skapas för element vilken placeras före aktuell nod om riktningen är
		BACKWARD och efter aktuell nod om riktningen är FORWARD.Den nya noden
		ska därefter bli aktuell nod.*/

	if (this->size() == 0) {
		Node* node = new Node(element, nullptr, nullptr);
		node->previous = node->next = node;
		this->current = node;
	} else {
		if (this->currentDirection == direction::FORWARD) {
			Node* next = this->current->next;
			Node* nodeToInsert = new Node(element, this->current, next);
			next->previous = nodeToInsert;
			this->current->next = nodeToInsert;
			this->current = nodeToInsert;
		} else {			
			Node* previous = this->current->previous;
			Node* nodeToInsert = new Node(element, previous, this->current);
			previous->next = nodeToInsert;
			this->current->previous = nodeToInsert;
			this->current = nodeToInsert;
		}
	}

	this->nrOfElements++;
}

template<typename T>
inline T CircularDoubleDirectedList<T>::getElementAtCurrent() const
{
	/*Om listan är tom kastas strängen ” Exception : call of getElementAtCurrent on
		empty list”som undantag.
		o Returnerar det element som är aktuellt.*/

	if(this->size() == 0)
		throw("Exception: call of getElementAtCurrent on empty list");

	return this->current->data;
}

template<typename T>
inline void CircularDoubleDirectedList<T>::removeAtCurrent()
{
	/*Om listan är tom kastas strängen ”Exception: call of removeAtCurrent on empty
list” som undantag.
o Aktuell nod tas bort. Om listan endast har en nod blir listan tom och annars blir
aktuell nod den nod som är före om riktningen är BACKWARD och den nod som
är efter om riktningen är FORWARD.*/

	if (this->size() == 0)
		throw("Exception: call of removeAtCurrent on empty list");

	if (this->size() == 1) {
		delete this->current;
		this->current = nullptr;
	} else {
		Node* next = this->current->next;
		Node* previous = this->current->previous;

		next->previous = previous;
		previous->next = next;

		delete this->current;

		if (this->currentDirection == direction::FORWARD)
			this->current = next;
		else
			this->current = previous;
	}

	this->nrOfElements--;
}

template<typename T>
inline int CircularDoubleDirectedList<T>::size() const
{
	/*Returnerar antalet element som finns i listan.*/
	return this->nrOfElements;
}

template<typename T>
inline void CircularDoubleDirectedList<T>::changeDirection()
{
	/* Ändrar riktningen för listan*/
	if (this->currentDirection == direction::FORWARD)
		this->currentDirection = direction::BACKWARD;
	else
		this->currentDirection = direction::FORWARD;
}

template<typename T>
inline void CircularDoubleDirectedList<T>::moveCurrent()
{
	/*Om listan är tom kastas strängen ” Exception: call of moveCurrent on empty
list”som undantag.
o Ändrar current till ”nästa” nod enligt den riktning som ges av
currentDirection. */

	if (this->size() == 0)
		throw ("Exception: call of moveCurrent on empty list");

	if (this->currentDirection == direction::FORWARD)
		this->current = this->current->next;
	else
		this->current = this->current->previous;
}

template<typename T>
inline direction CircularDoubleDirectedList<T>::getCurrentDirection() const
{
	return this->currentDirection;
}

#endif