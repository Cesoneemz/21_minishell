/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 02:41:45 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/15 05:06:56 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstlast_env(t_env *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*buffer;

	buffer = (t_env *)malloc(sizeof(t_env));
	if (buffer == NULL)
		return (NULL);
	buffer->key = key;
	buffer->value = value;
	buffer->next = NULL;
	return (buffer);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast_env(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
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
