#pragma once
#include <iostream>
#include <string>
#include "Produkt.h"
#include "Sklep.h"

using namespace std;

class Dostawca
{
private:
	Sklep* sklep;
public:
	Dostawca(Sklep *_sklep);
	void dostarczDoSklepu(Produkt *produkt);
};

