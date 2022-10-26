/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_in_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:51:03 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/26 00:41:15 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exit(t_tokens **tokens, t_info **info, char *str)
{
	int			index;
	t_tokens	*next;

	rl_clear_history();
	ft_free_env(&(*info)->env);
	index = 0;
	while (index < (*info)->cmd_count)
	{
		while ((*info)->cmd_list[index].sep_tokens)
		{
			next = (*info)->cmd_list[index].sep_tokens->next;
			free((*info)->cmd_list[index].sep_tokens);
			(*info)->cmd_list[index].sep_tokens = next;
		}
		free((*info)->cmd_list);
		index++;
	}
	free(*info);
	free(*tokens);
	free(str);
}

void	ft_free_all(t_tokens **tokens, t_info **info, char *str)
{
	int			index;
	t_tokens	*next;

	ft_free_tokens(tokens);
	index = 0;
	while (index < (*info)->cmd_count)
	{
		while ((*info)->cmd_list[index].sep_tokens)
		{
			next = (*info)->cmd_list[index].sep_tokens->next;
			free((*info)->cmd_list[index].sep_tokens->value);
			free((*info)->cmd_list[index].sep_tokens);
			(*info)->cmd_list[index].sep_tokens = next;
		}
		index++;
	}
	free((*info)->cmd_list);
	free(str);
}
