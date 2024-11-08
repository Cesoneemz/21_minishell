/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:06:13 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/26 13:56:47 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_cmd(t_info **info, t_tokens *tokens)
{
	(*info)->cmd_count = ft_count_cmd(tokens);
	if ((*info)->cmd_count == -1)
		return (-1);
	(*info)->cmd_list = (t_cmd *)malloc((*info)->cmd_count * sizeof(t_cmd));
	if (!(*info)->cmd_list)
		return (-1);
	return (1);
}

char	*ft_parse_cmd(char *cmd, t_token_types type, t_info *info)
{
	int			index;
	char		*expanded;
	char		*temp;
	char		*save;

	index = 0;
	if (type == EXP_FIELD)
		return (ft_quotes_treatment(cmd, type, info));
	expanded = ft_calloc(1, sizeof(char));
	while (cmd && cmd[index] != '\0' && type != FIELD)
	{
		temp = ft_parse_cmd_part_2(&index, &info, cmd, type);
		save = expanded;
		expanded = ft_strjoin(expanded, temp);
		free(temp);
		free(save);
	}
	if (ft_strlen(expanded) <= 0)
	{
		free(expanded);
		return (cmd);
	}
	return (expanded);
}

int	ft_parse_args(t_tokens **tokens, t_info *info, t_tokens **new)
{
	t_tokens	*temp;
	char		*arg;

	temp = (*tokens);
	arg = NULL;
	if (!*tokens)
		return (0);
	arg = ft_parse_cmd(temp->value, temp->type, info);
	if (arg)
	{
		(*new)->value = ft_strdup(arg);
		arg = NULL;
	}
	else
		(*new)->value = ft_strdup(" ");
	(*new)->type = temp->type;
	return (1);
}

void	ft_create_a_new_sep_token(t_tokens **new)
{
	(*new)->next = ft_new_token();
	(*new) = (*new)->next;
}

int	ft_create_cmd(t_info *info, t_tokens **tokens, int index)
{
	t_tokens	*head;
	int			i;

	info->cmd_list[index].sep_tokens = ft_new_token();
	head = info->cmd_list[index].sep_tokens;
	i = 0;
	while (tokens && *(tokens))
	{
		while ((*tokens) && (*tokens)->type == SEP)
			(*tokens) = (*tokens)->next;
		if (!(*tokens))
			break ;
		if ((*tokens) && (*tokens)->type != PIPE && i != 0)
			ft_create_a_new_sep_token(&info->cmd_list[index].sep_tokens);
		if ((*tokens) && (*tokens)->type == PIPE)
			break ;
		ft_parse_args(tokens, info, &info->cmd_list[index].sep_tokens);
		(*tokens) = (*tokens)->next;
		i++;
	}
	info->cmd_list[index].sep_tokens = head;
	return (0);
}
