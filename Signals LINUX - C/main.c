#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
 
 
int pid1, MPID, pid2 = 0;
void wyswietlSygnaly(int signal){
    printf("\nMoj nr PID to: %d", getpid());
    printf(" : Numer sygnalu to: %d\n", signal);
    psignal(signal,"\nOtrzymalem sygnal");
 
    return;
}
void wyswietlSygnalQuit(int signal){
    wyswietlSygnaly(signal);
    printf("Koniec mojej pracy...\n\n");
    exit(0);
 
    return;
}
void dlaMacierzystego(int signal){
 
    printf("\nMoj nr PID to: %d", getpid());
    printf(" : Numer sygnalu to: %d\n", signal);
    psignal(signal,"\nOtrzymalem sygnal");
 
    kill(pid1, SIGQUIT);
    kill(pid2, SIGQUIT);
    printf("Koniec mojej pracy...\n\n");
    usleep(100);
    exit(0);

    return;
}
void sygnalSIGILL(int signal){
    wyswietlSygnaly(signal);
    printf("Koniec mojej pracy...\n\n");
   
    kill(MPID, SIGQUIT);
 
    return;
}
 
int main(void) {
   
    //PM
    MPID = getpid();
    printf("Numer procesu macierzystego: %d\n", MPID);
 
        sigset_t set;
        sigfillset(&set);
        sigdelset(&set, SIGQUIT);
    
    if(fork()){
 
        if(fork()){
                    signal(SIGQUIT, dlaMacierzystego);
                    sigprocmask(SIG_SETMASK, &set, NULL);
        }else{
           
            //P2
            pid2 = getpid();
            printf("PID procesu nr 2: %d\n", getpid());
 
                        int i=0;
                        for(i;i<_NSIG;i++){
                                        signal(i,wyswietlSygnaly);
                                }
                                
                        signal(SIGQUIT, wyswietlSygnalQuit);
                        signal(SIGILL, sygnalSIGILL);
        }
    }
    else{
     
        //P1
        pid1 = getpid();
        printf("PID procesu nr 1: %d\n", getpid());
       
                        sigset_t set;
                        sigfillset(&set);
                        sigdelset(&set, SIGQUIT);
                      
                        signal(SIGQUIT, wyswietlSygnalQuit);
                        sigprocmask(SIG_SETMASK, &set, NULL);
      
        while(1) {
          printf("$ ");
          fflush(stdout);
          sleep(3);     
       }
       
    }
   
        for(;;);
    pause();
 
    return 0;
}