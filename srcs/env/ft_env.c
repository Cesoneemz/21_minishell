/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:07:05 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/18 02:25:14 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(t_env *env, char *key)
{
	t_env	*value;
	t_env	*temp;

	if (!env || !key)
		return (NULL);
	temp = env;
	while (temp)
	{
		if (!ft_strncmp(temp->key, key, ft_strlen(key) + 1))
			return (temp->value);
		temp = temp->next;
	}
	free(temp);
	return (NULL);
}

static void	ft_free_split(char **split)
{
	int	index;

	if (!split)
		return ;
	index = 0;
	while (split[index])
	{
		free(split[index]);
		index++;
	}
	free(split);
}

t_env	*ft_init_env(char **envp)
{
	int		index;
	char	**split_content;
	t_env	*env;
	t_env	*head;

	index = 0;
	env = ft_init_env_node();
	head = env;
	while (envp[index] != NULL)
	{
		split_content = ft_split(envp[index], '=');
		if (!split_content)
			return (NULL);
		env->key = ft_strdup(split_content[0]);
		env->value = ft_strdup(split_content[1]);
		ft_free_split(split_content);
		if (envp[index + 1] == NULL)
			break ;
		env->next = ft_init_env_node();
		env = env->next;
		index++;
	}
	env = head;
	return (env);
}
