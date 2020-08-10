#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <list>

using namespace std;

struct para {
    unsigned char znak;
    int ile;
};

int ile(string nazwa, ifstream &plik);
int licz(string nazwa, ifstream &plik, list<para> &lista);
int sortuj(list<para> &lista);

int main(int argc, char* argv[]) {

    if (argc < 2)
    {
        cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
        return -1;
    }

    string nazwaPliku = argv[1];
    ifstream plik;

    cout << "Liczenie symboli wystepujacych w pliku" << endl;

    if (ile(nazwaPliku, plik) == -1)
        return -1;

    cout << "Policzono symbole. Zapisano do pliku.\n" << endl;

    cout << "Tworzenie tabeli symboli wystepujacych w pliku" << endl;

    list<para> lista;

    if (licz(nazwaPliku, plik, lista) == -1)
        return -1;

    cout << "Utworzono tabele symboli. Zapisano do pliku.\n" << endl;

    cout << "Sortowanie tabeli symboli" << endl;

    if (sortuj(lista) == -1)
        return -1;

    cout << "Tabela posortowana malejaco. Zapisano do pliku.\n" << endl;

    return 0;
}

int ile(string nazwa, ifstream &plik)
{
    plik.open(nazwa.c_str(), ios::binary);

    if(!plik.is_open())
    {
        cout << "Blad otwarcia pliku do odczytu!" << endl;
        return -1;
    }

    int ile = 0;

    while(plik)
    {
        if(plik.get() != EOF)
            ile++;
    }

    plik.close();

    ofstream plikZapis;
    plikZapis.open("ile.ile");

    if(!plikZapis.is_open())
    {
        cout << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    plikZapis << ile << endl;
    plikZapis.close();

    return ile;
}

int licz(string nazwa, ifstream &plik, list<para> &lista)
{
    plik.open(nazwa.c_str(), ios::binary);
    unsigned char znak;

    if(!plik.is_open())
    {
        cout << "Blad otwarcia pliku do odczytu!" << endl;
        return -1;
    }

    list<para>::iterator itr;

    while(plik)
    {
        znak = (unsigned char)plik.get();
        if(plik.good())
        {
            for (itr = lista.begin(); itr != lista.end(); ++itr) {
                if(itr->znak == znak)
                {
                    itr->ile++;
                    break;
                }
            }
            if(itr == lista.end())
            {
                para* p = new para;
                p->znak = znak;
                p->ile = 1;
                lista.push_back(*p);
            }
        }
    }

    plik.close();

    ofstream plikZapis;
    plikZapis.open("licz.licz");

    if(!plikZapis.is_open())
    {
        cout << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    for (itr = lista.begin(); itr != lista.end(); ++itr) {
        plikZapis << (int)itr->znak << " " << itr->ile << '\n';
    }
    plikZapis.close();

    return 0;
}

bool porownaj(const para &a, const para &b)
{
    if(a.ile == b.ile)
        return a.znak < b.znak;
    return a.ile > b.ile;
}

int sortuj(list<para> &lista)
{
    lista.sort(porownaj);

    ofstream plikZapis;
    plikZapis.open("msort.msort");

    if(!plikZapis.is_open())
    {
        cout << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    list<para>::iterator itr;
    for (itr = lista.begin(); itr != lista.end(); ++itr) {
        plikZapis << (int)itr->znak << " " << itr->ile << '\n';
    }
    plikZapis.close();

    return 0;
}