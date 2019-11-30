#include "DodatkoweWyposazenie.h"


DodatkoweWyposazenie::DodatkoweWyposazenie(string nazwa)
{
	this->nazwa = nazwa;
}

DodatkoweWyposazenie::~DodatkoweWyposazenie()
{
}



string DodatkoweWyposazenie::getNazwa()
{
	return nazwa;
}
