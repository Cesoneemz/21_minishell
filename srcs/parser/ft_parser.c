/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:05:58 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/19 20:47:48 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_parse_cmd_part_2(int *index, t_info **info, char *cmd, \
t_token_types type)
{
	char	*expanded;
	char	*var;
	char	*temp;

	expanded = ft_calloc(1, 1);
	while (cmd[*index])
	{
		temp = expanded;
		if (cmd[*index] == '$')
		{
			var = ft_dollar_treatment(cmd, *info, index);
			if (var == NULL && ft_strlen(expanded) <= 0)
				expanded = ft_strjoin(temp, "\n");
			else
				expanded = ft_strjoin(temp, var);
		}
		if ((cmd[*index] == '\'' || cmd[*index] == '\"') && type == WORD)
			expanded = ft_strjoin(temp, \
			ft_word_treatment(cmd, index, cmd[*index]));
		if (ft_isascii(cmd[*index]))
			expanded = ft_add_char_to_str(temp, cmd[*index]);
		(*index)++;
		free(temp);
	}
	if (ft_strlen(expanded) <= 0)
		expanded = ft_strjoin(expanded, cmd);
	return (expanded);
}

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
			if (ft_create_cmd((*info), &tokens, index) == -1)
				return (-1);
		}
	}
	tokens = temp;
	ft_get_exec_line(info);
	return (1);
}
