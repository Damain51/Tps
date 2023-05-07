
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include<sys/wait.h>

#define FIFO_PATH "/tmp/MI_FIFO"

int main()
{
    int err, fd;
    char buf[1024];
   
   unlink(FIFO_PATH);    // si la FIFO existe la borro

   // FIFO puede ser leida, escrita y ejecutada por:
   err = mkfifo(FIFO_PATH, S_IRUSR | S_IWUSR | S_IXUSR|  // el usuario que la creo
                           S_IRGRP | S_IWGRP | S_IXGRP|  // el grupo al que pertenece el usuario
                           S_IROTH | S_IWOTH | S_IXOTH); // el resto de los usuarios del sistema

   //err = mkfifo(FIFO_PATH, 0777);
   if(err == -1) {
      write (STDOUT_FILENO, "Error al crear FIFO, la FIFO ya existe\n", sizeof("Error al crear FIFO, la FIFO ya existe\n"));
   }else {
      write (STDOUT_FILENO, "FIFO creada correctamente\n", sizeof("FIFO creada correctamente\n"));
   }

    // Abrir la FIFO en modo lectura
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Leer desde la FIFO hasta que se reciba un EOF
    while (read(fd, buf, sizeof(buf)) > 0) {
        printf("%s", buf);
    }

    // Cerrar la FIFO
    close(fd);

    return 0;
}

