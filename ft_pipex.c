/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:24:32 by wmiyu             #+#    #+#             */
/*   Updated: 2022/06/15 17:10:02 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_opn(char *filename, int mode)
{
	int	file;

	file = open(filename, mode, 0777);
	if (file == -1)
		error_exit(filename);
	return (file);
}

void	child_proc_n(char *arg, char **envp)
{
	int		pid_n;
	int		fd[2];
	char	**newargv;

	if (pipe(fd) == -1)
		error_exit("Error");
	pid_n = fork();
	if (pid_n == -1)
		error_exit("Error");
	if (pid_n == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		newargv = ft_split(arg, ' ');
		execute(newargv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid_n, NULL, 0);
	}
}

void	heredoc_mode(char *delim, int argc)
{
	int		pid_n;
	int		fd[2];
	char	*line;

	if (argc < 6)
		usage_bonus();
	if (pipe(fd) == -1)
		error_exit("Error");
	pid_n = fork();
	if (pid_n == 0)
	{
		close(fd[0]);
		while (get_next_line(&line, STDIN_FILENO))
		{
			if (ft_strncmp(line, delim, ft_strlen(delim)) == 0)
				exit (EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

void	main_pipex(int argc, char **argv, char **envp)
{
	int		c;
	int		file1;
	int		file2;
	char	**newargv;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		file2 = file_opn(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND);
		heredoc_mode(argv[2], argc);
		c = 3;
	}
	else
	{
		file1 = file_opn(argv[1], O_RDONLY);
		file2 = file_opn(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
		dup2(file1, STDIN_FILENO);
		close(file1);
		c = 2;
	}
	while (c < argc - 2)
		child_proc_n(argv[c++], envp);
	dup2(file2, STDOUT_FILENO);
	close(file2);
	newargv = ft_split(argv[argc - 2], ' ');
	execute(newargv, envp);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc >= 5)
		main_pipex(argc, argv, envp);
	else
		usage_bonus();
	return (EXIT_SUCCESS);
}

void	main_pipex2(int argc, char **argv, char **envp)
{
	int		c;
//	int		file1;
//	int		file2;
	char	**newargv;

/*	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		file2 = file_opn(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND);
		heredoc_mode(argv[2], argc);
		c = 3;
	}
	else
	{
		file1 = file_opn(argv[1], O_RDONLY);
		file2 = file_opn(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
		dup2(file1, STDIN_FILENO);
		close(file1);
		c = 2;
	}*/
//	dup2(file1, STDIN_FILENO);
	while (c < argc)
		child_proc_n(argv[c++], envp);
//	dup2(file2, STDOUT_FILENO);
//	close(file2);
	newargv = ft_split(argv[argc - 2], ' ');
	execute(newargv, envp);
}
