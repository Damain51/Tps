/*
 * TP Procesos, Ejercicio 4
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>    // Define pid_t
#include <unistd.h>       // Define fork, getpid y getppid

int main (){

	pid_t pid;
	int i;

	pid = fork();
	if (pid == 0){
	printf ("soy el hijo. fork() devolvio %d\n",pid);
	return(0);
}
	printf ("Mi pid es %d y el pid de papa es %d. fork() devolvio %d\n", getpid(), getppid(), pid);

	// Ejecute pstree en otra consola	
	sleep(2); 

	exit(0);

}
