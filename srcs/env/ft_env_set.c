/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 00:36:11 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/29 01:05:10 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_env(t_env **env, char *key, char *value)
{
	t_env	*head;

	head = *env;
	while (*env)
	{
		if (ft_strncmp((*env)->key, key, ft_strlen(key) + 1) == 0)
		{
			free((*env)->value);
			if (value)
				(*env)->value = ft_strdup(value);
			else
				(*env)->value = ft_strdup("");
			break ;
		}
		(*env) = (*env)->next;
	}
	(*env) = head;
}
