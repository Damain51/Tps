/*
 * Ejercicio 2 de TP PIPE
 * 
*/
#include <stdio.h>  // Inclusión de la librería stdio.h que contiene funciones de entrada y salida estándar.
#include <sys/types.h>  // Inclusión de la librería sys/types.h que contiene definiciones de tipos de datos utilizados en llamadas al sistema.
#include <unistd.h>  // Inclusión de la librería unistd.h que proporciona funciones para el manejo de procesos, la gestión de archivos, y la comunicación entre procesos.
#include <string.h>  // Inclusión de la librería string.h que proporciona funciones para el manejo de cadenas de caracteres.
#include <stdlib.h>  // Inclusión de la librería stdlib.h que proporciona funciones para la gestión de memoria dinámica, variables y procesos.
#include<sys/wait.h>  // Inclusión de la librería sys/wait.h que proporciona funciones para el manejo de procesos hijos.

#define DATA "INFORMACION IMPORTANTE"  // Definición de una constante llamada DATA que contiene la cadena de caracteres "INFORMACION IMPORTANTE".
#define BUFF_SIZE 80  // Definición de una constante llamada BUFF_SIZE que contiene el tamaño del buffer.

int main (){

   int ipc[2], proc;  // Declaración de dos variables enteras llamadas ipc y proc.
   int leido, success;  // Declaración de dos variables enteras llamadas leido y success.
   char buff[BUFF_SIZE] = {0};  // Declaración de un arreglo de caracteres llamado buff de tamaño BUFF_SIZE.

   if (pipe(ipc) == -1)  // Verificación si la función pipe() devuelve -1 en caso de fallo, lo que significa que la creación de la tubería ha fallado.
      exit(-1);  // Salida del programa con código de error -1.

   switch (fork()){  // Comienza la creación de un proceso hijo.

      case 0:  // Caso en que se ejecuta el proceso hijo.
         printf("Hijo escribiendo en tuberia, pid %d... \n", getpid());  // Impresión en pantalla del mensaje que indica que el proceso hijo está escribiendo en la tubería y muestra su PID.
         close(ipc[0]);  // Cierre del descriptor de lectura de la tubería. habia un error en esta linea
         strncpy(buff, DATA, sizeof(DATA));  // Copia la cadena de caracteres DATA en el arreglo de caracteres buff.
         write(ipc[1], buff, sizeof(DATA));  // Escritura de los datos del arreglo de caracteres buff en la tubería.
	 close(ipc[1]);
         exit(0);  // Salida del proceso hijo con código de error 0.

      default:  // Caso en que se ejecuta el proceso padre.
        close(ipc[1]); 
	printf("Padre leyendo tuberia, pid %d... \n", getpid());  // Impresión en pantalla del mensaje que indica que el proceso padre está leyendo la tubería y muestra su PID.
         leido = read(ipc[0], buff, sizeof(buff));  // Lectura de los datos de la tubería y almacenamiento en el arreglo de caracteres buff.
         if(leido < 1){  // Si no se ha leído ningún dato.
            write (STDOUT_FILENO, "Error al leer tuberia\n", sizeof("Error al leer tuberia\n"));  // Se escribe en la salida estándar el mensaje de error
         }else {
	    write (STDOUT_FILENO, "Leido de la tuberia \"", sizeof("Leido de la tuberia \""));
            write (STDOUT_FILENO, buff, leido-1);
            printf("\" por el proceso padre.\n");
         }
         wait(NULL);

         exit(0);
   }
}
