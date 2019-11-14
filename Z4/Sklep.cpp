#include "Sklep.h"

Sklep::Sklep()
{
	liczbaProduktow = 0;
}

int Sklep::dodajDoMagazynu(Produkt *produkt)
{
	produkty.push_back(produkt);
	liczbaProduktow++;
	return liczbaProduktow;
}

void Sklep::sprzedaj(string nazwa)
{
	vector<Produkt*>::iterator i;

	for (i = produkty.begin(); i != produkty.end(); i++) {
		if (!nazwa.compare((*i)->getNazwa())) {
			produkty.erase(i);
			liczbaProduktow--;
			break;
		}
	}


}

bool Sklep::isDostepny(string nazwa)
{
	vector<Produkt*>::iterator i;

	for (i = produkty.begin(); i != produkty.end(); i++) {
		if (!nazwa.compare((*i)->getNazwa()) ){
			return true;

		}
	}
	return false;
}

bool Sklep::isDostepny(Produkt *produkt)
{
	return isDostepny(produkt->getNazwa());
}

void Sklep::wyswietlProdukty()
{
	vector<Produkt*>::iterator i;

	for (i = produkty.begin(); i != produkty.end(); i++) {
		cout << (*i)->getNazwa() << " " << endl;
	}
}
