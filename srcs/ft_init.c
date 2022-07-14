/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:14:46 by wlanette          #+#    #+#             */
/*   Updated: 2022/06/06 13:26:20 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*ft_init_tokens_node(void)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->index = 0;
	tokens->type = NONE;
	tokens->value = NULL;
	tokens->next = NULL;
	return (tokens);
}

t_env	*ft_init_env_node(void)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
	return (env);
}

t_env	*ft_init_env_struct(char **envp)
{
	t_env	*tmp;
	t_env	*env;
	int		index;
	char	**split;

	index = 0;
	env = ft_init_env_node();
	tmp = env;
	while (envp[index] != NULL)
	{
		split = ft_split(envp[index], '=');
		env->key = ft_strdup(split[0]);
		if (split[1])
			env->value = ft_strdup(split[1]);
		else
			env->value = ft_strdup("");
		ft_free_split(split);
		if (envp[index + 1] == NULL)
			break ;
		env->next = ft_init_env_node();
		env = env->next;
		index++;
	}
	env = tmp;
	return (env);
}

t_info	*ft_init_info(void)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->exit_t = 0;
	return (info);
}
