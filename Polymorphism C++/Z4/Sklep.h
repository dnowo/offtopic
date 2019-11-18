#pragma once


#include <iostream>
#include <string>
#include "Produkt.h"
#include <vector>
using namespace std;

class Sklep
{
private:
	vector<Produkt*> produkty;

	int liczbaProduktow;
public:
	Sklep();
	int dodajDoMagazynu(Produkt *produkt);
	void sprzedaj(string nazwa);
	bool isDostepny(string nazwa);
	bool isDostepny(Produkt *produkt);
	void wyswietlProdukty();
};

