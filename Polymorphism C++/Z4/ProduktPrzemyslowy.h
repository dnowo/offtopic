#pragma once
#include <iostream>
#include <string>
#include "Produkt.h"

using namespace std;

class ProduktPrzemyslowy: public Produkt
{
public:
	ProduktPrzemyslowy(string _nazwa);

	string getNazwa();
};

