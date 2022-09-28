/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:11:23 by wmiyu             #+#    #+#             */
/*   Updated: 2022/09/28 22:05:13 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	check_builtins(char *cmd)
{
	char	**builtins;
	int		i;

	builtins = ft_split("echo,kuku,cd,pwd,export,unset,env,exit", ',');
	i = -1;
	while (builtins[++i])
	{
		if (strncmp(cmd, builtins[i], ft_strlen(builtins[i])) == 0)
		{
			//printf("  BUILTIN FOUND: [%s] \n", cmd);
			return (1);
		}
	}
	return (0);
}

int	ft_echo(char **arglist)
{
	int	i;
	int	n_opt;

	i = 0;
	n_opt = 0;
	if (arglist[1] && strncmp("-n", arglist[1], 2) == 0)
	{
		i++;
		n_opt = 1;
	}
	while (arglist[++i])
	{
		write(STDOUT_FILENO, arglist[i], ft_strlen(arglist[i]));
		write(STDOUT_FILENO, " ", 1);
	}
	if (!n_opt)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

int	ft_pwd(char **arglist)
{
	char	cwd[1024];

	(void)arglist;
	if (getcwd(cwd, 1024))
	{
		write(STDOUT_FILENO, cwd, ft_strlen(cwd));
		write(STDOUT_FILENO, "\n", 1);
		return (53);
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

int	ft_run_builtin(char **arglist)
{
	if (strncmp("echo", arglist[0], ft_strlen(arglist[0])) == 0)
	{
		return (ft_echo(arglist));
	}
	else if (strncmp("pwd", arglist[0], ft_strlen(arglist[0])) == 0)
	{
		return (ft_pwd(arglist));
	}
	else if (strncmp("exit", arglist[0], ft_strlen(arglist[0])) == 0)
	{
		return (ft_exit(arglist));
	}
	return (55);
}

/* Your shell must implement the following builtins:
◦ echo		511 with option -n
◦ cd 		512 with only a relative or absolute path 
◦ pwd 		513 with no options
◦ export 	514 with no options
◦ unset 	515 with no options
◦ env 		516 with no options or arguments
◦ exit 		510 with no options 
*/
