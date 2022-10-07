/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_z.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:41:02 by wmiyu             #+#    #+#             */
/*   Updated: 2022/09/28 22:05:27 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_exec_z(char *cmd_path, char **newargv, char **envp)
{
	int		pid;
	int		status;
	int		f_status;

	pid = fork();
	f_status = 0;
	if (!pid)
	{
//		ft_execve(cmd, ft_args_to_arr(cmd), ft_list_to_arr(head));

		if (execve(cmd_path, newargv, envp) == -1)
		{
			//perror(cmd_path);
			exit(errno);
		}
	}
	else if (pid == -1)
		perror("Fork failed");
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			f_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			f_status = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit: 3\n", 8);
		}
		return (f_status);
	}
	return (777);
}
