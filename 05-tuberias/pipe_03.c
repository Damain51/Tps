/*
 * Ejercicio 3 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h> 

#define FRASE_A "INFORMACION IMPORTANTE A"   //informacion a traspasar
#define FRASE_B "INFORMACION IMPORTANTE B"   //informacion a traspasar
#define BUFF_SIZE 80   //tamaño del buffer

void pipe_sign_handler(int a){
   
   printf ("SIGPIPE\n");
}

int main (){

   int ipc[2], ipc2[2], proc;     //0=read 1=write
   int leido, leido2, success;
   char buff[BUFF_SIZE] = {0};

   signal(SIGPIPE, pipe_sign_handler);
   
   pipe(ipc);
   pipe(ipc2);

   switch (fork()){   //crea un hijo
      
      case 0:
	   close(ipc[0]);      //cierra la lectura
	   strncpy(buff, FRASE_A, sizeof(FRASE_A)); //copia la frase A en el buffer
	   write(ipc[1], buff, sizeof(FRASE_A)); //lo escribe en la tuberia
	   close(ipc[1]);  //cierra la escritura en este hijo
	   exit(0);
      break;
      
      default:
      switch (fork()){  //crea otro hijo
            
         case 0:
            close(ipc2[0]);               //cierra la lectura
            strncpy(buff, FRASE_B, sizeof(FRASE_B)); //copia a frase B en el buffer
            write(ipc2[1], buff,    sizeof(FRASE_B)); //lo  escribe en la tuberia
            close(ipc2[1]); //cierrra la escritura en este hijo
            exit(0);      
         break;
         
         default:
            close(ipc[1]);  //padre cierra la escritura
            close(ipc2[1]);
            int i;
            
            sleep(1); //espera un segundo

            leido = read(ipc[0], buff, sizeof(buff)); //lee el tamaño
            if(leido < 1){    //si no lee nada
               write (STDOUT_FILENO, "Padre, Error al leer tuberia\n", sizeof("Padre, Error al leer tuberia\n"));
            }else {    //muestra en pantalla lo leido
               write (STDOUT_FILENO, "Padre, Leido de la tuberia \"", sizeof("Padre, Leido de la tuberia \""));
               write (STDOUT_FILENO, buff, leido-1);
               printf("\" por el proceso padre\n.");
               }

            leido2 = read(ipc2[0], buff, sizeof(buff)); //lee el tamaño
            if(leido2 < 1){    //si no lee nada
               write (STDOUT_FILENO, "Padre, Error al leer tuberia\n", sizeof("Padre, Error al leer tuberia\n"));
            }else {    //muestra en pantalla lo leido
               write (STDOUT_FILENO, "Padre, Leido de la tuberia \"", sizeof("Padre, Leido de la tuberia \""));
               write (STDOUT_FILENO, buff, leido2-1);
               printf("\" por el proceso padre\n.");
               }
            

            close(ipc[0]); //cierra la lectura
            close(ipc2[0]);
            wait(NULL);
            wait(NULL);
            exit(0);
         break;
      }
   }   
}
