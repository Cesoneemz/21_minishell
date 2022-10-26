/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_rebuild.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:25:02 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/25 22:22:05 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_create_new_node(t_tokens **list)
{
	(*list)->next = ft_new_token();
	(*list) = (*list)->next;
}

void	ft_free_all_lists(char **cmd_list)
{
	int			index;

	index = 0;
	while (cmd_list && *cmd_list && cmd_list[index])
		free(cmd_list[index++]);
	if (cmd_list)
	{
		*cmd_list = NULL;
		free(cmd_list);
	}
}

void	ft_add_back(t_tokens **lst, t_tokens *new)
{
	t_tokens	*head;

	if (lst)
	{
		if (*lst)
		{
			head = *lst;
			while ((*lst)->next)
				(*lst) = (*lst)->next;
			(*lst)->next = new;
			*lst = head;
		}
		else
			*lst = new;
	}
}

static void	ft_join_arrays(t_tokens **list, char **array)
{
	int			index;
	t_tokens	*head;

	index = 0;
	head = *list;
	while (array[index] && array[index] != 0)
	{
		(*list)->value = ft_strdup(array[index]);
		index++;
		if (array[index])
			ft_create_new_node(list);
	}
	*list = head;
}

void	ft_rebuild_cmd(char **array, t_tokens **new_list)
{
	t_tokens	*new;

	new = NULL;
	if (array && *array)
	{
		new = ft_new_token();
		ft_join_arrays(&new, array);
	}
	else
		return ;
	ft_free_all_lists(array);
	ft_add_back(new_list, new);
}
