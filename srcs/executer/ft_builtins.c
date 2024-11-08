/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:11:23 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/23 15:25:27 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

int	check_builtins3(char *cmd)
{
	char	**builtins;
	int		i;

	builtins = ft_split("echo,env,pwd", ',');
	i = -1;
	while (builtins[++i])
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
		{
			ft_freesplit(&builtins);
			return (1);
		}
	}
	ft_freesplit(&builtins);
	return (0);
}

int	check_builtins2(char *cmd)
{
	char	**builtins;
	int		i;

	builtins = ft_split("cd,export,unset,env,exit", ',');
	i = -1;
	while (builtins[++i])
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
		{
			ft_freesplit(&builtins);
			return (1);
		}
	}
	ft_freesplit(&builtins);
	return (0);
}

int	ft_exit(char **arglist)
{
	(void)arglist;
	write(STDOUT_FILENO, "bye bye!\n", 9);
	exit(0);
}

int	ft_run_builtin2(char **arglist, t_info *info)
{
	arglist = &arglist[1];
	if (ft_strncmp("echo", arglist[0], ft_strlen(arglist[0])) == 0)
		return (ft_echo(arglist));
	else if (ft_strncmp("cd", arglist[0], 2) == 0)
		return (ft_cd_parent2(arglist, info->env));
	else if (ft_strncmp("pwd", arglist[0], 3) == 0)
		return (ft_pwd(arglist));
	else if (ft_strncmp("env", arglist[0], 3) == 0)
		return (ft_built_env(arglist, info->env));
	else if (ft_strncmp("export", arglist[0], 3) == 0)
		return (ft_export_env(arglist, info->env));
	else if (ft_strncmp("unset", arglist[0], 3) == 0)
		return (ft_unset_env(arglist, &info->env));
	else if (ft_strncmp("exit", arglist[0], 4) == 0)
		return (ft_exit(arglist));
	return (55);
}

int	ft_run_builtin3(char **arglist, char **envp)
{
	if (ft_strncmp("echo", arglist[0], ft_strlen(arglist[0])) == 0)
		return (ft_echo(arglist));
	else if (ft_strncmp("pwd", arglist[0], ft_strlen(arglist[0])) == 0)
		return (ft_pwd(arglist));
	else if (ft_strncmp("env", arglist[0], ft_strlen(arglist[0])) == 0)
		return (ft_write_env(arglist, envp));
	else if (ft_strncmp("exit", arglist[0], ft_strlen(arglist[0])) == 0)
		return (ft_exit(arglist));
	return (55);
}

/*
			//printf("  BUILTIN 3 FOUND: [%s] \n", cmd);
			//printf("  BUILTIN 2 FOUND: [%s] \n", cmd);
*/