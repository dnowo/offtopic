#pragma once
#include <iostream>
#include <string>
using namespace std;
class Silnik
{	
	int moc;
	int liczbaCylindrow;
public:
	
	Silnik(int moc=0, int liczbaCylindrow=0);
	int getMoc();
	int getLiczbaCylindrow();
	~Silnik();
};

