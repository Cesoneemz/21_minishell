/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_rebuild.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:25:02 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/24 17:13:25 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_create_new_node(t_tokens **list)
{
	(*list)->next = ft_new_token();
	(*list) = (*list)->next;
}

void	ft_free_all_lists(char **cmd_list, char **save)
{
	int			index;

	index = 0;
	while (cmd_list[index++])
		free(cmd_list[index]);
	free(cmd_list);
	index = 0;
	while (save[index++])
		free(save[index]);
	free(save);
}

t_tokens	*ft_rebuild_cmd(char **cmd_list, char **save, int jndex, int zndex)
{
	int			index;
	t_tokens	*new_list;
	t_tokens	*head;

	index = 0;
	save[zndex] = NULL;
	cmd_list[jndex] = NULL;
	new_list = ft_new_token();
	head = new_list;
	index = 0;
	while (cmd_list[index])
	{
		new_list->value = ft_strdup(cmd_list[index++]);
		ft_create_new_node(&new_list);
	}
	index = 0;
	while (save[index])
	{
		new_list->value = ft_strdup(save[index++]);
		ft_create_new_node(&new_list);
	}
	ft_free_all_lists(cmd_list, save);
	new_list = head;
	return (new_list);
}
