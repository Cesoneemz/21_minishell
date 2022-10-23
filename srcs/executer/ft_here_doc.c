/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 15:28:38 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/23 14:38:30 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

int	ft_gnl(char **line, int fd)
{
	int	len;

	len = 0;
	*line = get_next_line(fd);
	if (line)
		len = ft_strlen(*line);
	return (len);
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
		while (ft_gnl(&line, STDIN_FILENO))
		{
			if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
				exit (0);
			write(fd[1], line, ft_strlen(line));
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
	if (i >= 3 && ft_strncmp(argv[i - 2], "<<", 2) == 0)
	{
		if (i < 2)
			return (ft_putstr_fd2("error: <<: bad arguments", NULL));
		*tmp_fd = ft_heredoc_mode(argv[i - 1]);
		argv[i - 2] = NULL;
	}
	return (0);
}
