#include "Kolo.h"

Kolo::Kolo(int rozmiar)
{
	this->rozmiar = rozmiar;
	//cout << "Konstruktor klasy Kolo!" << endl;
}

int Kolo::getRozmiar()
{
	return rozmiar;
}

Kolo::~Kolo()
{
}
