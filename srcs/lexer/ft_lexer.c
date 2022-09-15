/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 04:56:53 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/15 05:08:15 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lexer_loop(char *str, t_tokens **tokens)
{
	int	index;

	index = 0;
	while (str[index] != '\0' && index != -1)
	{
		if (index != 0)
		{
			(*tokens)->next = ft_new_token();
			(*tokens) = (*tokens)->next;
		}
		if (str[index] == ' ')
		{
			index += ft_tokenize_sep(str, index, (*tokens));
			continue ;
		}
		if (str[index] == '\"' || str[index] == '\'')
		{
			index += ft_tokenize_quotes(str, index + 1, (*tokens));
			continue ;
		}
		index += ft_tokenize_str(str, index, (*tokens));
		ft_get_type_of_token((*tokens));
	}
}

int	ft_lexer(char *str, t_tokens **tokens)
{
	int			index;
	t_tokens	*head;

	if (!ft_check_quotes(str))
		return (-1);
	index = 0;
	head = *tokens;
	ft_lexer_loop(str, tokens);
	*tokens = head;
	if (ft_finally_lex_analyze((*tokens)) == -1)
		return (-1);
	return (index);
}
