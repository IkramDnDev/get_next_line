#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char *remainder;
    char        *line;
    int         bytes_read;
    char        buffer[BUFFER_SIZE + 1];

    if (fd < 0 || BUFFER_SIZE <= 0)
    return (NULL);
    while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[bytes_read] = '\0';
        remainder = ft_strjoin(remainder, buffer);
        if (ft_strchr(remainder, '\n'))
            break ;
    }
    if (!remainder || *remainder == '\0')
    {
        free(remainder);
        remainder = NULL;
        return (NULL);
    }
    line = extract_line(remainder);
    remainder = save_remainder(remainder);
    return (line);
}

// int main ()
// {
//     int fd = open("file.txt", O_RDWR);
//     char *line;
//     line = get_next_line(fd);
//     printf("%s", line);
//     free(line);
//     close (fd);
//     return 0;
// }