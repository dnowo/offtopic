#include <iostream>
#include "Box.h"
using namespace std;
int main()
{

	cout << "*** Instancje tworzone dynamicznie:" << endl;
	const int ile = 10;
	Box* aBox[ile] = { 0 };
	aBox[0] = new Box;
	aBox[1] = new Box();
	aBox[2] = new Box("box2", 2.5, 1, .8);
	aBox[3] = new Box("box3", 3.1);
	aBox[4] = new Box("box4");
	aBox[5] = new Box(*aBox[1]);
	cout << "\n*** Instancje tworzone statycznie:\n";
	Box b6;
	Box b7 = Box();
	Box b8("box8", 1.25, 1, 6.4);
	Box b9("box9", 9.1);
	Box b10("box10");
	Box b11 = b10;
	Box b12(b10);
	Box b13 = Box("box13");
	b12 = b6;
	b13 = Box();
	cout << endl;
	for (int i=0;i<ile;i++)
		if (aBox[i]) aBox[i]->printVolume();
	cout << endl;
	b6.printVolume();
	b7.printVolume();
	b8.printVolume();
	b9.printVolume();
	b10.printVolume();
	b11.printVolume();
	b12.printVolume();
	b13.printVolume();
	cout << "\n*** Czyszczenie instancji dynamicznych:\n";
	for(int i=0;i<ile;i++)
		if(aBox[i]) delete aBox[i];
	cout<< "\n*** Koniec main()\n";
}
