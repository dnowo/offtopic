#include "SalonSamochodowy.h"

SalonSamochodowy::SalonSamochodowy(FabrykaSamochodow *fabryka)
{
	this->fabryka = fabryka;
}

void SalonSamochodowy::dodajWyposazenie(Samochod* samochod, DodatkoweWyposazenie* wyposazenie)
{
	samochod->dodajWyposazenie(wyposazenie);
}

Samochod* SalonSamochodowy::zrealizujZamowienie(Samochod* wzorzec)
{
	return fabryka->wyprodukujSamochod(wzorzec);
}

SalonSamochodowy::~SalonSamochodowy()
{
	//delete fabryka;
}
