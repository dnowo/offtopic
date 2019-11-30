#pragma once
#include <iostream>
#include <string>

using namespace std;

class DodatkoweWyposazenie
{
protected:
	string nazwa;
public:
	string getNazwa();
	DodatkoweWyposazenie(string nazwa);
	~DodatkoweWyposazenie();

};

