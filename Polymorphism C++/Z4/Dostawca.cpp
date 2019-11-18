#include "Dostawca.h"

Dostawca::Dostawca(Sklep *_sklep)
{
	sklep = _sklep;
}

void Dostawca::dostarczDoSklepu(Produkt *produkt)
{
	sklep->dodajDoMagazynu(produkt);
	
}
