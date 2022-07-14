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

static void	ft_check_special_tokens(t_tokens *tokens, char **str, int pos)
{
	if (ft_strncmp(str[pos], ">", 1) == 0)
	{
		tokens->type = TRUNC;
		tokens->value = ft_strdup(str[pos]);
	}
	if (ft_strncmp(str[pos], "<", 1) == 0)
	{
		tokens->type = INPUT;
		tokens->value = ft_strdup(str[pos]);
	}
	if (ft_strncmp(str[pos], ">>", 1) == 0)
	{
		tokens->type = APPEND;
		tokens->value = ft_strdup(str[pos]);
	}
	if (ft_strncmp(str[pos], "<<", 1) == 0)
	{
		tokens->type = HEREDOC;
		tokens->value = ft_strdup(str[pos]);
	}
	if (ft_strncmp(str[pos], "|", 1) == 0)
	{
		tokens->type = PIPE;
		tokens->value = ft_strdup(str[pos]);
	}
}

static void	ft_get_tokens(t_tokens *tokens, char **str, t_env *env)
{
	int		index;
	char	*env_value;

	index = 0;
	while (str[index])
	{
		tokens->index = index;
		ft_check_special_tokens(tokens, str, index);
		if (tokens->type == NONE)
		{
			if (str[index][0] == '$')
			{
				env_value = ft_get_env(env, ft_substr(str[index], 1, ft_strlen(str[index]) - 1))->value;
				tokens->value = ft_strdup(env_value);
			}
			else
				tokens->value = ft_strdup(str[index]);
		}
		if (str[index + 1] != NULL)
		{
			tokens->next = ft_init_tokens_node();
			tokens = tokens->next;
		}
		index++;
	}
}

t_tokens	*ft_lexer(char *str, t_env *env)
{
	t_tokens	*tokens;
	char		**split_str;

	tokens = ft_init_tokens_node();
	str = ft_remove_spaces(str);
	split_str = ft_split(str, ' ');
	ft_get_tokens(tokens, split_str, env);
	ft_free_split(split_str);
	return (tokens);
}
