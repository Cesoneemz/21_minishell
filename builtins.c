/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 15:09:51 by wmiyu             #+#    #+#             */
/*   Updated: 2022/06/14 17:22:18 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_num_builtins(char **builtin_str)
{
	int	i;

	i = 0;
	while (builtin_str[i])
		i++;
	return (i);
}

int	msh_cd(char **args)
{
	if (args[1] == NULL)
		printf(BOLDGREEN"Error argument for \"cd\"\n"CLOSE);
	else
		if (chdir(args[1]) != 0)
			perror("Error cd");
	return (1);
}

int	msh_help(char **args, char **builtin_str)
{
	int	i;

	(void) args;
	i = 0;
	printf(BOLDGREEN"\n--- List of minishell builtin commands: ---\n\n");
	while (i < msh_num_builtins(builtin_str))
		printf("%s\n", builtin_str[i++]);
	printf("\n-------------------------------------------\n"CLOSE);
	return (1);
}

int	msh_exit(char **args)
{
	(void) args;
	printf(BOLDGREEN"BYE BYE\n"CLOSE);
	return (0);
}

int	run_bultin_num(int fnum, char **args, char **builtin_str)
{
	if (fnum == 0)
		return (msh_cd(args));
	else if (fnum == 1)
		return (msh_help(args, builtin_str));
	else if (fnum == 2)
		return (msh_exit(args));
	return (1);
}
