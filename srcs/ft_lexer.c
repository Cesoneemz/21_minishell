/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:36:16 by wlanette          #+#    #+#             */
/*   Updated: 2022/06/29 15:47:41 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_tokens_count(char *str)
{
	int	result;
	int	index;

	result = 0;
	index = 0;
	while (str[index] != '\0')
	{
		if (ft_isascii(str[index]))
		{
			while (str[index] != ' ' && str[index] != '\0')
				index++;
			result++;
		}
		index++;
	}
	result++;
	return (result - 1);
}

char	**ft_lexer(char *str)
{
	int		index;
	char	**tokens;
	int		token_index;

	index = 0;
	token_index = 0;
	tokens = (char **)malloc(sizeof(char) * ft_tokens_count(str));
	if (!tokens)
		return (NULL);
	while (str[index] != '\0')
	{
		if (str[index] == ' ')
		{
			while (str[index] == ' ')
				index++;
			token_index++;
		}
		if (ft_isascii(str[index]))
			tokens[token_index] = ft_realloc_str(tokens[token_index], \
			str[index]);
		index++;
	}
	return (tokens);
}
