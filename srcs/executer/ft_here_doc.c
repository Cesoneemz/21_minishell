/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:28:38 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/21 16:53:59 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

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

int	ft_try_heredoc(int i, char **argv, int *tmp_fd)
{
	if (i >= 3 && strcmp(argv[i - 2], "<<") == 0)
	{
		if (i < 2)
			return (ft_putstr_fd2("error: <<: bad arguments", NULL));
		*tmp_fd = ft_heredoc_mode(argv[i - 1]);
		argv[i - 2] = NULL;
	}
	return (0);
}
