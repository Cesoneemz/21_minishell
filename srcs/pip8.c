/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip8.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:25:21 by wmiyu             #+#    #+#             */
/*   Updated: 2022/09/13 16:55:19 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_in_out1(int fd_in[2], int fd_out[2], char *param1, char **envp)
{
	int		pid;
	char	**param;

	param = ft_split(param1, ' ');
	if (!(pid = fork()))
	{
		if (fd_in != NULL)
		{
			dup2(fd_in[0], STDIN_FILENO);
			close(fd_in[0]);
			close(fd_in[1]);
		}
		if (fd_out != NULL)
		{
			dup2(fd_out[1], STDOUT_FILENO);
			close(fd_out[0]);
			close(fd_out[1]);
		}
		//execve(param[0], param, envp);
		execute(param, envp);
		return (1);
	}
	return (0);
}

int	exec_in_recurse(int count, char **arg4, char **envp, int fd[2])
{
	int	fd2[2];
	int	maxcount;
	int	pid;

	maxcount = 0;
	while (arg4[maxcount])
		maxcount++;
	if (count > 1)
	{	
		if (count == maxcount)
		{
			//printf(" PARAM 1st: %d (%s),", maxcount - count, arg4[maxcount - count]);
			pipe(fd2);
			exec_in_out1(NULL, fd2, arg4[maxcount - count], envp);
		}
		else
		{
			//printf(" PARAM No.: %d (%s),", maxcount - count, arg4[maxcount - count]);
			pipe(fd2);
			exec_in_out1(fd, fd2, arg4[maxcount - count], envp);
			close (fd[0]);
			close (fd[1]);
		}
		exec_in_recurse(--count, arg4, envp, fd2);
	}
	else if (count == 1)
	{
		//printf(" PARAM Last: %d (%s)\n", maxcount - count, arg4[maxcount - count]);
		exec_in_out1(fd, NULL, arg4[maxcount - count], envp);
		close (fd[0]);
		close (fd[1]);
		pid = 1;
		while (pid > 0)
		{
			pid = wait(0); 
			//printf(" Waiting %d...\n" ,pid);
		}
	}	
	return (0);
}

/*
int main (int argc, char **argv, char **envp)
{
	char *my_cmd2;

	my_cmd2 = "/usr/bin/yes | /usr/bin/head -n 42 | /usr/bin/wc -l | /bin/cat -e | /bin/cat -e | /bin/cat -e";
	exec_in_recurse(ft_split_count(my_cmd2,'|'), ft_split(my_cmd2, '|'), envp, NULL);
	
	my_cmd2 = "/usr/bin/yes | /usr/bin/head -n 34 | /bin/cat -e | /bin/cat -e | /bin/cat -e | /bin/cat -e | /bin/cat -e | /bin/cat -e | /bin/cat -e | /bin/cat -e | /bin/cat -e| /usr/bin/wc";
	exec_in_recurse(ft_split_count(my_cmd2,'|'), ft_split(my_cmd2, '|'), envp, NULL);
	return (0);

}
*/