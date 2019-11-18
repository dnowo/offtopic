#include "ProduktPrzemyslowy.h"

string ProduktPrzemyslowy::getNazwa()
{
	return this->nazwa;
}
ProduktPrzemyslowy::ProduktPrzemyslowy(string _nazwa) {
	nazwa = _nazwa;
}