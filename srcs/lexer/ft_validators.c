/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validators.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 04:56:29 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/13 01:28:45 by wlanette         ###   ########.fr       */
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

static int	ft_redirect_check(t_token_types type, t_tokens *next, char *redirect)
{
	if (ft_is_redirect(type))
	{
		if (next == NULL)
		{
			ft_print_error("Invalid syntax: parse error near \'\\n\'\n");
			return (-1);
		}
		else if (ft_is_redirect(next->type))
		{
			ft_print_error("Invalid syntax: parse error near \'\\n\'\n");
			return (-1);
		}
		else if (next->next == NULL || (ft_strncmp(redirect, "<", 1) == 0 \
		&& (next->next->next == NULL)))
		{
			ft_print_error("Invalid syntax: no command to enter\n");
			return (-1);
		}
	}
	return (0);
}

int	ft_finally_lex_analyze(t_tokens *tokens)
{
	t_tokens	*temp;
	t_tokens	*prev;

	temp = tokens;
	prev = NULL;
	while (temp)
	{
		if (ft_check_pipes(temp, prev) == -1)
			return (-1);
		if (ft_redirect_check(temp->type, temp->next, temp->value))
			return (-1);
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
