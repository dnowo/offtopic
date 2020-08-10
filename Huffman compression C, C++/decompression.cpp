#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;

int wczytajTabele(string nazwa, ifstream &plik);
int dekompresuj(string nazwa, ifstream &plikOdczyt, ofstream &plikZapis);

string tab[256];

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

    cout << "Wczytywanie tabeli kodowej" << endl;

    if(wczytajTabele(sCode, plikOdczyt) == -1)
        return -1;

    cout << "Wczytywanie pliku do dekompresji" << endl;

    if(dekompresuj(sPlik, plikOdczyt, plikZapis) == -1)
        return -1;

    return 0;
}

int wczytajTabele(string nazwa, ifstream &plik)
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
        plik >> symbol;
        if(!plik)
            break;
        plik >> tab[symbol];
    }

    plik.close();
    return 0;
}

string decToBin(int liczba)
{
    if (liczba == 0)
        return "0";
    if (liczba == 1)
        return "1";

    if (liczba % 2 == 0)
        return decToBin(liczba / 2) + "0";
    else
        return decToBin(liczba / 2) + "1";
}

int dekompresuj(string nazwa, ifstream &plikOdczyt, ofstream &plikZapis)
{
    plikOdczyt.open(nazwa.c_str(), ios::binary);
    plikZapis.open("dhuff.dhuff", ios::binary);

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

    cout << "Dekompresja pliku" << endl;

    unsigned char znak;
    string kod, str, str2;

    plikOdczyt.seekg(0, plikOdczyt.end);
    int dlugosc = (int)plikOdczyt.tellg();
    plikOdczyt.seekg(0, plikOdczyt.beg);

    int znaczace, ile;
    unsigned char buff;
    znaczace = plikOdczyt.get();
    dlugosc--;

    while(plikOdczyt)
    {
        plikOdczyt.read((char*)&buff, 1);
        znak = buff;
        if(plikOdczyt.good())
        {
            str = decToBin(znak);
            if(str.length() < 8)
            {
                if(dlugosc <= 1)
                {
                    //ile = znaczace - str.length();
                    ile = 8 - str.length();
                    for (int j = 0; j < ile; j++)
                        str.insert(0, "0");

                    str.erase(str.end()-(8-znaczace), str.end());
                }
                else
                {
                    ile = 8 - str.length();
                    for (int j = 0; j < ile; j++)
                        str.insert(0, "0");
                }
            }

            kod += str;
            while(kod.length() > 0)
            {
                str = kod.substr(0, 1);
                kod.erase(0, 1);
                str2 += str;
                for(int i = 0; i < 256; i++)
                {
                    if(tab[i] == str2)
                    {
                        plikZapis << (unsigned char)i;
                        str2.erase();
                        break;
                    }
                }
            }

            dlugosc--;
        }
    }

    plikOdczyt.close();
    plikZapis.close();

    return 0;
}