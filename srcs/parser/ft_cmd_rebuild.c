/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_rebuild.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:25:02 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/24 21:50:13 by wlanette         ###   ########.fr       */
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

static void	ft_join_arrays(t_tokens **list, char **array)
{
	int	index;

	index = 0;
	while (array[index])
	{
		(*list)->value = ft_strdup(array[index++]);
		if (array[index])
			ft_create_new_node(list);
	}
}

t_tokens	*ft_rebuild_cmd(char **cmd_list, char **save, int jndex, int zndex)
{
	t_tokens	*new_list;
	t_tokens	*head;

	save[zndex] = NULL;
	cmd_list[jndex] = NULL;
	new_list = ft_new_token();
	head = new_list;
	if (cmd_list)
		ft_join_arrays(&new_list, cmd_list);
	if (save)
		ft_join_arrays(&new_list, save);
	ft_free_all_lists(cmd_list, save);
	new_list = head;
	return (new_list);
}
