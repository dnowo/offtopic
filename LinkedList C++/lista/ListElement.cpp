#include "ListElement.h"
#include <iostream>

ListElement::ListElement(int key) {
	this->key = key;
	this->next = NULL;
}
int ListElement::getKey() {
	return key;
}