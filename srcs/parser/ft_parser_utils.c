/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:20:32 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/18 18:16:08 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redirect(t_token_types type)
{
	return (type == INPUT || type == TRUNC || type == APPEND \
	|| type == HEREDOC);
}

t_token_types	ft_get_new_type(t_token_types type)
{
	if (type == INPUT)
		return (FILE_IN);
	if (type == TRUNC)
		return (FILE_OUT);
	if (type == APPEND)
		return (FILE_OUT_APPEND);
	if (type == HEREDOC)
		return (HEREDOC_ENDLINE);
	return (WORD);
}

static int	ft_count_args(t_tokens *tokens)
{
	t_tokens	*temp;
	int			index;

	temp = tokens;
	index++;
	while (temp)
	{
		if (temp->type == WORD || temp->type == BUILTIN)
			index++;
		temp = temp->next;
	}
	return (index);
}

int	ft_get_exec_line(t_info **info)
{
	int			index;
	int			jndex;
	int			len;
	t_tokens	*temp;

	index = 0;
	while (index < (*info)->cmd_count)
	{
		len = ft_count_args((*info)->cmd_list[index].sep_tokens);
		(*info)->cmd_list[index].exec_line = \
		(char **)malloc(sizeof(char *) * (len + 1));
		temp = (*info)->cmd_list[index].sep_tokens;
		jndex = 0;
		while (temp)
		{
			if (temp->type == WORD || temp->type == BUILTIN)
			{
				(*info)->cmd_list[index].exec_line[jndex] = \
				ft_strdup(temp->value);
				jndex++;
			}
			temp = temp->next;
		}
		(*info)->cmd_list[index].exec_line[len + 1] = NULL;
		index++;
	}
}
