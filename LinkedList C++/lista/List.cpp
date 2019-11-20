#include "List.h"
#include <iostream>

using namespace std;

void List::addToBeginning(int key) {
	ListElement* temp = new ListElement(key);
	temp->key = key;
	temp->next = this->firstElement;
	this->firstElement = temp;
	this->size++;
}
void List::addToEnd(int key) {
	ListElement* temp = new ListElement(key);
	ListElement* head = firstElement;

	if (!head) {
		firstElement = temp;
		size++;
		return;
	}
	else {
		ListElement* last = head;
		while (last->next) {
			last = last->next;
		}
		last->next = temp;
		size++;
	}
	
}

void List::printList() {
	ListElement* temp = firstElement;

		cout << "List = [ ";
		while (temp) {
			if (temp) {
				std::cout << temp->key << " ";
				temp = temp->next;
			}
			
		}
		cout << "] size = " << size << endl;

		
	
	
}
List& List::operator+=(ListElement& element)
{
	this->addToEnd(element.getKey());
	return *this;
}
List& List::operator+=(int key)
{
	addToEnd(key);
	return *this;
}
List& List::operator-=(ListElement& element)
{
	removeKey(element.getKey());
	return *this;
}
List& List::operator-=(int key)
{
	removeKey(key);
	return *this;
}
bool List::operator==(List& otherList)
{
	ListElement* temp = firstElement;
	if (otherList.size == this->size)
	{
		while (temp != NULL) {
			if (!contains(temp->getKey())) {
				return false;
			}
			temp = temp->next;
		}
	}
	else return false;

	return true;
}
bool List::operator!=(List& otherList)
{
	ListElement* temp = firstElement;
	if (otherList.size == this->size)
	{
		while (temp != NULL) {
			if (!contains(temp->getKey())) {
				return true;
			}
			temp = temp->next;
		}
	}
	else return true;

	return false;
}
bool List::contains(int key) {
	ListElement* head = firstElement;
	bool contains;
	while (head && head->key != key)
	{
		head = head->next;
	}
	if (head) {
		std::cout << "Contains key " << head->key << endl;
		contains = true;
	}
	else {
		std::cout << "Doesn't contain key " << key << endl;
		contains = false;
	}
	return contains;
}
void List::removeKey(int key) {
	ListElement* head = firstElement;
	if (!head)
		return;

	if (head->getKey() == key)
	{
		if (head->next)
			firstElement = head->next;
		else
			firstElement = NULL;

		delete head;
		size--;
		return;
	}

	while (head->next)
	{
		if (head->next->getKey() == key)
		{
			if (head->next->next)
			{
				ListElement* temp = head->next;
				head->next = head->next->next;
				delete temp;
			}
			else
			{
				delete head->next;
				head->next = NULL;
			}
			size--;
			return;
		}
		head = head->next;
	}

}
void List::clearAll() {
	ListElement* temp = firstElement;
	ListElement* next = NULL;

	if (!temp) return;

	while (temp->next) {
		next = temp->next;
		delete temp;
		temp = next;
		size--;
	}
	delete temp;
	size--;
	firstElement = NULL;

}
