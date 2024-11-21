#include "get_next_line.h"

void leaks()
{
    system("leaks a.out");
}

int main()
{
    int fd = open("file2.txt", O_RDONLY);
    char *line = get_next_line(fd);
    while (line != NULL)
    {
        printf("Ligne lue : %s\n", line);
        free(line);
        line = get_next_line(fd);
    }
    atexit(leaks);
    close(fd);
    return (0);
}

int	main(void)
{
	int		fd1, fd2;
	char	*line;

	fd1 = open("file1.txt", O_RDONLY);
	fd2 = open("file2.txt", O_RDONLY);
    // printf("%d\n", fd1);
    // printf("%d", fd2);
	while ((line = get_next_line(fd1)))
	{
		printf("File 1: %s\n", line);
		free(line);
		line = get_next_line(fd2);
		printf("File 2: %s\n", line);
		free(line);
	}
	close(fd1);
	close(fd2);
    atexit(leaks);
	return (0);
}
