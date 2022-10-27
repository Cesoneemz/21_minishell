/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 14:55:18 by WMiyu             #+#    #+#             */
/*   Updated: 2022/10/27 15:47:27 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_putstr_fd2(char *str, char *arg)
{
	write(2, "minishell: ", 11);
	while (*str)
		write(2, str++, 1);
	while (arg && *arg)
		write(2, arg++, 1);
	write(2, "\n", 1);
	return (1);
}

static char	*check_splitpath(char **splitpath, char *cmd)
{
	int		i;
	char	*tmppath;
	char	*cmdpath;

	tmppath = NULL;
	cmdpath = NULL;
	i = -1;
	while (splitpath && splitpath[++i])
	{
		tmppath = ft_strjoin(splitpath[i], "/");
		cmdpath = ft_strjoin(tmppath, cmd);
		free(tmppath);
		if (access(cmdpath, F_OK) == 0)
			return (cmdpath);
		else if (cmdpath)
			free(cmdpath);
	}
	return (NULL);
}

char	*find_cmd_in_path(char *cmd, char **envp)
{
	int		i;
	char	**splitpath;
	char	*cmdpath;

	i = -1;
	splitpath = NULL;
	cmdpath = NULL;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			splitpath = ft_split(envp[i] + 5, ':');
	if (splitpath)
	{
		cmdpath = check_splitpath(splitpath, cmd);
		ft_freesplit(&splitpath);
	}
	return (cmdpath);
}
