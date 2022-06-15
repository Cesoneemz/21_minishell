/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:55:18 by WMiyu             #+#    #+#             */
/*   Updated: 2022/06/15 17:20:14 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freesplit(char **splitarr)
{
	while (*splitarr)
		free (*splitarr++);
}

char	*find_cmd_in_path(char *cmd, char **envp)
{
	int		i;
	char	**splitpath;
	char	*tmppath;
	char	*cmdpath;

	i = -1;
	while (envp[++i])
		if (strncmp("PATH=", envp[i], 5) == 0)
			splitpath = ft_split(envp[i] + 5, ':');
	i = -1;
	while (splitpath[++i])
	{
		tmppath = ft_strjoin(splitpath[i], "/");
		cmdpath = ft_strjoin(tmppath, cmd);
		free(tmppath);
		if (access(cmdpath, F_OK) == 0)
		{
			freesplit(splitpath);
			return (cmdpath);
		}
		else if (cmdpath)
			free(cmdpath);
	}
	freesplit(splitpath);
	return (NULL);
}

int	execute(char **newargv, char **envp)
{
	char	*cmd_path;

	if (access(newargv[0], F_OK) == 0)
		cmd_path = newargv[0];
	else
		cmd_path = find_cmd_in_path(newargv[0], envp);
	if (cmd_path != NULL)
	{
		execve(cmd_path, newargv, envp);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	else
		error_exit("minishell");
	return (EXIT_FAILURE);
}
