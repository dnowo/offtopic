#pragma once
#include <iostream>
#include <string>
#include "FabrykaSamochodow.h"
#include "Samochod.h"
#include "DodatkoweWyposazenie.h"
using namespace std;

class SalonSamochodowy
{
private:
	FabrykaSamochodow *fabryka;
public:
	SalonSamochodowy(FabrykaSamochodow *fabryka);
	void dodajWyposazenie(Samochod *samochod, DodatkoweWyposazenie *wyposazenie);
	Samochod* zrealizujZamowienie(Samochod *wzorzec);
	~SalonSamochodowy();
};

