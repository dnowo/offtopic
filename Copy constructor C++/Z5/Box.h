#pragma once
#include <string>
#include <iostream>
using namespace std;
class Box
{
public:
	string Nazwa;
	static int Nr;
	string Nazwazrodlowegoobiektu;
	static int Nrkopii;
	double objetosc;

	Box();
	Box(string);
	Box(string, double);
	Box(string, double, double, double);
	Box(const Box &box);
    void printVolume();
};
