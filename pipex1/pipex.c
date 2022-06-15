/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 12:57:36 by WMiyu             #+#    #+#             */
/*   Updated: 2022/06/01 13:37:12 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child_proc1(int fd[2], char **argv, char **envp)
{
	char	**newargv;
	int		file;
	int		pid1;

	pid1 = fork();
	if (pid1 < 0)
		error_exit("Error");
	if (pid1 == 0)
	{
		file = open(argv[1], O_RDONLY);
		if (file == -1)
			error_exit(argv[1]);
		dup2(file, STDIN_FILENO);
		close(file);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		newargv = ft_split(argv[2], ' ');
		execute(newargv, envp);
	}
	return (pid1);
}

int	child_proc_n(int fd[2], char **argv, char **envp)
{
	char	**newargv;
	int		file;
	int		pid_n;

	pid_n = fork();
	if (pid_n < 0)
		error_exit("Error");
	if (pid_n == 0)
	{
		file = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (file == -1)
			error_exit(argv[4]);
		dup2(file, STDOUT_FILENO);
		close(file);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		newargv = ft_split(argv[3], ' ');
		execute(newargv, envp);
	}
	return (pid_n);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid1;
	int		pid2;

	if (argc != 5)
		usage();
	if (pipe(fd) == -1)
		return (1);
	pid1 = child_proc1(fd, argv, envp);
	pid2 = child_proc_n(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
