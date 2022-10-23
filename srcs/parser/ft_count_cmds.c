/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:04:32 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/23 15:01:27 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_args(t_tokens *tokens)
{
	int			index;
	t_tokens	*temp;

	index = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->type == PIPE)
			break ;
		if (temp->type == SEP)
		{
			temp = temp->next;
			continue ;
		}
		temp = temp->next;
		index++;
	}
	return (index);
}

int	ft_count_cmd(t_tokens *tokens)
{
	t_tokens	*temp;
	int			counter;

	temp = tokens;
	counter = 1;
	while (1)
	{
		if (temp->type == PIPE)
		{
			counter++;
			if (temp->next && temp->next->type == PIPE)
				return (-1);
		}
		if (temp->next == NULL)
			break ;
		temp = temp->next;
	}
	if (temp->type == TRUNC || temp->type == INPUT || \
	temp->type == APPEND || temp->type == HEREDOC)
		return (-1);
	return (counter);
}

char	*ft_check_dollar_exceptions(char *cmd, int *index, t_info *info)
{
	if (cmd[(*index) + 1] == '?')
	{
		(*index) += 2;
		return (ft_itoa(info->exit_code));
	}
	if (cmd[(*index)] == '$' && \
	(!ft_isascii(cmd[(*index) + 1]) || cmd[(*index) + 1] == '\0'))
		return (ft_strdup("$"));
	return (NULL);
}
