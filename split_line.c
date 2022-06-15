/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:53:54 by wmiyu             #+#    #+#             */
/*   Updated: 2022/06/15 17:18:40 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_exit(char *msg, int len)
{
	write(1, msg, len);
	exit (EXIT_FAILURE);
}

char	**msh_split_line(char *line, const char *sep)
{
	int		bufsize;
	int		pos;
	char	**tokens;
	char	*token;

	bufsize = TOK_BUFSIZE;
	pos = 0;
	tokens = malloc(bufsize * sizeof(char *));
	token = strtok(line, sep);
	while (token)
	{
		tokens[pos] = token;
		pos++;
		if (pos >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
				error_exit("Error malloc msh_split_line\n", 25);
		}
	token = strtok(NULL, TOK_DELIM);
	}
	tokens[pos] = NULL;
	return (tokens);
}
