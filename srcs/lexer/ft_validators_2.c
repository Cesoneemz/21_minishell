/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validators_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 01:23:53 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/13 16:40:06 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_parse_pipe_next(t_tokens *temp)
{
	while (temp->type == SEP)
		temp = temp->next;
	if (temp && temp->type == PIPE)
	{
		ft_print_error("Invalid syntax: parse error near \'|\'\n");
		return (-1);
	}
	return (0);
}

int	ft_check_pipes(t_tokens *temp, t_tokens *prev)
{
	if (temp->type == PIPE)
	{
		if (prev == NULL)
		{
			ft_print_error("Invalid syntax: parse error near \'|\'\n");
			return (-1);
		}
		if (temp->next && temp->next->type == PIPE)
		{
			ft_print_error("Invalid syntax: parse error near \'||\'\n");
			return (-1);
		}
		temp = temp->next;
		if (temp)
		{
			if (ft_parse_pipe_next(temp) == -1)
				return (-1);
		}
		else
			return (-1);
	}
	return (0);
}
