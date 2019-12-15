#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


int main()
{
    int oIleZnakow,znak;
    char wiadomosc[2048], nazwaPliku[50], ch;

    printf("Podaj nazwe pliku do zaszyfrowania: \n");
    scanf("%s", nazwaPliku);

    if( access( nazwaPliku, F_OK ) != -1 ) {
        printf("Podaj liczbe do klucza: \n");
        scanf("%i", &oIleZnakow);
    } else {
        printf("Podany plik nie istnieje!");
        exit(0);
    }

    if( access( nazwaPliku, R_OK ) == -1 ) {
        printf("Nie masz uprawnien do tego pliku!");
        exit(0);
    }

    FILE* fodczyt;
    fodczyt = fopen(nazwaPliku, "r");

    if (fodczyt == NULL)
    {
        perror("Nie moge otworzyc pliku\n");
        exit(EXIT_FAILURE);
    }
    int i=0;
    while ((ch = fgetc(fodczyt)) != EOF){
            wiadomosc[i] = ch;
            i++;
    }

    fclose(fodczyt);

    i=0;
    for (i = 0; wiadomosc[i] != '\0'; i++) {
        znak = wiadomosc[i];

        if (znak >= 'a' && znak <= 'z') {
            znak += (int)oIleZnakow;

            if (znak > 'z') {
                znak = znak - 'z' + 'a' - 1;
            }
            wiadomosc[i] = znak;
        }
        else if (znak >= 'A' && znak <= 'Z') {
            znak += (int)oIleZnakow;

            if (znak > 'z') {
                znak = znak - 'A' + 'Z' - 1;
            }
            wiadomosc[i] = znak;
        }
    }

    char nowaNazwaPliku[60] = "SZYFR";

    i=0;
    FILE *fzapis;

    fzapis = fopen(strcat( nowaNazwaPliku, nazwaPliku ), "w+");
    for(i = 0; wiadomosc[i] != '\0'; i++){
        fputc(wiadomosc[i], fzapis);
    }
    fclose(fzapis);

    printf("Zaszyfrowano do pliku: %s", nowaNazwaPliku);

    return 0;

}
