/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:03:37 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/15 05:03:37 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_tokens *tokens)
{
	t_tokens	*temp;

	temp = tokens;
	while (tokens != NULL)
	{
		free(tokens->value);
		tokens = tokens->next;
	}
	tokens = temp;
	while (tokens != NULL)
	{
		temp = tokens;
		free(tokens);
		tokens = temp->next;
	}
}

void	ft_free_env(t_env **env)
{
	t_env	*temp;

	while (*env != NULL)
	{
		temp = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = temp;
	}
	*env = NULL;
}

void	ft_free_info(t_info *info)
{
	int		index;
	int		jndex;
	t_env	*temp;

	index = info->cmd_count;
	while (index--)
	{
		free(info->cmd_list[index].cmd);
		jndex = 0;
		while (info->cmd_list[index].args[jndex])
		{
			free(info->cmd_list[index].args[jndex]);
			jndex++;
		}
	}
	free(info->cmd_list);
	temp = info->env;
	ft_free_env(&info->env);
}
