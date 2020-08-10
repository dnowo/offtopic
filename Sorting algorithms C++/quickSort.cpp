#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
 
using namespace std;
 
vector<int> tablica;
void wyswietl()
{
    cout << " ";
    for(int i = 0; i < tablica.size();i++)
        cout << tablica[i];
}
int sortuj(int p,int r)
{
 
    int i = (p+r+1)/2;
    cout << tablica[i];
    int pivot = tablica[i];
    tablica[i] = tablica[r];
    int j = p;
   for(int i = p; i < r; i++)
   {
 
       if(tablica[i] < pivot)
       {
           swap(tablica[i],tablica[j]);
           j++;
       }
 
 
   }
   tablica[r] = tablica[j];
   tablica[j] = pivot;
   if(p < j-1)sortuj(p,j-1);
   if(j+1 < r)sortuj(j+1,r);
 
}
 
 
int main() {
    int stop = 0, steruj,wartosc,ile;
    while(stop != 1)
    {
        cin >> wartosc;
        if(wartosc == -1)
        {
            ile = tablica.size()-1;
            sortuj(0,ile);
            wyswietl();
            stop = 1;
        }
        else
        {
            tablica.push_back(wartosc);
        }
    }
    return 0;
}