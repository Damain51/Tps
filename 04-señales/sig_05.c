#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


void manejador(){
   write(STDOUT_FILENO,"Me rehuso a terminar\n", sizeof("Me rehuso a terminar\n"));
}


int main ()
{
  signal(SIGUSR1, manejador);
  //signal(SIGSTOP, SIG_IGN);  //Ctrl + Z
   
   printf("Proceso PID = %d\n", getpid());   
   
   while(1);
   
   exit(0);
}
