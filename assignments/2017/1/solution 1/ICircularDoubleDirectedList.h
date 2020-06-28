#ifndef ICDDLIST_H
#define ICDDLIST_H

enum direction{ FORWARD, BACKWARD };

template <typename T>
class ICircularDoubleDirectedList
{
public:
	virtual ~ICircularDoubleDirectedList() {};
	virtual void addAtCurrent(const T& element) = 0;
	virtual T getElementAtCurrent() const = 0;
	virtual void removeAtCurrent() = 0;
	virtual int size() const = 0;
	virtual void changeDirection() = 0;
	virtual void moveCurrent() = 0;
	virtual direction getCurrentDirection() const = 0;
};

#endif