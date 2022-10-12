/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:04:52 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/18 00:54:24 by wlanette         ###   ########.fr       */
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
	return (1);
}

char	*ft_dollar_treatment(char *cmd, t_info *info, int *index)
{
	char	*env_key;
	char	*value;
	int		env_len;
	int		temp;

	env_len = 0;
	temp = *index;
	while (ft_is_end_of_str(cmd[*index]))
	{
		env_len++;
		(*index)++;
	}
	env_key = ft_substr(cmd, temp + 1, env_len - 1);
	if (ft_strncmp(env_key, "?", 1) == 0)
		return (ft_itoa(info->exit_code));
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

	result = (char *)malloc(sizeof(char) * 2);
	if (!result)
		return (NULL);
	s_str = str;
	if (!s_str)
	{
		s_str = (char *)malloc(sizeof(char));
		if (!s_str)
			return (NULL);
		s_str[0] = '\0';
	}
	result[0] = c;
	result[1] = '\0';
	tmp = result;
	result = ft_strjoin(s_str, result);
	free(tmp);
	free(s_str);
	return (result);
}

char	*ft_quotes_treatment(char *cmd, t_token_types type, t_info *info)
{
	int		index;
	char	*value;

	index = 0;
	value = ft_calloc(1, 1);
	while (cmd[index] != '\0')
	{
		if (cmd[index] == '$' && type == EXP_FIELD)
		{
			value = ft_strjoin(value, ft_dollar_treatment(cmd, info, &index));
			continue ;
		}
		else
			value = ft_add_char_to_str(value, cmd[index]);
		index++;
	}
	if (value == NULL)
		return (cmd);
	return (value);
}
