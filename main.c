/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:49:37 by Wmiyu             #+#    #+#             */
/*   Updated: 2022/06/14 17:21:57 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*msh_readline(char *pmt)
{
	char	*str;

	str = NULL;
	str = readline(pmt);
	add_history(str);
	return (str);
}

void	print_tokens(char **tokens)
{
	char	*token;
	int		c;

	c = 0;
	token = NULL;
	printf("========================\n");
	while (tokens[c])
	{
		token = tokens[c];
		printf("%s\n", token);
		c++;
	}
	printf("========================\n");
}

void	msh_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	args = NULL;
	printf("=== Minishell v.0.1 by WW-Team\n\n");	
	while (status)
	{
		line = msh_readline(BOLDGREEN "MiniShell $> "CLOSE);
		args = msh_split_line(line);
		print_tokens(args);
		status = msh_execute(args);
		free(line);
		free(args);
	}
}


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	msh_loop();

	return (EXIT_SUCCESS);
}
