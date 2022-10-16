/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_semi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:33:07 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/16 17:29:25 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

int	ft_execute3(char **argv, int i, int fd_in, char **envp)
{
	char	*cmd_path;
	int		t_cnt;

	argv[i] = NULL;
	t_cnt = param_count(&argv);
	if (t_cnt >= 3 && (argv[0][0] == '<') && \
		file_in_redir(argv[1], argv[0]) > 0)
		param_shift(&argv, 2);
	else
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	t_cnt = param_count(&argv);
	if (t_cnt >= 3 && (argv[t_cnt - 2][0] == '>' || \
	(argv[t_cnt - 2][0] == '>' && argv[t_cnt - 2][1] == '>' )))
	{
		if (file_opn_redir(argv[t_cnt - 1], argv[t_cnt - 2]) > 0)
			argv[t_cnt - 2] = NULL;
	}
	cmd_path = find_cmd_in_path(argv[0], envp);
	if (cmd_path != NULL)
		return (execve(cmd_path, argv, envp));
	else
		return (ft_putstr_fd2(argv[0], ": command not found"));
}

void	ft_waitpid_semi(pid_t wpid, int *most_recent_code, char *cmd)
{
	int			f_status;
	int			status;

	f_status = 0;
	status = 0;
	(void) cmd;
	waitpid(wpid, &status, 0);
	if (WIFEXITED(status))
		*most_recent_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		*most_recent_code = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			write(1, "Quit: 3\n", 8);
	}
}

int	ft_pipe_semi(int tmp_fd, char **argv, char **envp, int i)
{
	int			fd[2];

	pipe(fd);
	if (fork() == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		if (ft_execute3(argv, i, tmp_fd, envp))
			exit (127);
	}
	else
	{
		close(fd[1]);
		close(tmp_fd);
		tmp_fd = fd[0];
	}
	return (tmp_fd);
}

int	ft_fork_semi(int t_f_i[2], char **argv, char **envp, int *most_recent_code)
{
	pid_t	wpid;
	int		tmp_fd;
	int		i;

	tmp_fd = t_f_i[0];
	i = t_f_i[1];
	wpid = fork();
	if (wpid == 0 && ft_execute3(argv, i, tmp_fd, envp))
		exit (127);
	else
	{
		close(tmp_fd);
		ft_waitpid_semi(wpid, most_recent_code, argv[0]);
		tmp_fd = dup(STDIN_FILENO);
	}
	return (tmp_fd);
}

int	ft_exec_semi(int tmp_fd, char **argv, char **envp)
{
	int			i;
	static int	most_recent_code;
	int			t_f_i[2];

	i = 0;
	most_recent_code = 0;
	while (argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];
		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (strcmp(argv[i-2], "<<") == 0)
		{
			if (i < 2)
				return (ft_putstr_fd2("error: <<: bad arguments", NULL));
			tmp_fd = ft_heredoc_mode(argv[i - 1]);
			argv[i - 2] = NULL;
		}
		if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0 ))
		{
			t_f_i[0] = tmp_fd;
			t_f_i[1] = i;
			tmp_fd = ft_fork_semi(t_f_i, argv, envp, &most_recent_code);
		}
		else if (i != 0 && strcmp(argv[i], "|") == 0)
			tmp_fd = ft_pipe_semi(tmp_fd, argv, envp, i);
	}
	return (most_recent_code);
}
/*wpid = fork();
if (wpid == 0 && ft_execute3(argv, i, tmp_fd, envp))
	exit (127);
else
{
	close(tmp_fd);
	ft_waitpid_semi(wpid, &most_recent_code, argv[0]);
	tmp_fd = dup(STDIN_FILENO);
	
}
//printf("\t wpid: [%d] cmd: (%s) \t LAST_status: %d\n", \
wpid, cmd, *most_recent_code);
*/
