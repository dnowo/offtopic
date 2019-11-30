#include <iostream>
#include <string>
#include "DodatkoweWyposazenie.h"
#include "Samochod.h"
#include "FabrykaSamochodow.h"
#include "SalonSamochodowy.h"

using namespace std;

int main()
{
	
	Samochod* wzorzec = Samochod::dajWzorzec("Peugeot", 140, 16, 4);
	cout << endl;
	wzorzec->wyswietlSpecyfikacje();
	cout << endl;
	
	FabrykaSamochodow fab;
	SalonSamochodowy salon(&fab);

	Samochod* zamowionySamochod = salon.zrealizujZamowienie(wzorzec);
	
	salon.dodajWyposazenie(zamowionySamochod, new DodatkoweWyposazenie("klimatyzacja"));
	
	wzorzec->wyswietlSpecyfikacje();
	cout << endl;
	zamowionySamochod->wyswietlSpecyfikacje();
	
	cout << "Koniec programu" << endl;
	
	return 0;
}
