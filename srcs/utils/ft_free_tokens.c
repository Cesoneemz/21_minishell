/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:03:37 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/18 18:32:54 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_free_tokens(t_tokens **tokens)
{
	t_tokens	*temp;

	while (*tokens)
	{
		temp = (*tokens)->next;
		free((*tokens)->value);
		free(*tokens);
		*tokens = temp;
	}
	*tokens = NULL;
}

void	ft_free_cmd(t_info **info)
{
	t_tokens	*temp;
	int			index;
	int			jndex;

	index = 0;
	while (index < (*info)->cmd_count)
	{
		jndex = 0;
		ft_free_tokens(&(*info)->cmd_list[index].sep_tokens);
		while ((*info)->cmd_list[index].exec_line[jndex])
		{
			free((*info)->cmd_list[index].exec_line[jndex]);
			jndex++;
		}
		free((*info)->cmd_list[index].exec_line);
		index++;
	}
	free((*info)->cmd_list);
}
