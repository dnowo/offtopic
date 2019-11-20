#include "Box.h"
int Box::Nr = -1;
int Box::Nrkopii = -2;
Box::Box()
{
	Nr++;
	Nazwa += "i" + to_string(this->Nr);
	objetosc = 1;
	cout << "K: tworze " << Nazwa << " -def" << endl;
}

Box::Box(string _nazwa)
{
	Nr++;
	Nazwa = "i" + to_string(Nr)+ " " + _nazwa;
	objetosc = 1;
	cout << "K: tworze " << Nazwa << " -def" << endl;
}

Box::Box(string _nazwa, double _x)
{
	Nr++;
	Nazwa = "i" + to_string(Nr) + " " + _nazwa;
	objetosc = _x;
	
	cout << "K: tworze " << Nazwa << " -def" << endl;
}

Box::Box(string _nazwa, double _x, double _y, double _z)
{
	Nr++;
	Nazwa = "i" + to_string(Nr) + " " + _nazwa;
	objetosc = _x*_y*_z;
	cout << "K: tworze " << Nazwa << " -def" << endl;

}

Box::Box(const Box& box)
{
	Nr++;
	Nrkopii++;
	objetosc = box.objetosc;
	Nazwazrodlowegoobiektu = box.Nazwa;
	Nazwa = "i" + to_string(Nr) + " -kopia" + to_string(Nrkopii) + "_" + Nazwazrodlowegoobiektu;
	cout << "KK: tworze " << Nazwa << endl;

}

void Box::printVolume()
{
	cout << "V(" << Nazwa << ")=" << objetosc << endl;
}
