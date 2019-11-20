#pragma once
class ListElement
{
	int key;
	ListElement* next;

public:
	friend class List;

	int getKey();
	ListElement(int key);

};

