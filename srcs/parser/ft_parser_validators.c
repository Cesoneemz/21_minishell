/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_validators.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:19:28 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/25 20:55:35 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_head(t_token_types type)
{
	if (type == INPUT || type == HEREDOC \
	|| type == FILE_IN || type == HEREDOC_ENDLINE)
		return (1);
	return (0);
}

int	ft_is_redirect(t_token_types type)
{
	return (type == INPUT || type == TRUNC || type == APPEND \
	|| type == HEREDOC);
}

int	ft_get_redirection_count(t_tokens *temp)
{
	int	redirect_count;

	redirect_count = 0;
	while (temp)
	{
		if (ft_is_head(temp->type))
			redirect_count++;
		temp = temp->next;
	}
	return (redirect_count);
}

int	ft_is_field(t_token_types type)
{
	return (type == WORD || type == BUILTIN \
	|| type == EXP_FIELD || type == FIELD);
}
