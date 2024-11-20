#include "get_next_line.h"

void leaks()
{
    system("leaks a.out");
}

int main()
{
    int fd = open("file.txt", O_RDONLY);
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