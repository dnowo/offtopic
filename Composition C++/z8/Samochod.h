#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Silnik.h"
#include "Kolo.h"
#include "DodatkoweWyposazenie.h"
using namespace std;

class Samochod
{
	Silnik* silnik;
	vector<Kolo*> kola;
	string nazwa;
	vector<DodatkoweWyposazenie*> wyposazenie;

public:
	static Samochod* dajWzorzec(string nazwa, int moc, int liczbaCylindrow, int rozmiarKol);
	void wyswietlSpecyfikacje();
	Samochod(Samochod& samochod);
	~Samochod();
	void dodajWyposazenie(DodatkoweWyposazenie* wyposazenie);
private:
	Samochod(string nazwa, int moc, int liczbaCylindrow, int rozmiarKol);
};

