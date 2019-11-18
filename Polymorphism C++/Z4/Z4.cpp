
#include <iostream>
#include "Sklep.h"
#include "Produkt.h"
#include "ProduktPrzemyslowy.h"
#include "ProduktSpozywczy.h"
#include "Dostawca.h"

int main()
{
	Sklep* sklep = new Sklep();     

	Dostawca* dostawca = new Dostawca(sklep);


	ProduktPrzemyslowy* notes = new ProduktPrzemyslowy("Notes");
	dostawca->dostarczDoSklepu(notes);

	ProduktSpozywczy* chleb = new ProduktSpozywczy("Chleb");
	dostawca->dostarczDoSklepu(chleb);

	ProduktPrzemyslowy* dlugopis = new ProduktPrzemyslowy("Dlugopis");
	dostawca->dostarczDoSklepu(dlugopis);

	ProduktSpozywczy* wodaMineralna = new ProduktSpozywczy("Woda mineralna");
	dostawca->dostarczDoSklepu(wodaMineralna);

	sklep->wyswietlProdukty();     

	
	if (sklep->isDostepny("Chleb"))
	{
		sklep->sprzedaj("Chleb");
	}
	
	if (sklep->isDostepny(notes)) {
		sklep->sprzedaj(notes->getNazwa());
	}
	
	cout << endl;
	
	sklep->wyswietlProdukty();

	

}
