/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 14:49:37 by Wmiyu             #+#    #+#             */
/*   Updated: 2022/07/01 13:32:28 by wmiyu            ###   ########.fr       */
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

int	count_tokens(char **tokens)
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
	return (c);
}

void	pipes_proceed(char	*line)
{
	char	**args;
	int		status;
	char	**pipes;
	int		i;
	int		tok_count;

	printf("PIPE_PROCEED!\n");
	pipes = msh_split_line(line, "|");
	i = 0;
	tok_count = count_tokens(pipes);
	while (i < tok_count)
	{
		args = msh_split_line(pipes[i], TOK_DELIM);
		status = msh_execute(args);
		i++;
	}
	if (line)
		free(line);
	if (args)
		free(args);
}

void	msh_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	args = NULL;
	while (status)
	{
		line = msh_readline(BOLDGREEN "MiniShell $> "CLOSE);
		if (strchr(line, '|') != 0)
		{
			pipes_proceed(line);
		}
		else
		{
			args = msh_split_line(line, TOK_DELIM);
			status = msh_execute(args);
			if (line)
				free(line);
			if (args)
				free(args);
		}
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
