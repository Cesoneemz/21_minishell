/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 15:20:32 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/25 00:48:02 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**ft_parse_loop(t_tokens *temp, char ***cmd_list, char ***save)
{
	int		redirect_count;
	char	**redirect;
	int		jndex;
	int		zndex;
	int		xndex;

	redirect_count = ft_get_redirection_count(temp);
	redirect = malloc(sizeof(char *) * (redirect_count + 1));
	jndex = 0;
	zndex = 0;
	xndex = 0;
	while (temp)
	{
		if (ft_is_head(temp->type))
			redirect[xndex++] = ft_strdup(temp->value);
		else if (temp->type == WORD || temp->type == BUILTIN)
			(*cmd_list)[jndex++] = ft_strdup(temp->value);
		else
			(*save)[zndex++] = ft_strdup(temp->value);
		temp = temp->next;
	}
	redirect[xndex] = NULL;
	(*cmd_list)[jndex] = NULL;
	(*save)[zndex] = NULL;
	return (redirect);
}

int	ft_get_exec_line(t_info **info, char ***cmd_list, char ***save)
{
	int			index;
	char		**redirect;
	t_tokens	*new_list;
	t_tokens	*temp;

	index = 0;
	while (index < (*info)->cmd_count)
	{
		new_list = NULL;
		ft_init_exec_line(info, index, save, cmd_list);
		temp = (*info)->cmd_list[index].sep_tokens;
		redirect = ft_parse_loop(temp, cmd_list, save);
		ft_rebuild_cmd(redirect, &new_list);
		ft_rebuild_cmd((*cmd_list), &new_list);
		ft_rebuild_cmd((*save), &new_list);
		(*info)->cmd_list[index].sep_tokens = new_list;
		index++;
	}
	return (0);
}
