/*
 * Ejercicio 3 del TP FIFO
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include<sys/wait.h> 

#define MENSAJE "Mensaje para proceso B\n"
#define FIFO_PATH "/tmp/MI_FIFO"

int main(){

   int err, fifo_d;
   char buff[80];
   int leido;

   unlink(FIFO_PATH);    //si la FIFO existe la borro                   

   // FIFO puede ser leida, escrita y ejecutada por: 
   err = mkfifo(FIFO_PATH, 0777); // el resto de los usuarios del sistema.
   
   if(err == -1) {
      write (STDOUT_FILENO, "Error al crear FIFO, la FIFO ya existe\n", sizeof("Error al crear FIFO, la FIFO ya existe\n"));
   }else {
      write (STDOUT_FILENO, "FIFO creada correctamente\n", sizeof("FIFO creada correctamente\n"));
   }

// se abre y escribe

         write (STDOUT_FILENO, "Programa iniciado\n", sizeof("Programa iniciado\n"));

         fifo_d = open(FIFO_PATH, O_WRONLY, 0);
         if(fifo_d == -1){
            write(STDOUT_FILENO, "proceso A, error al abrir FIFO\n", sizeof("Proceso A, error al abrir FIFO\n"));
            return -1;
         }else {
            write(STDOUT_FILENO, "Proceso A, FIFO abierta correctamente\n", sizeof("Proceso A, FIFO abierta correctamente\n"));
         }

         // Se escribe en el FIFO
         err = write(fifo_d, MENSAJE, sizeof(MENSAJE));
         if(err == -1) {
            write(STDOUT_FILENO, "Proceso A, error al escribir en FIFO\n", sizeof("Proceso A, error al escribir en FIFO\n"));
         } else {
            write(STDOUT_FILENO, "Proceso A, escrito MENSAJE en FIFO\n", sizeof("Proceso A, escrito MENSAJE en FIFO\n"));
         }
         
         close(fifo_d);
         
         wait(NULL);   

         write (0, "Padre termina\n", sizeof("Padre termina\n")); 

   
   //Eliminacion FIFO
   //if (unlink(FIFO_PATH) < 0) {
    //   printf("\nNo se puede borrar FIFO.\n");  }         

   exit(0);

}
