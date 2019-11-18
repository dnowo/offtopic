#pragma once
#include <iostream>
#include <string>
#include "Produkt.h"

using namespace std;

class ProduktSpozywczy : public Produkt
{
public:
	ProduktSpozywczy(string _nazwa);
	string getNazwa();
};

