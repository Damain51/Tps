
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

