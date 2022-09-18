/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:05:58 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/18 02:49:17 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_sort_cmd(t_info **info)
{
	int			index;
	int			jndex;
	int			zindex;
	t_cmd_line	*temp;

	index = 0;
	zindex = 0;
	(*info)->cmd_line = \
	(char **)malloc(sizeof(char *) * (*info)->cmd_with_args_count);
	while (index < (*info)->cmd_count)
	{
		jndex = 0;
		while (jndex < (*info)->cmd_with_args_count)
		{
			if ((*info)->cmd_list[index].line[jndex].type == BUILTIN)
			{
				(*info)->cmd_line[zindex] = \
				ft_strdup((*info)->cmd_list[index].line[jndex].arg);
				zindex++;
			}
			jndex++;
		}
		index++;
	}
	return (1);
}

int	ft_parse_command(t_info **info, t_tokens *tokens)
{
	int			index;
	int			jndex;
	int			args_count;
	t_tokens	*temp;

	if (!ft_init_cmd(info, tokens))
		return (-1);
	index = 0;
	temp = tokens;
	while (tokens != NULL)
	{
		if (tokens->type == PIPE)
		{
			index++;
			tokens = tokens->next;
		}
		else
			ft_create_cmd((*info), &tokens, index);
	}
	tokens = temp;
	ft_free_tokens(tokens);
	ft_sort_cmd(info);
	return (1);
}
