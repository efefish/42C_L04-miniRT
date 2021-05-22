#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

# define BUFFER_SIZE 1000

int			get_next_line(int fd, char **line);
int			gnl_check_line(int fd, char **line, char **nextl, char *buf);
int			read_error_free(char **line, char *nextl);
size_t		gnl_strchr(const char *s, char c);
char		*gnl_strjoin(char const *s1, char const *s2, size_t len);
size_t		gnl_strlen(const char *s);
char		*gnl_strdup(const char *s);

#endif
