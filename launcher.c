/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 15:06:12 by wmiyu             #+#    #+#             */
/*   Updated: 2022/06/14 17:04:02 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	msh_launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("Error execvp");
		}
		exit (EXIT_FAILURE);
	}
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
		{
			wpid = waitpid(pid, &status, WUNTRACED);
		}
	}
	return (1);
}

int	msh_execute(char **args)
{
	int		i;
	char	*builtin_str[] = { "cd", "help", "exit", NULL};

	if (args[0] == NULL)
	{
		return (1);
	}
	i = 0;
	while (i < msh_num_builtins(builtin_str))
	{
		if (strcmp(args[0], builtin_str[i]) == 0)
		{
			return (run_bultin_num(i, args, builtin_str));
		}
		i++;
	}
	return (msh_launch(args));
}
