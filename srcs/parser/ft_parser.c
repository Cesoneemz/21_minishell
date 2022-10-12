/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:05:58 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/03 18:29:14 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_edit_type(t_info **info)
{
	t_tokens	*tokens_temp;
	int			is_heredoc;

	tokens_temp = (*info)->token_head;
	is_heredoc = 0;
	while (tokens_temp)
	{
		if (tokens_temp->type == HEREDOC)
			is_heredoc = 1;
		else if (is_heredoc == 1 && tokens_temp->value \
		&& tokens_temp->type != SEP)
		{
			tokens_temp->type = HEREDOC_ENDLINE;
			is_heredoc = 0;
		}
		tokens_temp = tokens_temp->next;
	}
	return (1);
}

static int	ft_edit_file_type(t_info **info)
{
	t_tokens		*tokens_temp;
	t_token_types	type;
	int				is_file;

	tokens_temp = (*info)->token_head;
	is_file = 0;
	while (tokens_temp)
	{
		if (ft_is_redirect(tokens_temp->type) && is_file == 1)
			return (0);
		if (is_file != 1 && ft_is_redirect(tokens_temp->type) \
		&& tokens_temp->value)
		{
			type = tokens_temp->type;
			is_file = 1;
		}
		else if (is_file == 1 && tokens_temp->type != SEP)
		{
			tokens_temp->type = ft_get_new_type(type);
			is_file = 0;
		}
		tokens_temp = tokens_temp->next;
	}
	return (1);
}

int	ft_parse_command(t_info **info, t_tokens *tokens)
{
	int			index;
	t_tokens	*temp;

	if (ft_init_cmd(info, tokens) == -1)
		return (0);
	if (ft_edit_type(info) == 0 || ft_edit_file_type(info) == 0)
		return (0);
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
		{
			if (ft_create_cmd((*info), &tokens, index)  == -1)
				return (-1);
		}
	}
	tokens = temp;
	ft_get_exec_line(info);
	return (1);
}
