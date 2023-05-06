/*
 * Ejercicio 4 de TP PIPE
*/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include<sys/wait.h>
#define DATA "TECNICAS DIGITALES III ES LO MAS" // Datos a escribir en la tubería
#define ERROR "SIGPIPE, problema con pipeline.\n " // Mensaje de error
#define BUFF_SIZE 80 // Tamaño del buffer

// Manejador de la señal SIGPIPE
void pipe_sign_handler(int a) {
    write(STDOUT_FILENO, ERROR, sizeof(ERROR)); // Imprime mensaje de error
    exit(-1); // Termina el proceso con un código de error
}

int main() {
    int ipc[2]; // Arreglo para los descriptores de archivos de la tubería
    int leido, success;
    char buff[BUFF_SIZE] = {0}; // Inicializa el buffer en ceros

    signal(SIGPIPE, pipe_sign_handler); // Establece el manejador de la señal SIGPIPE

    if (pipe(ipc) == -1) // Crea la tubería y verifica si hubo un error
        exit(-1);

    switch (fork()) {
        case 0: // Hijo
            close(ipc[1]); // Cierra el descriptor de escritura
            printf("Hijo leyendo tuberia... \n");
            leido = read(ipc[0], buff, sizeof(buff)); // Lee de la tubería
            if (leido < 1) { // Si no se leyó nada
                write(STDOUT_FILENO, "Error al leer tuberia\n", sizeof("Error al leer tuberia\n"));
            } else { // Si se leyó algo
                write(STDOUT_FILENO, "Leido de la tuberia \"", sizeof("Leido de la tuberia \""));
                write(STDOUT_FILENO, buff, leido - 1);
                printf("\" por el proceso hijo.\n");
            }
            exit(0); // Termina el proceso hijo

        default: // Padre
            close(ipc[0]); // Cierra el descriptor de lectura
            strncpy(buff, DATA, sizeof(DATA)); // Copia los datos a escribir en el buffer
            write(ipc[1], buff, sizeof(DATA)); // Escribe en la tubería
            wait(NULL); // Espera a que el hijo termine
            exit(0); // Termina el proceso padre
    }
}

