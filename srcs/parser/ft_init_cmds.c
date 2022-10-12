/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:06:13 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/07 16:05:32 by wmiyu            ###   ########.fr       */
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

	index = 0;
	if (type == EXP_FIELD)
		return (ft_quotes_treatment(cmd, type, info));
	expanded = ft_calloc(1, 1);
	while (cmd && cmd[index] != '\0' && type != FIELD)
	{
		if (cmd[index] == '$')
			expanded = ft_strjoin(expanded, (ft_dollar_treatment(cmd, info, index)));
		index++;
	}
	return (cmd);
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
		(*new)->value = ft_strdup(arg);
	else
		(*new)->value = ft_strdup("\n");
	(*new)->type = temp->type;
	return (1);
}

int	ft_create_cmd(t_info *info, t_tokens **tokens, int index)
{
	t_tokens	*head;

	info->cmd_list[index].sep_tokens = ft_new_token();
	head = info->cmd_list[index].sep_tokens;
	while (tokens && *(tokens))
	{
		while ((*tokens) && (*tokens)->type == SEP)
			(*tokens) = (*tokens)->next;
		if (!(*tokens))
			return (-1);
		if ((*tokens) && (*tokens)->type == PIPE)
		{
			if (info->cmd_list[index].sep_tokens->value == NULL)
				free(info->cmd_list[index].sep_tokens);
			break ;
		}
		ft_parse_args(tokens, info, &info->cmd_list[index].sep_tokens);
		if ((*tokens)->next && (*tokens)->next->type != PIPE)
		{
			info->cmd_list[index].sep_tokens->next = ft_new_token();
			info->cmd_list[index].sep_tokens = \
			info->cmd_list[index].sep_tokens->next;
		}
		(*tokens) = (*tokens)->next;
	}
	info->cmd_list[index].sep_tokens = head;
	return (0);
}
