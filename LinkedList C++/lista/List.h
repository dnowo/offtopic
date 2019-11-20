#pragma once
#include "ListElement.h"
class List
{
private:
	ListElement* firstElement;
	int size;
public:
	void addToBeginning(int key);
	void addToBegining(ListElement element);
	void addToEnd(int key);
	void addToEnd(ListElement element);
	ListElement getElement(int key);
	bool contains(int key);
	void removeKey(int key);
	void clearAll();
	void printList();
	List& operator+=(ListElement& element);
	List& operator+=(int key);
	List& operator-=(ListElement& element);
	List& operator-=(int key);
	bool operator==(List& otherList);
	bool operator!=(List& otherList);

};

