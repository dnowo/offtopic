#include "Samochod.h"

Samochod* Samochod::dajWzorzec(string nazwa, int moc, int liczbaCylindrow, int rozmiarKol)
{

	return new Samochod(nazwa, moc, liczbaCylindrow, rozmiarKol);

}

void Samochod::wyswietlSpecyfikacje()
{
	cout << "Nazwa samochodu: " << this->nazwa << endl;
	cout << "Moc samochodu: " << this->silnik->getMoc() << endl;
	cout << "Liczba cylindrow samochodu: " << this->silnik->getLiczbaCylindrow() << endl;
	for (int i = 0; i < 4; i++) {
		cout << "Rozmiar kola " << i << " to " << this->kola[i]->getRozmiar() << endl;
	}
	for (size_t i = 0; i < wyposazenie.size(); i++) {
		cout << "Dodatkowe wyposazenie: " << wyposazenie[i]->getNazwa() << endl;
	}
	
}

Samochod::Samochod(Samochod& samochod)
{
	this->nazwa = samochod.nazwa;
	silnik = new Silnik(samochod.silnik->getMoc(), samochod.silnik->getLiczbaCylindrow());
	for (int i = 0; i < 4; i++) {
		kola.push_back(new Kolo(samochod.kola[i]->getRozmiar()));
	}
}

Samochod::~Samochod()
{
	delete silnik;
	for (size_t i = 0; i < kola.size(); i++) {
		delete kola[i];
	}
	for (size_t i = 0; i < wyposazenie.size(); i++) {
		delete wyposazenie[i];
	}

}

void Samochod::dodajWyposazenie(DodatkoweWyposazenie* wyposazenie)
{
	this->wyposazenie.push_back(wyposazenie);
}

Samochod::Samochod(string nazwa, int moc, int liczbaCylindrow, int rozmiarKol)
{
	this->nazwa = nazwa;
	silnik = new Silnik(moc, liczbaCylindrow);
	for (int i = 0; i < 4; i++) {
		kola.push_back(new Kolo(rozmiarKol));
	}
}
