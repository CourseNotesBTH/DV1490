#ifndef QUEUE_H
#define QUEUE_H

#include "IQueue.h"

template <typename T>
class Queue : public IQueue<T>
{
	struct Node {
		T data;
		Node* next;
		Node(const T data, Node* next) : data(data), next(next) {};
	};

	Node* first;
	Node* last;
	int nrOfElements;

	void free();
	void deepCopy(const Queue& other);
public:
	Queue();
	Queue(const Queue& other);
	~Queue();

	Queue<T>& operator = (const Queue& other);

	void enqueue(const T& element);
	// May throw string exception (missing from interface)
	void dequeue();
	// May throw string exception (missing from interface)
	T front() const;
	bool isEmpty() const;
};

template<typename T>
inline void Queue<T>::free()
{
	if (this->isEmpty())
		return;

	Node* nodeToRemove = this->first;
	for (int i = 0; i < this->nrOfElements - 1; i++)
	{
		Node* next = nodeToRemove->next;
		delete nodeToRemove;
		nodeToRemove = next;
	}

	delete nodeToRemove;
	this->first = nullptr;
	this->last = nullptr;
}

template<typename T>
inline void Queue<T>::deepCopy(const Queue & other)
{
	this->first = nullptr;
	this->last = nullptr;
	this->nrOfElements = other.nrOfElements;

	if (!other.isEmpty()) {
		this->first = new Node(other.first->data, nullptr);
		this->last = this->first;

		Node* walker = other.first->next;
		for (int i = 1; i < other.nrOfElements; i++) {
			Node* nodeToAdd = new Node(walker->data, nullptr);
			this->last->next = nodeToAdd;
			this->last = nodeToAdd;
			walker = walker->next;
		}
	}
}

template<typename T>
inline Queue<T>::Queue()
{
	this->first = nullptr;
	this->last = nullptr;
	this->nrOfElements = 0;
}

template<typename T>
inline Queue<T>::Queue(const Queue & other)
{
	this->deepCopy(other);
}

template<typename T>
inline Queue<T>::~Queue()
{
	free();
}

template<typename T>
inline Queue<T>& Queue<T>::operator=(const Queue & other)
{
	if (this == &other)
		return *this;

	this->free();

	this->deepCopy(other);

	return *this;
}

template<typename T>
inline void Queue<T>::enqueue(const T & element)
{
	Node* nodeToAdd = new Node(element, nullptr);

	if (this->isEmpty()) {
		this->first = nodeToAdd;
		this->last = nodeToAdd;
	} else {
		this->last->next = nodeToAdd;
		this->last = nodeToAdd;
	}
	this->nrOfElements++;
}

template<typename T>
inline void Queue<T>::dequeue()
{
	if (this->isEmpty())
		throw("Exception: empty queue");

	Node* next = this->first->next;
	T data = this->first->data;
	delete this->first;
	this->first = next;
	this->nrOfElements--;
}

template<typename T>
inline T Queue<T>::front() const
{
	if (this->isEmpty())
		throw("Exception: empty queue");

	return this->first->data;
}

template<typename T>
inline bool Queue<T>::isEmpty() const
{
	return this->nrOfElements == 0;
}

#endif