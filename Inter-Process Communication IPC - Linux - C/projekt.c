/*
        Daniel Nowosielecki
            WCYI8Y2S1
./projekt 1 - Wersja interaktywna
./projekt 2 nazwaPliku - Wersja odczytu z pliku
./projekt 3 - Wersja odczytu pliku urandom
 
kill -SIGINT pid  -> Zakończ program
kill -SIGUSR1 pid  -> Zatrzymaj program
kill -SIGUSR2 pid  -> Wznów program
 
 
 // Tak wiem, że mogłem ograniczyć ilość kodu :) Nijak to się ma do wymagań prowadzącego...
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
 
#define READ 0
#define WRITE 1
 
#define TAB_SIZE_INTER 256
#define BUFF_SIZE_INTER 32
#define SHM_SIZE 16
 
#define BUFF_SIZE_FILE 31
 
int     potok[2],
        potokRozmiar[2],
        potokPid1[2],
        potokPid2[2],
        potokPid3[2];
 
int 	procesGlownyId,
        proces1 = -1,
        proces2 = -1,
        proces3 = -1,
        shmid,
        semid,
        wybierzTryb=0,
        wpid,
        status,
        praca=1;
       
unsigned char   *nazwaPliku,
            daneInter[TAB_SIZE_INTER];
 
unsigned char   *wskShm;
 
static struct sembuf buf;
 
key_t   key;
 
void podnies(int semid, int semnum);
void opusc(int semid, int semnum);
 
void wykonajTryb();
 
void inter_P1();
void inter_P2();
void inter_P3();
 
void plik_P1();
void plik_P2();
void plik_P3();
 
void dev_P1();
 
void zakoncz();
void wznow(int signal);
void zatrzymaj(int signal);
 
void sprzataj();
 
int main(int argc, char *argv[]){
    procesGlownyId = getpid();
    printf("Program rozpoczyna prace: %i\n", getpid());
    if(argc < 2){
        printf("Nie podales argumentow!");
        exit(0);
    }
    if(!strcmp(argv[1],"1")){
        wybierzTryb=1;
        printf("Otworzyles tryb interaktywny!\n");
    } else if(!strcmp(argv[1],"2") && argc > 2){
        wybierzTryb=2;
        nazwaPliku = argv[2];
        printf("Otworzyles tryb odczytu z pliku!\n");
    } else if(!strcmp(argv[1],"3")){
        wybierzTryb=3;
        nazwaPliku = "/dev/urandom";
        printf("Otworzyles tryb odczytu z /dev/urandom!\n");
    } else{
        wybierzTryb=0;
        printf("Niestety, podales zle argumenty! Koncze prace\n");
    }      
 
    /* Komunikacja P2 z P3 poprzez pamięć współdzieloną. */
    semid = semget(45281, 2, IPC_CREAT|0600);
       
    if (semid == -1){
        perror("Utworzenie tablicy semaforow");
        exit(1);
    }
       
    if (semctl(semid, 0, SETVAL, (unsigned char)SHM_SIZE) == -1){
        perror("Nadanie wartosci semaforowi 0");
        exit(1);
    }
   
    if (semctl(semid, 1, SETVAL, (unsigned char)0) == -1){
        perror("Nadanie wartosci semaforowi 1");
        exit(1);
    }
   
    shmid = shmget(45281, SHM_SIZE*sizeof(unsigned char), IPC_CREAT|0600);
   
    if (shmid == -1){
        perror("Utworzenie segmentu pamieci wspoldzielonej");
        exit(1);
    }
   
    wskShm = (unsigned char*)shmat(shmid, NULL, 0);
 
    if (wskShm == NULL){
        perror("Przylaczenie segmentu pamieci wspoldzielonej");
        exit(1);
    }
       
    /* Przetwarzanie potokowe, lacze nienazwane */
    pipe(potok);
    pipe(potokRozmiar);
    pipe(potokPid1);
    pipe(potokPid2);
    pipe(potokPid3);
 
    /* Obsługa sygnałów procesu rodzica */
    signal(SIGUSR1, zatrzymaj);
    signal(SIGUSR2, wznow);
    signal(SIGINT, zakoncz);
    while(!praca);
 
    /* Wybór trybu pracy i utworzenie procesów */
    wykonajTryb();
 
    return 0;
}
 
void wykonajTryb(){
    switch(wybierzTryb){
        case 1:
        printf("Wprowadz dane: \n");
        fgets(daneInter,sizeof(daneInter),stdin);
       
        /* Tworzenie procesow */
        if (procesGlownyId == getpid()) proces1 = fork();
        if (procesGlownyId == getpid()) proces2 = fork();
        if (procesGlownyId == getpid()) proces3 = fork();
       
        /* Przekazywanie sterowania odpowiednim dla odpowiednich funkcji */
        if (proces1 == 0) inter_P1();
        if (proces2 == 0) inter_P2();
        if (proces3 == 0) inter_P3();
        if (procesGlownyId == getpid()){
           
            close(potokPid1[READ]);
            write(potokPid1[WRITE], &proces2, sizeof(proces2));
            write(potokPid1[WRITE], &proces3, sizeof(proces3));
            close(potokPid1[WRITE]);
           
            while((wpid = wait(&status)) > 0);
            printf("\nProgram konczy prace. %d\n", getpid());
            sprzataj();
        }
        break;
           
        case 2:
        /* Tworzenie procesow */
        if (procesGlownyId == getpid()) proces1 = fork();
        if (procesGlownyId == getpid()) proces2 = fork();
        if (procesGlownyId == getpid()) proces3 = fork();
       
        /* Przekazywanie sterowania odpowiednim dla odpowiednich funkcji */
        if (proces1 == 0) plik_P1();
        if (proces2 == 0) plik_P2();
        if (proces3 == 0) plik_P3();
        if (procesGlownyId == getpid()){
           
            close(potokPid1[READ]);
            write(potokPid1[WRITE], &proces2, sizeof(proces2));
            write(potokPid1[WRITE], &proces3, sizeof(proces3));
            close(potokPid1[WRITE]);
           
           
            while((wpid = wait(&status)) > 0);
            printf("\nProgram konczy prace. %d\n", getpid());
            sprzataj();
        }
        break;
           
        case 3:
        /* Tworzenie procesow */
        if (procesGlownyId == getpid()) proces1 = fork();
        if (procesGlownyId == getpid()) proces2 = fork();
        if (procesGlownyId == getpid()) proces3 = fork();
       
        /* Przekazywanie sterowania odpowiednim dla odpowiednich funkcji */
        if (proces1 == 0) dev_P1();
        if (proces2 == 0) plik_P2();
        if (proces3 == 0) plik_P3();
        if (procesGlownyId == getpid()){
           
            close(potokPid1[READ]);
            write(potokPid1[WRITE], &proces2, sizeof(proces2));
            write(potokPid1[WRITE], &proces3, sizeof(proces3));
            close(potokPid1[WRITE]);
   
            while((wpid = wait(&status)) > 0);
            printf("\nProgram konczy prace. %d\n", getpid());
            sprzataj();
        }
        break;
           
        default:
        /* Wyjdz gdy zla operacja */
        exit(0);
        break;
    }
}
//
/* //////////////// Tryb odczytu /dev/urandom //////////////// */
//
void dev_P1(){
    // Odbiór i przesłanie PID procesów
    proces1 = getpid();
   
    close(potokPid1[WRITE]);
    read(potokPid1[READ], &proces2, sizeof(proces2));
    read(potokPid1[READ], &proces3, sizeof(proces3));
    close(potokPid1[WRITE]);
   
    printf("\n** Proces 1 ma pid: %d ,P2: (%d), P3: (%d) \n", proces1,proces2,proces3);
   
    close(potokPid2[READ]);
    write(potokPid2[WRITE], &proces1, sizeof(proces1));
    write(potokPid2[WRITE], &proces3, sizeof(proces3));
    close(potokPid2[WRITE]);
   
    unsigned char buffor[BUFF_SIZE_FILE + 1];
    int i,stop=0;
    FILE *fp = fopen(nazwaPliku, "r");
 
    signal(SIGUSR1, zatrzymaj);
    signal(SIGUSR2, wznow);
    signal(SIGINT, zakoncz);
 
    close(potok[READ]);
   
    if (fp != NULL) {
        while(!stop){
            while(!praca);
            size_t newLen = fread(buffor, sizeof(unsigned char), BUFF_SIZE_FILE+1, fp);
            if ( ferror( fp ) != 0 ) {
                fputs("Error reading file", stderr);
            } else {
                buffor[newLen++] = '\0';
               
            }
            //printf("Proces 1: %s\n", buffor);
            write(potok[WRITE],buffor,sizeof(buffor));
            sleep(1);
            memset(buffor,0,sizeof(buffor));
        }
        fclose(fp);
    }
 
}
//
/* //////////////// Tryb odczytu z pliku //////////////// */
//
void plik_P1(){
 
    // Odbiór i przesłanie PID procesów
    proces1 = getpid();
   
    close(potokPid1[WRITE]);
    read(potokPid1[READ], &proces2, sizeof(proces2));
    read(potokPid1[READ], &proces3, sizeof(proces3));
    close(potokPid1[WRITE]);
   
    printf("\n** Proces 1 ma pid: %d ,P2: (%d), P3: (%d) \n", proces1,proces2,proces3);
   
    close(potokPid2[READ]);
    write(potokPid2[WRITE], &proces1, sizeof(proces1));
    write(potokPid2[WRITE], &proces3, sizeof(proces3));
    close(potokPid2[WRITE]);
   
    signal(SIGUSR1, zatrzymaj);
    signal(SIGUSR2, wznow);
    signal(SIGINT, zakoncz);
 
    unsigned char buffor[BUFF_SIZE_FILE + 1];
    int i,stop=0;
    FILE *fp = fopen(nazwaPliku, "rb");
   
    close(potok[READ]);
   
    if (fp != NULL) {
        while(!stop){
            while(!praca);
            size_t newLen = fread(buffor, sizeof(unsigned char), BUFF_SIZE_FILE+1, fp);
            if ( ferror( fp ) != 0 ) {
                fputs("Error reading file", stderr);
            } else {
                buffor[newLen++] = '\0';
            }
            for(i =0;i<sizeof(buffor);i++){
                if(buffor[i] == '\0'){
                    stop = 1;
                    break;
                }
            }
            //printf("Proces 1: %s\n", buffor);
            write(potok[WRITE],buffor,sizeof(buffor));
            memset(buffor,0,sizeof(buffor));
        }
        fclose(fp);
    }
 
}
 
void plik_P2(){
    proces2 = getpid();
   
    // Odbior pid i przeslanie pozostalych
    close(potokPid2[WRITE]);
    read(potokPid2[READ], &proces1, sizeof(proces2));
    read(potokPid2[READ], &proces3, sizeof(proces3));
    close(potokPid2[WRITE]);
   
    printf("\n** Proces 2 ma pid: %d ,P1: (%d), P3: (%d) \n", proces2,proces1,proces3);
   
    close(potokPid3[READ]);
    write(potokPid3[WRITE], &proces1, sizeof(proces1));
    write(potokPid3[WRITE], &proces2, sizeof(proces2));
    close(potokPid3[WRITE]);
   
    signal(SIGUSR1, zatrzymaj);
    signal(SIGUSR2, wznow);
    signal(SIGINT, zakoncz);
   
    unsigned char buffor[BUFF_SIZE_FILE+1];
   
    int stop=0,
        i;
       
    close(potok[WRITE]);
   
    while(!stop){
        while(!praca);
        read(potok[READ], buffor, sizeof(buffor));
        for(i=0;i<sizeof(buffor);i++){
            if(buffor[i]=='\0'){ stop = 1; break; }
        }
       
        //printf("Proces 2: %s\n", buffor);
       
        // Alokuje miejsce na zapis HEX rozm*2B+1
        unsigned char hex[sizeof(buffor)*2+1];
        unsigned char *ptr = &hex[0];
        int rozmiarDanych = 0;
       
        memset(hex,0,sizeof(hex));
       
        // Zamieniam dane z (buffor) na HEX.
        for(i=0; i<sizeof(buffor); i++){
            if(buffor[i] == '\0') {
                break;
            }
            rozmiarDanych++;
            ptr += sprintf(ptr, "%02X", buffor[i]);
        }
        // Tablica hex jest pełna tutaj. Rozmiar jest 2x większy odebranych danych na hex.
        rozmiarDanych *= 2;
        //printf("%s (%d)\n", hex, rozmiarDanych);
       
        //Wysyłam rozmiar danych do P3
        close(potokRozmiar[READ]);
        write(potokRozmiar[WRITE], &rozmiarDanych, sizeof(rozmiarDanych));
 
        //Zapis do pamięci wspoldzielonej
        for(i=0;i<rozmiarDanych;i++){
            opusc(semid, 0);
            wskShm[i] = hex[i];
            podnies(semid, 1); 
        }
        //printf("%s", wskShm);
    }
}
 
void plik_P3(){
    // Odbior pid i przeslanie pozostalych
    proces3 = getpid();
    close(potokPid3[WRITE]);
    read(potokPid3[READ], &proces1, sizeof(proces1));
    read(potokPid3[READ], &proces2, sizeof(proces2));
    close(potokPid3[WRITE]);
   
    printf("\n** Proces 3 ma pid: %d ,P1: (%d), P2: (%d) \n", proces3,proces1,proces2);
   
    signal(SIGUSR1, zatrzymaj);
    signal(SIGUSR2, wznow);
    signal(SIGINT, zakoncz);
   
    int     i,
            stop=0,
            rozmiarDanych,
            licz=0;
 
    while(!stop){
        // Odbieram rozmiar danych hex
        close(potokRozmiar[WRITE]);
        read(potokRozmiar[READ], &rozmiarDanych, sizeof(rozmiarDanych));
        //printf("[%d]\n", rozmiarDanych);
        if(rozmiarDanych<64) stop = 1;
 
            for(i=0; i<rozmiarDanych; i++){
                    opusc(semid, 1);
 
                    if(licz == 15){
                        fprintf(stderr, "\n");
                        licz = 0;
                    }else if(licz%2 == 0 && licz !=0){
                                fprintf(stderr, " ");
                            }
                    fprintf(stderr, "%c", wskShm[i]);
                    licz++;
                    podnies(semid, 0);
            }
        sleep(1);
    }
}
//
/* //////////////// Tryb Interaktywny //////////////// */
//
void inter_P1(){
 
    // Odbiór i przesłanie PID procesów
    proces1 = getpid();
   
    close(potokPid1[WRITE]);
    read(potokPid1[READ], &proces2, sizeof(proces2));
    read(potokPid1[READ], &proces3, sizeof(proces3));
    close(potokPid1[WRITE]);
   
    printf("\n** Proces 1 ma pid: %d ,P2: (%d), P3: (%d) \n", proces1,proces2,proces3);
   
    close(potokPid2[READ]);
    write(potokPid2[WRITE], &proces1, sizeof(proces1));
    write(potokPid2[WRITE], &proces3, sizeof(proces3));
    close(potokPid2[WRITE]);
   
    signal(SIGUSR1, zatrzymaj);
    signal(SIGUSR2, wznow);
    signal(SIGINT, zakoncz);
   
    unsigned char buffor[BUFF_SIZE_INTER];
    int i=0,
        j=0,
        stopInter=0;
       
    memset(buffor,0,sizeof(buffor));
   
    while(daneInter[i] != '\0'){
        while(!praca);
        if(j == BUFF_SIZE_INTER){
            j=0;
            // Zamkniecie deskryptora odczytu i wysłanie buffora do P2
            close(potok[READ]);
            write(potok[WRITE],buffor,sizeof(buffor));
            memset(buffor,0,sizeof(buffor));
        }
        buffor[j]=daneInter[i];
        i++;
        j++;
    }
 
    // Zamkniecie deskryptora odczytu i wysłanie buffora do P2
    close(potok[READ]);
    write(potok[WRITE],buffor,sizeof(buffor));
}
 
void inter_P2(){
    proces2 = getpid();
   
    // Odbior pid i przeslanie pozostalych
    close(potokPid2[WRITE]);
    read(potokPid2[READ], &proces1, sizeof(proces2));
    read(potokPid2[READ], &proces3, sizeof(proces3));
    close(potokPid2[WRITE]);
   
    printf("\n** Proces 2 ma pid: %d ,P1: (%d), P3: (%d) \n", proces2,proces1,proces3);
   
    close(potokPid3[READ]);
    write(potokPid3[WRITE], &proces1, sizeof(proces1));
    write(potokPid3[WRITE], &proces2, sizeof(proces2));
    close(potokPid3[WRITE]);
 
    signal(SIGUSR1, zatrzymaj);
    signal(SIGUSR2, wznow);
    signal(SIGINT, zakoncz);
   
    unsigned char buffor[BUFF_SIZE_INTER],
         copyBuff[BUFF_SIZE_INTER];
    int stop=0,i;
   
    while(!stop){
        while(!praca);
        close(potok[WRITE]);
        read(potok[READ], buffor, sizeof(buffor));
        for(i=0;i<sizeof(buffor);i++){
            if(buffor[i]=='\0'){ stop = 1; break; }
        }
       
        /* Kopia buffora hex */
        //printf("%s\n", buffor);
        for(i=0;i<sizeof(copyBuff);i++){
            copyBuff[i] = buffor[i];
        }
       
        //printf("%s\n", copyBuff);
        // Alokuje miejsce na zapis HEX rozm*2B+1
        unsigned char hex[sizeof(copyBuff)*2+1];
        unsigned char *ptr = &hex[0];
        int rozmiarDanych = 0;
       
        memset(hex,0,sizeof(hex));
       
        // Zamieniam dane z copyBuff (buffor) na HEX.
        for(i=0; i<sizeof(copyBuff); i++){
            if(copyBuff[i] == '\0') {
                break;
            }
            rozmiarDanych++;
            ptr += sprintf(ptr, "%02X", copyBuff[i]);
        }
        // Tablica hex jest pełna tutaj. Rozmiar jest 2x większy odebranych danych na hex.
        rozmiarDanych *= 2;
 
        //Wysyłam rozmiar danych do P3
        close(potokRozmiar[READ]);
        write(potokRozmiar[WRITE], &rozmiarDanych, sizeof(rozmiarDanych));
       
        //Zapis do pamięci wspoldzielonej
        for(i=0;i<rozmiarDanych;i++){
            opusc(semid, 0);
            wskShm[i] = hex[i];
            podnies(semid, 1); 
        }
    }
}
 
void inter_P3(){
    // Odbior pid i przeslanie pozostalych
    proces3 = getpid();
    close(potokPid3[WRITE]);
    read(potokPid3[READ], &proces1, sizeof(proces1));
    read(potokPid3[READ], &proces2, sizeof(proces2));
    close(potokPid3[WRITE]);
   
    printf("\n** Proces 3 ma pid: %d ,P1: (%d), P2: (%d) \n", proces3,proces1,proces2);
   
    int     i,
            stop=0,
            rozmiarDanych,
            licz=0;
 
    signal(SIGUSR1, zatrzymaj);
    signal(SIGUSR2, wznow);
    signal(SIGINT, zakoncz);
 
    while(!stop){
        while(!praca);
        // Odbieram rozmiar danych hex
        close(potokRozmiar[WRITE]);
        read(potokRozmiar[READ], &rozmiarDanych, sizeof(rozmiarDanych));
       
        if(rozmiarDanych<64) stop = 1;
       
            for(i=0; i<rozmiarDanych; i++){
                    opusc(semid, 1);
                    if(licz == 15){
                        fprintf(stderr, "\n");
                        licz = 0;
                    }else if(licz%2 == 0 && licz !=0){
                                fprintf(stderr, " ");
                            }
                    fprintf(stderr, "%c", wskShm[i]);
                    licz++;
                    podnies(semid, 0);
            }
            sleep(1);
        }
}
//
/* //////////////// Działanie semaforów //////////////// */
//
 void podnies(int semid, int semnum){ /* inkrementuj semafor */
    buf.sem_num = semnum;
    buf.sem_op = 1;
    buf.sem_flg = 0;
   
    if (semop(semid, &buf, 1) == -1){
        perror("Podnoszenie semafora");
        exit(1);
    }
}
 
void opusc(int semid, int semnum){ /* dekrementuj semafor */
    buf.sem_num = semnum;
    buf.sem_op = -1;
    buf.sem_flg = 0;
    while(semop(semid, &buf, 1) == -1){
        if(errno != EINTR){
            perror("Opuszczenie semafora");
        exit(1);
        }
    }
}
//
/* //////////////// Działanie sygnałów //////////////// */
//
void zatrzymaj(int signal) { /* wstrzymaj prace dzieci */
    if(praca==1){
    praca=0;
    printf("Prace procesu %d wstrzymano.\n", getpid());
    } else return;
   
    if(getpid()!=proces1)  kill(proces1, SIGUSR1);
    if(getpid()!=proces2)  kill(proces2, SIGUSR1);
    if(getpid()!=proces3)  kill(proces3, SIGUSR1);
   
}
void wznow(int signal) { /* wznow prace dzieci */
   
    if(praca==0){
    praca=1;
    printf("Prace procesu %d wznowionoo.\n", getpid());
    } else return;
   
    if(getpid()!=proces1)  kill(proces1, SIGUSR2);
    if(getpid()!=proces2)  kill(proces2, SIGUSR2);
    if(getpid()!=proces3)  kill(proces3, SIGUSR2);
   
}
 
void zakoncz() { /* koniec pracy programu */
    printf("%d odebral sygnal SIGINT\n", getpid());
    kill(proces1, SIGINT);
    kill(proces2, SIGINT);
    kill(proces3, SIGINT);
    sprzataj();
    exit(0);
}
 
void sygnal_1_D(int sig){ /* zakoncz prace dzieci */
    int pid = getpid();
    if(pid == proces1){
        kill(proces2, SIGINT);
        kill(proces3, SIGINT);
        kill(getppid(), SIGINT);
    }
    if(pid == proces2){
        kill(proces1, SIGINT);
        kill(proces3, SIGINT);
        kill(getppid(), SIGINT);
    }
    if(pid == proces3){
        kill(proces1, SIGINT);
        kill(proces2, SIGINT);
        kill(getppid(), SIGINT);
    }
    if(getpid() == procesGlownyId){
        kill(proces1, SIGINT);
        kill(proces2, SIGINT);
        kill(proces3, SIGINT);
    }
    exit(0);
}
void sprzataj(){
    close(potokPid1[0]);
    close(potokPid2[0]);
    close(potokPid3[0]);
    close(potokRozmiar[0]);
    close(potok[0]);
    close(potokPid1[1]);
    close(potokPid2[1]);
    close(potokPid3[1]);
    close(potokRozmiar[1]);
    close(potok[1]);
    shmdt(wskShm);
    shmctl(shmid, IPC_RMID, 0);
    semctl(semid, 0, IPC_RMID);
    fflush(stderr);
}