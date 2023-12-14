// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/wait.h>
// #include <unistd.h>

// int	main(void)
// {
// 	int		pipefd[2];
// 	pid_t	pid;

// 	// Crear el pipe
// 	if (pipe(pipefd) == -1)
// 	{
// 		perror("Error al crear el pipe");
// 		exit(EXIT_FAILURE);
// 	}
// 	// Crear un nuevo proceso
// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("Error al crear el proceso hijo");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (pid > 0)
// 	{                     // Proceso padre
// 		close(pipefd[0]); // Cerramos el extremo de lectura, no lo necesitamos
// 		// Redirigir la salida estándar al extremo de escritura del pipe
// 		dup2(pipefd[1], STDOUT_FILENO);
// 		close(pipefd[1]);
// 			// Cerramos el extremo de escritura después de la redirección
// 		// Ejecutar 'ls'
// 		execlp("cat", "cat", "Makefile", NULL);
// 		perror("execlp");
// 		exit(EXIT_FAILURE);
// 	}
// 	else
// 	{                     // Proceso hijo
// 		close(pipefd[1]); // Cerramos el extremo de escritura, no lo necesitamos
// 		// Redirigir la entrada estándar al extremo de lectura del pipe
// 		dup2(pipefd[0], STDIN_FILENO);
// 		close(pipefd[0]);
// 			// Cerramos el extremo de lectura después de la redirección
// 		// Ejecutar 'ls -lah'
// 		execlp("cat", "cat", "-e", NULL);
// 		perror("execlp");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(void)
{
	int		pipefd[2];
	pid_t	pid;

	// Crear el pipe
	if (pipe(pipefd) == -1)
	{
		perror("Error al crear el pipe");
		exit(EXIT_FAILURE);
	}
	// Crear un nuevo proceso
	pid = fork();
	if (pid < 0)
	{
		perror("Error al crear el proceso hijo");
		exit(EXIT_FAILURE);
	}

	if (pid > 0)
	{ // Proceso padre
		close(pipefd[0]); // Cerramos el extremo de lectura, no lo necesitamos
		// Redirigir la salida estándar al extremo de escritura del pipe
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]); // Cerramos el extremo de escritura después de la redirección
		// Ejecutar 'ls'
		char *argv[] = {"cat", "Makefile", NULL};
		execve("/bin/cat", argv, NULL);
		perror("execve");
		exit(EXIT_FAILURE);

	}
	else
	{ // Proceso hijo
		close(pipefd[1]); // Cerramos el extremo de escritura, no lo necesitamos

		// Redirigir la entrada estándar al extremo de lectura del pipe
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]); // Cerramos el extremo de lectura después de la redirección
		// Ejecutar 'ls -lah'
		char *argv[] = {"cat", "-e", NULL};
		execve("/bin/cat", argv, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}

	return 0;
}
