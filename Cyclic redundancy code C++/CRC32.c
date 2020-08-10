#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

unsigned int tab[256];
unsigned int wielomian = 0x04C11DB7;

void utworzTablice()
{
    for(int i = 0; i < 256; i++)
    {
        tab[i] = (unsigned int)i << 24;
        for (int j = 0; j < 8; j++)
        {
            if((tab[i] & 0x80000000) != 0)
            {
                tab[i] <<= 1;
                tab[i] ^= wielomian;
            }
            else
                tab[i] <<= 1;
        }
    }
}

int obliczCRC(string nazwa, ifstream &plik)
{
    unsigned int crc = 0;

    plik.open(nazwa.c_str(), ios::binary);

    if(!plik.is_open())
    {
        cout << "Blad otwarcia pliku do odczytu!" << endl;
        return -1;
    }

    unsigned char znak;
    while(plik)
    {
        plik.read((char*)&znak, 1);
        if(!plik)
            break;
        unsigned char i = (unsigned char)((crc ^ (znak << 24)) >> 24);
        crc = (crc << 8) ^ tab[i];
    }

    plik.close();
    return crc;
}

string decToBin(unsigned int liczba)
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

int zapiszCRC(unsigned int crc)
{
    ofstream plik;
    plik.open("crc32.crc32");

    if(!plik.is_open())
    {
        cout << "Blad otwarcia pliku do zapisu!" << endl;
        return -1;
    }

    string str, str2, strbin;
    str = decToBin(crc);
    strbin = str;
    if(strbin.length() < 32)
    {
        for(int i = 0; i < 32-str.length(); i++)
            strbin.insert(0, "0");
    }

    for(int i = 0; i < 4; i++)
    {
        str2 = strbin.substr(i*8, 8);
    	plik << (unsigned char)strtol(str2.c_str(), NULL, 2);
    }
    plik << endl;

    plik << strbin << endl;
    plik << hex << crc << endl;
    plik << dec << crc << endl;

    plik.close();
    return 0;
}

int main(int argc, char* argv[]) {

    if (argc < 2)
    {
        cout << "Nie podano nazwy pliku jako parametru wejsciowego!" << endl;
        return -1;
    }

    string nazwaPliku = argv[1];
    ifstream plik;

    cout << "Tworzenie tablicy CRC" << endl;

    utworzTablice();

    cout << "Obliczanie CRC dla calego pliku" << endl;

    int crc = obliczCRC(nazwaPliku, plik);

    cout << "Zapisywanie CRC do pliku" << endl;

    if(zapiszCRC(crc) == -1)
        return -1;

    return 0;
}