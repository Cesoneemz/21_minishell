/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:49:37 by Wmiyu             #+#    #+#             */
/*   Updated: 2022/09/13 17:27:54 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_readline(char *pmt)
{
	char	*str;

	str = NULL;
	str = readline(pmt);
	if (str != NULL)
		add_history(str);
	return (str);
}

int	token_count(char *str, char tok)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (str && str[i])
	{
		if (str[i] == tok)
			c++;
		i++;
	}
	return (c);
}

void	msh_loop(char **argv, char **envp)
{
	char	*line;
	char	**args;
	int		status;
	int		pid_n;

	(void)argv;
	(void)envp;
	status = 1;
	args = NULL;
	line = NULL;
	while (status)
	{
		pid_n = fork();
		if (pid_n == 0)
		{
			line = msh_readline(" => MiniShell v.0.6 $> ");
			if (line && token_count(line, '|') > 0)
			{
			//	printf("#%d: %s\n", status, line);
				exec_in_recurse(ft_split_count(line,'|'), ft_split(line, '|'), envp, NULL);
			}
			free(line);
			line = NULL;
			sleep(1);
		}
		else
		{
			//printf(" MiniShell waiting %d \n", pid_n);
			waitpid(pid_n, 0, 0);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
//===========================================
	add_history("ls -m | wc -w | cat -e\n");
	add_history("yes | head | wc |cat -e\n");
	msh_loop(argv, envp);
	printf("=-=- END 0_6 -=-=-\n");
//===========================================
	return (EXIT_SUCCESS);
}
