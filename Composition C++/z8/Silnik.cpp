#include "Silnik.h"

Silnik::Silnik(int moc, int liczbaCylindrow)
{
	this->moc = moc;
	this->liczbaCylindrow = liczbaCylindrow;
}

int Silnik::getMoc()
{
	return moc;
}

int Silnik::getLiczbaCylindrow()
{
	return liczbaCylindrow;
}

Silnik::~Silnik()
{
}
