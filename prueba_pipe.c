#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int	fd;
	int	fd2;
	int	aux;

	fd = open("hola.txt", O_RDONLY);
	printf("%d\n", fd);
	aux = fd;
	close(fd);
	fd2 = open("hola.txt", O_RDONLY);
	printf("%d == %d?\n", aux, fd2);
	return (0);
}
