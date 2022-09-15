/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treatment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:04:52 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/15 05:05:49 by wlanette         ###   ########.fr       */
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
	if (ft_isalpha(c))
		return (0);
	if (ft_isdigit(c))
		return (0);
	return (1);
}

char	*ft_dollar_treatment(char *cmd, t_info *info, int index)
{
	char	*env_key;
	char	*value;
	int		env_len;

	env_len = 0;
	while (!ft_is_end_of_str(cmd[index]))
		env_len++;
	env_key = ft_substr(cmd, 1, env_len - 1);
	value = ft_get_env(info->env, env_key);
	if (!value)
	{
		free(env_key);
		return (NULL);
	}
	free(env_key);
	return (value);
}

char	*ft_quotes_treatment(char *cmd, t_token_types type, t_info *info)
{
	int		index;
	char	*value;

	index = 0;
	value = NULL;
	while (cmd[index] != '\0')
	{
		if (cmd[index] == '$' && type == EXP_FIELD)
			value = ft_dollar_treatment(cmd, info, index);
		index++;
	}
	if (value == NULL)
		return (cmd);
	return (value);
}
