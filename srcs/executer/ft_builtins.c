/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:11:23 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/16 14:40:40 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

int	check_builtins3(char *cmd)
{
	char	**builtins;
	int		i;

	builtins = ft_split("echo,env,pwd,exit", ',');
	i = -1;
	while (builtins[++i])
	{
		if (strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
		{
//			printf("  BUILTIN FOUND: [%s] \n", cmd);
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
		if (strncmp(cmd, builtins[i], ft_strlen(cmd)) == 0)
		{
//			printf("  BUILTIN FOUND: [%s] \n", cmd);
			ft_freesplit(&builtins);
			return (1);
		}
	}
	ft_freesplit(&builtins);
	return (0);
}

int	ft_pwd(char **arglist)
{
	char	cwd[1024];

	(void)arglist;
	cwd[0] = '\0';
	if (getcwd(cwd, 1024))
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else
		return (-53);
}

int	ft_exit(char **arglist)
{
	(void)arglist;
	write(STDOUT_FILENO, "bye bye!\n", 9);
	exit(77);
}

int	ft_run_builtin(char **cmd_list, t_info *info)
{
	char	**arglist;

	arglist = ft_split(cmd_list[0], '\t');
	if (strncmp("echo", arglist[0], ft_strlen(arglist[0])) == 0)
		return (ft_echo(arglist));
	else if (strncmp("cd", arglist[0], 2) == 0)
		return (ft_cd_parent2(arglist, info->env));
	else if (strncmp("pwd", arglist[0], 3) == 0)
		return (ft_pwd(arglist));
	else if (strncmp("env", arglist[0], 3) == 0)
		return (ft_built_env(arglist, info->env));
	else if (strncmp("export", arglist[0], 3) == 0)
		return (ft_export_env(arglist, info->env));
	else if (strncmp("unset", arglist[0], 3) == 0)
		return (ft_unset_env(arglist, &info->env));
	else if (strncmp("exit", arglist[0], 4) == 0)
		return (ft_exit(arglist));
	return (55);
}

int	ft_run_builtin2(char **arglist, t_info *info)
{
	arglist = &arglist[1];
	if (strncmp("echo", arglist[0], ft_strlen(arglist[0])) == 0)
		return (ft_echo(arglist));
	else if (strncmp("cd", arglist[0], 2) == 0)
		return (ft_cd_parent2(arglist, info->env));
	else if (strncmp("pwd", arglist[0], 3) == 0)
		return (ft_pwd(arglist));
	else if (strncmp("env", arglist[0], 3) == 0)
		return (ft_built_env(arglist, info->env));
	else if (strncmp("export", arglist[0], 3) == 0)
		return (ft_export_env(arglist, info->env));
	else if (strncmp("unset", arglist[0], 3) == 0)
		return (ft_unset_env(arglist, &info->env));
	else if (strncmp("exit", arglist[0], 4) == 0)
		return (ft_exit(arglist));
	return (55);
}

/*
int	check_builtins(char *cmd)
{
	char	**builtins;
	char	**cmds;
	int		i;

	builtins = ft_split("echo,cd,pwd,export,unset,env,exit", ',');
	cmds = ft_split(cmd, '\t');
	i = -1;
	while (builtins[++i])
	{
		if (strncmp(cmds[0], builtins[i], ft_strlen(cmds[0])) == 0)
		{
			printf("  BUILTIN FOUND: [%s] \n", cmds[0]);
			ft_freesplit(&builtins);
			ft_freesplit(&cmds);
			return (1);
		}
	}
	ft_freesplit(&builtins);
	ft_freesplit(&cmds);
	return (0);
}
*/