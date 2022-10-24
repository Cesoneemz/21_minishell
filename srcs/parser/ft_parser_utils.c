/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:20:32 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/24 21:27:23 by wlanette         ###   ########.fr       */
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

static int	ft_count_args(t_tokens *tokens, int *args_len)
{
	t_tokens	*temp;
	int			index;

	temp = tokens;
	index = 0;
	while (temp)
	{
		if (temp->type == WORD || temp->type == BUILTIN)
			index++;
		else
			(*args_len)++;
		temp = temp->next;
	}
	return (index);
}

static void	ft_init_exec_line(t_info **info, int index, \
char ***save, char ***cmd_list)
{
	int	len;
	int	args_len;

	args_len = 0;
	len = ft_count_args((*info)->cmd_list[index].sep_tokens, &args_len);
	*save = (char **)malloc(sizeof(char *) * (args_len + 1));
	*cmd_list = (char **)malloc(sizeof(char *) * (len + 1));
}

int	ft_get_exec_line(t_info **info, char ***cmd_list, char ***save)
{
	int			index;
	int			jndex;
	int			zndex;
	t_tokens	*temp;

	index = 0;
	while (index < (*info)->cmd_count)
	{
		ft_init_exec_line(info, index, save, cmd_list);
		temp = (*info)->cmd_list[index].sep_tokens;
		jndex = 0;
		zndex = 0;
		while (temp)
		{
			if (temp->type == WORD || temp->type == BUILTIN)
				(*cmd_list)[jndex++] = ft_strdup(temp->value);
			else
				(*save)[zndex++] = ft_strdup(temp->value);
			temp = temp->next;
		}
		(*info)->cmd_list[index].sep_tokens = \
		ft_rebuild_cmd((*cmd_list), (*save), jndex, zndex);
		index++;
	}
	return (0);
}
