/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:06:13 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/18 02:38:24 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_cmd(t_info **info, t_tokens *tokens)
{
	t_tokens	*temp;
	int			index;

	(*info)->cmd_count = ft_count_cmd(tokens);
	if ((*info)->cmd_count == -1)
		return (-1);
	(*info)->cmd_list = (t_cmd *)malloc((*info)->cmd_count * sizeof(t_cmd));
	if (!(*info)->cmd_list)
		return (-1);
	return (1);
}

int	ft_init_cmd_line(t_info **info, t_tokens *tokens, int index)
{
	int			counter;
	t_tokens	*temp;

	counter = 0;
	temp = tokens;
	while (temp && temp->type != PIPE)
	{
		counter++;
		temp = temp->next;
	}
	(*info)->cmd_list[index].line = \
	(t_cmd_line *)malloc(sizeof(t_cmd_line) * counter);
	(*info)->cmd_with_args_count = counter;
	if (!(*info)->cmd_list[index].line)
		return (0);
	return (1);

}

char	*ft_parse_cmd(char *cmd, t_token_types type, t_info *info)
{
	int			index;

	index = 0;
	if (type == EXP_FIELD)
		return (ft_quotes_treatment(cmd, type, info));
	while (cmd[index] != '\0' && type != FIELD)
	{
		if (cmd[index] == '$')
			return (ft_dollar_treatment(cmd, info, index));
		index++;
	}
	return (cmd);
}

char	*ft_parse_args(t_tokens **tokens, t_info *info)
{
	int		args_count;
	char	*arg;

	arg = ft_strdup(ft_parse_cmd((*tokens)->value, \
	(*tokens)->type, info));
	(*tokens) = (*tokens)->next;
	return (arg);
}

int	ft_create_cmd(t_info *info, t_tokens **tokens, int index)
{
	int	jndex;
	int	zindex;

	jndex = 0;
	ft_init_cmd_line(&info, *tokens, index);
	while (*(tokens) && ((*tokens)->type) != PIPE)
	{
		while ((*tokens)->type == SEP && (*tokens))
			(*tokens) = (*tokens)->next;
		info->cmd_list[index].line[jndex].type = (*tokens)->type;
		info->cmd_list[index].line[jndex].arg = \
		ft_strdup(ft_parse_args(tokens, info));
		jndex++;
	}
}
