#include "get_next_line.h"
int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }
    while ((line = get_next_line(fd)) != NULL) // Lecture progressive ligne par ligne
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
