/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:04:52 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/23 13:36:36 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_end_of_str(char c)
{
	if (c == '_')
		return (0);
	if (c == ' ')
		return (0);
	if (c == '?')
		return (0);
	if (c == '\0')
		return (0);
	if (c == '$')
		return (0);
	return (1);
}

char	*ft_dollar_treatment(char *cmd, t_info *info, int *index)
{
	char	*env_key;
	char	*value;
	int		env_len;
	int		temp;

	env_len = 0;
	temp = (*index);
	env_key = ft_check_dollar_exceptions(cmd, index, info);
	if (env_key != NULL)
		return (env_key);
	while (ft_is_end_of_str(cmd[++(*index)]))
		env_len++;
	if (cmd[(*index)] == '$' && (!ft_isascii(cmd[(*index) + 1]) \
	|| cmd[(*index) + 1] == '\0'))
		(*index)--;
	env_key = ft_substr(cmd, temp + 1, env_len);
	value = ft_get_env(info->env, env_key);
	if (!value)
	{
		free(env_key);
		return (NULL);
	}
	free(env_key);
	return (value);
}

char	*ft_add_char_to_str(char *str, char c)
{
	char	*s_str;
	char	*result;
	char	*tmp;

	if (!str)
		return (NULL);
	result = (char *)malloc(sizeof(char) * 2);
	if (!result)
		return (NULL);
	s_str = str;
	result[0] = c;
	result[1] = '\0';
	tmp = result;
	result = ft_strjoin(s_str, result);
	free(tmp);
	free(s_str);
	return (result);
}

char	*ft_word_treatment(char *cmd, int *index, char c)
{
	char	*expanded_word;
	int		counter;
	char	*tmp;

	counter = 0;
	expanded_word = ft_calloc(1, sizeof(char));
	while (cmd[counter])
	{
		if (cmd[counter] != c)
		{
			tmp = expanded_word;
			expanded_word = ft_add_char_to_str(expanded_word, cmd[counter]);
			free(tmp);
		}
		(*index)++;
		counter++;
	}
	return (expanded_word);
}

char	*ft_quotes_treatment(char *cmd, t_token_types type, t_info *info)
{
	int		index;
	char	*value;
	char	*temp;

	index = 0;
	value = ft_calloc(1, sizeof(char));
	while (cmd[index] != '\0')
	{
		temp = value;
		if (cmd[index] == '$' && type == EXP_FIELD)
		{
			value = ft_strjoin(value, ft_dollar_treatment(cmd, info, &index));
			continue ;
		}
		else
			value = ft_add_char_to_str(value, cmd[index]);
		index++;
		free(temp);
	}
	if (value == NULL)
		return (cmd);
	return (value);
}
