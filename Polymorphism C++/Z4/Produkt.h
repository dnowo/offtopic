#pragma once
#include <iostream>
#include <string>

using namespace std;

class Produkt
{
protected:
	string nazwa;
public:
	Produkt();
	virtual string getNazwa();
};

