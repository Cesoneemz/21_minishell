# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>

int	ft_get_next_line(char **line, int fd)
{
	int		i;
	char	*buffer;
	char	c;
	int		rd;

	i = 0;
	c = '\0';
	rd = 0;
	buffer = malloc(100000);
	if (!buffer)
		return (-1);
	rd = read(fd, &c, 1);
	while (rd > 0 && c != '\n')
	{
		buffer[i++] = c;
		rd = read(fd, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (rd);
}

int	ft_heredoc_mode(char *delim)
{
	int		fd[2];
	char	*line;

	if (pipe(fd) != 0)
		perror("pipe error");
	if (fork() == 0)
	{
		close(fd[0]);
		write (STDOUT_FILENO, ">", 1);
		while (ft_get_next_line(&line, STDIN_FILENO))
		{
			if (strncmp(line, delim, strlen(delim)) == 0)
				exit (0);
			write(fd[1], line, strlen(line));
			write (STDOUT_FILENO, ">", 1);
		}
	}
	else
	{
		close(fd[1]);
		while (waitpid(-1, NULL, WUNTRACED) != -1)
			;
	}
	return (fd[0]);
}
