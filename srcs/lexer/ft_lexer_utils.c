/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 04:56:17 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/13 16:50:09 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_len_of_token(char *str, int index, t_tokens *tokens)
{
	while (str[index] != ' ' && str[index] != '\0')
	{
		if (str[index] == '<' || str[index] == '>')
			break ;
		if (str[index] == ' ')
			break ;
		if (str[index] == '|')
			break ;
		tokens->len++;
		index++;
	}
	return (tokens->len);
}

int	ft_tokenize_sep(char *str, int index, t_tokens *tokens)
{
	int	temp;

	temp = index;
	while (str[index] == ' ')
	{
		tokens->len++;
		index++;
	}
	tokens->value = ft_substr(str, temp, tokens->len);
	if (!tokens->value)
		return (-1);
	tokens->type = SEP;
	return (tokens->len);
}

int	ft_tokenize_quotes(char *str, int index, t_tokens *tokens, char quote)
{
	int	temp;

	temp = index;
	while (str[index] != quote)
	{
		tokens->len++;
		index++;
	}
	tokens->value = ft_substr(str, temp, tokens->len);
	if (!tokens->value)
		return (-1);
	if (str[index] == '\"')
		tokens->type = EXP_FIELD;
	else
		tokens->type = FIELD;
	return (tokens->len + 2);
}

int	ft_tokenize_str(char *str, int index, t_tokens *tokens)
{
	int	temp;

	temp = index;
	if (str[index] == '<' || str[index] == '>')
	{
		index++;
		if (str[index] == '<' || str[index] == '>')
		{
			tokens->value = ft_substr(str, temp, 2);
			return (2);
		}
		tokens->value = ft_substr(str, temp, 1);
		return (1);
	}
	if (str[index] == '|')
	{
		tokens->value = ft_substr(str, temp, 1);
		return (1);
	}
	tokens->len = ft_get_len_of_token(str, index, tokens);
	tokens->value = ft_substr(str, temp, tokens->len);
	if (!tokens->value)
		return (-1);
	return (tokens->len);
}

void	ft_get_type_of_token(t_tokens *tokens)
{
	if (ft_is_builtin(tokens->value))
		tokens->type = BUILTIN;
	if (ft_strncmp(tokens->value, ">", 1) == 0)
		tokens->type = TRUNC;
	if (ft_strncmp(tokens->value, "<", 1) == 0)
		tokens->type = INPUT;
	if (ft_strncmp(tokens->value, ">>", 2) == 0)
		tokens->type = APPEND;
	if (ft_strncmp(tokens->value, "<<", 2) == 0)
		tokens->type = HEREDOC;
	if (ft_strncmp(tokens->value, "|", 1) == 0)
		tokens->type = PIPE;
	if (tokens->type == 0)
		tokens->type = WORD;
}
