#include "FabrykaSamochodow.h"
#include "Samochod.h"
Samochod* FabrykaSamochodow::wyprodukujSamochod(Samochod* wzorzec)
{
	return new Samochod(*wzorzec);
}

