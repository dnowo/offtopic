
#include <iostream>
#include "List.h"
#include "ListElement.h"


using namespace std;

int main()
{
	/*
	
	
	List* lista = new List();
	lista->addToEnd(3);


	lista->addToBeginning(2);

	lista->printList();

	lista->addToBeginning(1);
	lista->addToBeginning(4);

	lista->printList();

	lista->contains(3);
	lista->contains(5);

	lista->removeKey(3);
	lista->printList();

	lista->removeKey(5);
	lista->printList();

	lista->removeKey(1);
	lista->printList();

	lista->clearAll();
	lista->addToEnd(0);

	lista->printList();
	*/

	List list = List();
	List list2 = List();
	cout << "list: "; list.printList(); cout << endl;
	cout << "list2: "; list2.printList(); cout << endl;
	if (list == list2) cout << "Listy sa identyczne" << endl << endl;
	list += 3; list += 4;
	list2 += 4; list2 += 3;
	list += *new ListElement(5);
	cout << "list: "; list.printList(); cout << endl;
	cout << "list2: "; list2.printList(); cout << endl;
	if (list != list2) cout << "Listy sa rozne" << endl << endl;
	list -= 5; list -= 3; list -= 4;
	list2 -= 4; list2 -= *new ListElement(5); list2 -= *new ListElement(3);
	cout << "list: "; list.printList(); cout << endl;
	cout << "list2: "; list2.printList(); cout << endl;
	list += 1; list += 2;  list += 3;
	list2 += 4; list2 += 5;
	cout << "list: "; list.printList(); cout << endl;
	cout << "list2: "; list2.printList(); cout << endl;


	
}

