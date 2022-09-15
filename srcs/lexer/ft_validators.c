/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 04:56:29 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/15 04:56:30 by wlanette         ###   ########.fr       */
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
		if (temp->type == PIPE || temp->type == INPUT || \
		temp->type == APPEND || \
		temp->type == HEREDOC || temp->type == TRUNC)
		{
			if (prev == NULL || temp->next == NULL)
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
