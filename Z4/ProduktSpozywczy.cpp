#include "ProduktSpozywczy.h"

ProduktSpozywczy::ProduktSpozywczy(string _nazwa)
{
	this->nazwa = _nazwa;

}

string ProduktSpozywczy::getNazwa()
{
	return this->nazwa;
}
