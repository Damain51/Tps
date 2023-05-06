#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t pid[3];

    // Crear tres procesos hijos
    for (int i = 0; i < 3; i++) {
        pid[i] = fork();
        if (pid[i] == 0) {
            // Código del proceso hijo
            while (1) {
                // Bucle infinito
            }
            exit(0);
        }
    }

    // Esperar un tiempo antes de enviar las señales de finalización
    sleep(5);

    // Finalizar los procesos hijos
    for (int i = 0; i < 3; i++) {
        kill(pid[i], SIGKILL);
    }

    return 0;
}

