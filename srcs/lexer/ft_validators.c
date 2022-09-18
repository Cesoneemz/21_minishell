/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 04:56:29 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/18 18:19:11 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parse_quote(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == c)
		{
			index++;
			while (str[index] != c && str[index] != '\0')
				index++;
			if (str[index] == '\0')
				return (0);
		}
		index++;
	}
	return (1);
}

int	ft_finally_lex_analyze(t_tokens *tokens)
{
	t_tokens	*temp;
	t_tokens	*prev;

	temp = tokens;
	prev = NULL;
	while (temp)
	{
		if (temp->type == PIPE)
		{
			if (prev == NULL)
				return (-1);
		}
		if (temp->type == APPEND || temp->type == HEREDOC || \
		temp->type == TRUNC || temp->type == INPUT)
		{
			if (temp->next == NULL)
				return (-1);
		}
		prev = temp;
		temp = temp->next;
	}
	return (1);
}

int	ft_check_quotes(char *str)
{
	if (!ft_parse_quote(str, '\"') || (!ft_parse_quote(str, '\'')))
		return (0);
	return (1);
}

int	ft_is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(str, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(str, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(str, "export", 7) == 0)
		return (1);
	if (ft_strncmp(str, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(str, "env", 4) == 0)
		return (1);
	if (ft_strncmp(str, "exit", 5) == 0)
		return (1);
	return (0);
}
