/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pip11.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:25:21 by wmiyu             #+#    #+#             */
/*   Updated: 2022/09/30 13:14:47 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int param_count(char ***par)
{
	int		t_cnt;
	int 	i;

	i = 0;
	t_cnt = 0;
	while (*(par[0] + i))
	{
		//printf(" par: %d : %s\n", i, *(par[0] + i));
		i++;
		t_cnt++;
	}
	//printf(" t_cnt: %d\n", t_cnt);
	return (t_cnt);
}

void param_shift(char ***par, int offset)
{
	int		t_cnt;
	int 	i;

	i = 0;
	t_cnt = param_count(par);
	while (i < t_cnt - offset)
	{
		*(par[0] + i) = *(par[0] + i + offset);
		i++;
	}	
		*(par[0] + i) = NULL;
	t_cnt = param_count(par);
}

int	file_in_redir(char *filename, char *redirect)
{
	int	file;

	printf(" FOUND < REDIRECT: %s %s\n", redirect, filename);
	file = -1;
	file = open(filename, O_RDONLY, 0777);
	if (file == -1)
	{
		perror(filename);
		return (-1);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	return (file);
}

int	file_opn_redir(char *filename, char *redirect)
{
	int	file;
	int	file_mode;

	printf(" FOUND > REDIRECT: %s %s\n", redirect, filename);
	file = -1;
	if (redirect[0] == '>' && redirect[1] == '>' )
		file_mode = O_WRONLY | O_CREAT | O_APPEND;
	else
		file_mode = O_WRONLY | O_CREAT | O_TRUNC;
	file = open(filename, file_mode, 0777);
	if (file == -1)
	{
		perror(filename);
		return (-1);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (file);
}

pid_t	exec_in_out1(int fd_in[2], int fd_out[2], char *param1, char **envp)
{
	pid_t	pid;
	char	**par;
	int		t_cnt;
	int		ret;

	par = ft_split(param1, '\t');
	t_cnt = param_count(&par);
	pid = fork();
	if (pid == 0)
	{
		if (t_cnt >= 3 && (par[0][0] == '<'))
		{
			if (file_in_redir(par[1], par[0]) > 0)
			{
				param_shift(&par, 2);
				fd_in = NULL;
				t_cnt = param_count(&par);
			}
		}
		if (fd_in != NULL)
		{
			dup2(fd_in[0], STDIN_FILENO);
			close(fd_in[0]);
			close(fd_in[1]);
		}
		if (t_cnt >= 3 && (par[t_cnt - 2][0] == '>' || \
		(par[t_cnt - 2][0] == '>' && par[t_cnt - 2][1] == '>' )))
		{
			if (file_opn_redir(par[t_cnt - 1], par[t_cnt - 2]) > 0)
			{
				par[t_cnt - 2] = NULL;
				fd_out = NULL;
			}
		}
		if (fd_out != NULL)
		{
			dup2(fd_out[1], STDOUT_FILENO);
			close(fd_out[0]);
			close(fd_out[1]);
		}
		ret = execute(par, envp);
		//if (ret != 0)
		//	perror(par[0]);		
		exit (ret);
	}
	return (pid);
}

int	exec_in_recurse1(int count, char **arg4, char **envp, int fd[2])
{
	int		fd2[2];
	int		maxcount;
	int		status;
	int		f_status;
	static	int most_recent_code;
//	pid_t	pid;
	pid_t	wpid;
	char	*cmd;

	cmd = NULL;
	status = 800;
	f_status = 0;
	maxcount = 0;
	wpid = -77;
	while (arg4[maxcount])
		maxcount++;
	if (count > 1)
	{	
		if (count == maxcount)
		{
			//printf(" PARAM 1st: %d (%s) | ", maxcount - count, arg4[maxcount - count]);
			pipe(fd2);
			cmd = arg4[maxcount - count];
			wpid = exec_in_out1(NULL, fd2, arg4[maxcount - count], envp);
		}
		else
		{
			//printf(" PARAM No.: %d (%s) | ", maxcount - count, arg4[maxcount - count]);
			pipe(fd2);
			cmd = arg4[maxcount - count];
			wpid = exec_in_out1(fd, fd2, arg4[maxcount - count], envp);
			close (fd[0]);
			close (fd[1]);
		}
		exec_in_recurse1(--count, arg4, envp, fd2);
	}
	else if (count == 1)
	{
		//printf(" PARAM Last: %d (%s)\n", maxcount - count, arg4[maxcount - count]);
		cmd = arg4[maxcount - count];
		wpid = exec_in_out1(fd, NULL, arg4[maxcount - count], envp);
		if (fd != NULL)
		{
			close (fd[0]);
			close (fd[1]);
		}
		waitpid(wpid, &status, 0);
		if (WIFEXITED(status))
			most_recent_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			most_recent_code = 128 + WTERMSIG(status);
			if (WTERMSIG(status) == SIGQUIT)
				write(1, "Quit: 3\n", 8);
		}	
		printf("\t wpid: [%d] cmd: (%s) \t LAST_status: %d\n", wpid, cmd, most_recent_code);
		return (most_recent_code);
	}
	waitpid(wpid, &status, 0);
	if (WIFEXITED(status))
		f_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		f_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit: 3\n", 8);
	}	
	printf("\t wpid: [%d] cmd: (%s) \t exit_status: %d\n", wpid, cmd, f_status);

	return (most_recent_code);
}
