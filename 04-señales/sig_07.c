#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void manejador() {
    int status;
    pid_t pid = wait(&status);
    printf("Proceso hijo con PID %d finalizado con status %d\n", pid, status);
}

int main() {
    pid_t pid;
    signal(SIGCHLD, manejador);
    // Crear un proceso hijo
    pid = fork();
    if (pid == 0) {
        // Código del proceso hijo
        sleep(2);
        exit(0);
    }

    // Esperar más de 10 segundos antes de verificar el estado del hijo
    sleep(11);

    // Verificar si el proceso hijo está en estado zombie
   // system("pstree -p $PPID");

    // Establecer un manejador para la señal SIGCHLD
    signal(SIGCHLD, manejador);

    // Esperar a la finalización del proceso hijo
    wait(NULL);

    return 0;
}

