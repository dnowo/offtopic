#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;

ifstream wczytaj;
int ilosc = 0;
int tablica[10000];
int help[10000];

void wczytaj_dane(string plik)
{
    wczytaj.open(plik.c_str());
    if(!wczytaj.good())
        return;

    for(int i = 0; i < ilosc; i++)
    {
        wczytaj >> help[i];
    }
    wczytaj.close();
}
void przepisywanko()
{
    for(int i = 0; i < ilosc; i++)
    {
        tablica[i] = help[i];
    }
}

void bubble_sort()
{
    for(int i = 0; i < ilosc; i++)
        for(int j = 1; j < ilosc-i; j++)
            if(tablica[j-1] > tablica[j])
                swap(tablica[j-1], tablica[j]);
}
/* Sortowanie Kubelkowe */
void bucket_sort()
{
    int n=ilosc, i, j;
    int max=tablica[0];
    int min=tablica[0];

    for(i = 0; i < n; i++)
    {
        if (tablica[i] > max) max = tablica[i];
        else if(tablica[i] < min) min = tablica[i];
    }

    int* buck = new int[max-min+1];

    for(i = min; i <= max; i++)
        buck[i - min] = 0;

    for(i = 0; i < ilosc; i++)
        buck[tablica[i] - min]++;

    j = 0;
    for(i = min; i <= max; i++)
    {
        while (buck[i - min]--)
            tablica[j++] = i;
    }

    delete[] buck;
}
/*Sortowanie przez wstawianie*/
void insert_sort()
{
    int n = ilosc;
    int pom, i, j;

    for(i=1; i<n; i++)
    {
        pom=tablica[i];
        j=i-1;
        while(j>=0 && tablica[j]>pom)
        {
            tablica[j+1]=tablica[j];
            j--;
        }
        tablica[j+1]=pom;
    }
}
/*Sortowanie przez zliczanie*/
int getMaxx() {
    int size = ilosc;
    int max = tablica[1];
    for(int i = 2; i<=size; i++) {
        if(tablica[i] > max)
            max = tablica[i];
    }
    return max;
}
void count_sort() {
    int size = ilosc;
    int* output = new int[size+1];
    int max = getMaxx();
    int* count = new int[max+1];
    for(int i = 0; i<=max; i++)
        count[i] = 0;
    for(int i = 1; i <=size; i++)
        count[tablica[i]]++;
    for(int i = 1; i<=max; i++)
        count[i] += count[i-1];
    for(int i = size; i>=1; i--) {
        output[count[tablica[i]]] = tablica[i];
        count[tablica[i]] -= 1;
    }
    for(int i = 1; i<=size; i++) {
        tablica[i] = output[i];
    }
    delete[] output;
    delete[] count;
}
/*Pozycyjne*/
int getMax(int n) {
    int max = tablica[0];
    for (int i = 1; i < n; i++){
        if (tablica[i] > max)
            max = tablica[i];
    }
    return max;
}

void countSort(int exp) {
    int n = ilosc;
    int* output = new int[ilosc];
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[ (tablica[i]/exp)%10 ]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        output[count[ (tablica[i]/exp)%10 ] - 1] = tablica[i];
        count[ (tablica[i]/exp)%10 ]--;
    }

    for (i = 0; i < n; i++)
        tablica[i] = output[i];

    delete[] output;
}

void radix_sort() {
    int m = getMax(ilosc);

    for (int exp = 1; m/exp > 0; exp *= 10)
        countSort(exp);
}
/*Sortowanie przez wstawianie*/
void scalanie(int lewy,int srodek,int prawy){
    int* tab_pomocnicza = new int[ilosc];
    int lewy1;
    int lewy2;
    int srodek1;
    for (lewy1 = lewy; lewy1 <= prawy; lewy1++) {
        tab_pomocnicza[lewy1]=tablica[lewy1];
    }
    lewy1=lewy;
    lewy2=lewy;
    srodek1=srodek+1;
    while(lewy1<=srodek && srodek1<=prawy) {
        if (tab_pomocnicza[lewy1] < tab_pomocnicza[srodek1]) {
            tablica[lewy2] = tab_pomocnicza[lewy1];
            lewy2++;
            lewy1++;
        } else {
            tablica[lewy2] = tab_pomocnicza[srodek1];
            lewy2++;
            srodek1++;
        }
    }
    while(lewy1<=srodek){
        tablica[lewy2]=tab_pomocnicza[lewy1];
        lewy2++;
        lewy1++;
    }
    delete[] tab_pomocnicza;
}

void rozbijanie(int lewy, int prawy){
    int srodek;

    if(lewy<prawy) {
        srodek = (prawy + lewy) / 2;
        rozbijanie(lewy,srodek);
        rozbijanie(srodek+1,prawy);
        scalanie(lewy,srodek,prawy);
    }
}
void scalanie_sort()
{
    rozbijanie(0,ilosc-1);
}

void pauza()
{
    int x=ilosc;
    int y=2*x;

    for(int i=0;i<ilosc;i++)
    {
        tablica[y]=0;
        tablica[y-1]=tablica[x-1];
        tablica[x-1]=0;
        x--;
        y=y-2;
    }
}

void scalanieB()
{
    int x=0;
    for(int i=0;i<=2*ilosc;i++)
    {
        if(tablica[i]!=0)
        {
            tablica[x]=tablica[i];
            x++;
            tablica[i]=0;
        }
    }
}

void library_sort()
{
    int pom=1;
    while(pom!=0)
    {
        pom=0;
        pauza();

        int i=1;
        int wyz=0;
        while(wyz!=ilosc)
        {
            for(int j=i+2;j<(2*ilosc);j=j+2)
            {
                if(tablica[i]>tablica[j])
                {
                    tablica[j+1]=tablica[i];
                    tablica[i]=0;
                    pom++;
                }
                i=i+2;
            }
            wyz++;
        }
        scalanieB();
    }
}

int main(int argc, char* argv[])
{
    ofstream zapisz;
    zapisz.open("wyniki.txt");

    string nazwy[8] = {"10.txt", "10p.txt", "100.txt", "100p.txt", "1000.txt", "1000p.txt", "10000.txt", "10000p.txt"};
    int ilosci[4] = {10, 100, 1000, 10000};
    int testy = 100;
    double czas = 0;
    typedef void (*func)();
    func tabf[7] = {bubble_sort, bucket_sort, insert_sort, count_sort, radix_sort, scalanie_sort, library_sort};

    for(int p = 0; p < 8; p++)
    {
        ilosc = ilosci[p/2];
        wczytaj_dane(nazwy[p]);
        przepisywanko();
        for(int j = 0; j < 7; j++)
        {
            czas = 0;
            for (int i = 0; i < testy; i++)
            {
                clock_t begin = clock();
                tabf[j]();
                clock_t end = clock();
                czas += double(end - begin) / CLOCKS_PER_SEC;
                przepisywanko();
            }

            zapisz << setprecision(8) <<(double)czas << endl;
        }
        zapisz << " ----- " << endl;
    }

    zapisz.close();

    return 0;
}