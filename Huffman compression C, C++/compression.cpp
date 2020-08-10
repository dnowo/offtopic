#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <list>
#include <cstdio>

using namespace std;

struct para {
    unsigned char symbol;
    string kod;
};

int wczytajTabele(string nazwa, ifstream &plik, list<para> &lista);
int kompresuj(string nazwa, ifstream &plikOdczyt, ofstream &plikZapis, list<para> &lista);

int main(int argc, char* argv[]) {

    if (argc < 3)
    {
        cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
        return -1;
    }

    string sCode = argv[1];
    string sPlik = argv[2];
    ifstream plikOdczyt;
    ofstream plikZapis;
    list<para> lista;

    cout << "Wczytywanie tabeli kodowej" << endl;

    if(wczytajTabele(sCode, plikOdczyt, lista) == -1)
        return -1;

    cout << "Wczytywanie pliku do kompresji" << endl;

    if(kompresuj(sPlik, plikOdczyt, plikZapis, lista) == -1)
        return -1;

    return 0;
}

int wczytajTabele(string nazwa, ifstream &plik, list<para> &lista)
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
        para* w = new para;
        plik >> symbol;
        if(!plik)
            break;
        plik >> w->kod;
        w->symbol = (unsigned char)symbol;
        lista.push_back(*w);
    }

    plik.close();
    return 0;
}

int kompresuj(string nazwa, ifstream &plikOdczyt, ofstream &plikZapis, list<para> &lista)
{
    plikOdczyt.open(nazwa.c_str(), ios::binary);
    plikZapis.open("huff.huff", ios::binary);

    if(!plikOdczyt.is_open())
    {
        cout << "Blad otwarcia pliku do odczytu!" << endl;
        return -1;
    }

    if(!plikZapis.is_open())
    {
        cout << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    cout << "Kompresowanie pliku" << endl;

    list<para>::iterator i;
    unsigned char znak, ostbity = 0;
    string str, str2;

    unsigned char buff;
    buff = 8;
    plikZapis.write((char*)&buff, 1);

    while(plikOdczyt)
    {
        znak = (unsigned char)plikOdczyt.get();
        if(plikOdczyt.good())
        {
            for(i = lista.begin(); i != lista.end(); ++i)
            {
                if(i->symbol == znak)
                {
                    str += i->kod;
                    if(str.length() >= 8)
                    {
                        str2 = str.substr(0, 8);
                        str.erase(0, 8);
                        buff = (unsigned char)strtol(str2.c_str(), NULL, 2);
                        plikZapis.write((char*)&buff, 1);
                    }
                    ostbity = str.length();
                    break;
                }
            }
        }
    }

    if(str.length() > 0)
    {
        for(int j = 0; j < 8-ostbity; j++)
            str += "0";

        buff = (unsigned char)strtol(str.c_str(), NULL, 2);
        plikZapis.write((char*)&buff, 1);

        buff = ostbity;
        plikZapis.seekp(0);
        plikZapis.write((char*)&buff, 1);
    }

    plikOdczyt.close();
    plikZapis.close();

    return 0;
}