#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <list>
#include <cstdio>

using namespace std;

struct wezel {
    int symbol;
    int ile;
    wezel* lewy;
    wezel* prawy;
};

typedef wezel* pWezel;

int wczytaj_model(string nazwa, ifstream &plik, list<pWezel> &lista);
int stworzDrzewo(pWezel &korzen, list<pWezel> &lista);
int utworz_tabele(pWezel korzen);

int main(int argc, char* argv[]) {

    if (argc < 2)
    {
        cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
        return -1;
    }

    string nazwaPliku = argv[1];
    ifstream plik;
    pWezel korzen = NULL;
    list<pWezel> lista;

    cout << "Wczytywanie modelu zrodla informacji" << endl;

    if(wczytaj_model(nazwaPliku, plik, lista) == -1)
        return -1;

    cout << "Tworzenie drzewa kodowania" << endl;

    if (stworzDrzewo(korzen, lista) == -1)
        return -1;

    if (utworz_tabele(korzen) == -1)
        return -1;

    return 0;
}

bool porownaj(const pWezel &a, const pWezel &b)
{
    if(a->ile == b->ile)
        return a->symbol < b->symbol;
    return a->ile > b->ile;
}

int wczytaj_model(string nazwa, ifstream &plik, list<pWezel> &lista)
{
    plik.open(nazwa.c_str());

    if(!plik.is_open())
    {
        cout << "Blad otwarcia pliku do odczytu!" << endl;
        return -1;
    }

    int symbol;
    while(plik)
    {
        pWezel w = new wezel;
        plik >> symbol;
        if(!plik)
            break;
        plik >> w->ile;
        w->symbol = symbol;
        w->lewy = NULL;
        w->prawy = NULL;
        lista.push_back(w);
    }

    lista.sort(porownaj);

    plik.close();
    return 0;
}

void wypiszDrzewo(pWezel w, string &str, ofstream &plik)
{
    if (w)
    {
        plik << w->symbol << " " << str << endl;
        str += "0";
        wypiszDrzewo(w->lewy, str, plik);
        str.erase(str.length()-1);
        str += "1";
        wypiszDrzewo(w->prawy, str, plik);
        str.erase(str.length()-1);
    }
}

void wypiszLiscie(pWezel w, string &str, ofstream &plik)
{
    if(!w->lewy && !w->prawy)
    {
        plik << w->symbol << " " << str << endl;
    }
    else
    {
        str += "0";
        wypiszLiscie(w->lewy, str, plik);
        str.erase(str.length()-1);
        str += "1";
        wypiszLiscie(w->prawy, str, plik);
        str.erase(str.length()-1);
    }
}

void zapiszWezly(pWezel w, ofstream &plik)
{
    if(w && (w->lewy || w->prawy))
    {
        plik << w->symbol << " " << w->lewy->symbol << " " << w->prawy->symbol << endl;
        zapiszWezly(w->lewy, plik);
        zapiszWezly(w->prawy, plik);
    }
}

int stworzDrzewo(pWezel &korzen, list<pWezel> &lista)
{
    int zast = -1;
    list<pWezel>::reverse_iterator ritr1;
    list<pWezel>::reverse_iterator ritr2;

    while(lista.size() > 1)
    {
        ritr1 = lista.rbegin();
        ritr2 = ritr1;
        ++ritr2;
        pWezel w = new wezel;
        w->ile = (*ritr1)->ile + (*ritr2)->ile;
        w->lewy = *ritr1;
        w->prawy = *ritr2;
        w->symbol = zast--;
        lista.pop_back();
        lista.pop_back();
        lista.push_front(w);
        if(lista.size() > 1)
            lista.sort(porownaj);
    }

    korzen = *lista.begin();

    ofstream plik;
    plik.open("tree.tree");

    if(!plik.is_open())
    {
        cout << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    zapiszWezly(korzen, plik);
    plik.close();

    return 0;
}

int utworz_tabele(pWezel korzen)
{
    ofstream plik;
    string str = "";
    cout << "Tworzenie tabeli kodu dla calego drzewa" << endl;
    plik.open("coding.coding");

    if(!plik.is_open())
    {
        cout << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    wypiszDrzewo(korzen, str, plik);
    plik.close();

    cout << "Tworzenie tabeli kodowej dla lisci" << endl;
    plik.open("code.code");

    if(!plik.is_open())
    {
        cout << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    str = "";
    wypiszLiscie(korzen, str, plik);
    plik.close();

    return 0;
}
