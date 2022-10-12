/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_validators_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 01:23:53 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/13 01:31:06 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			while (temp->type == SEP)
				temp = temp->next;
			if (temp && temp->type == PIPE)
			{
				ft_print_error("Invalid syntax: parse error near \'|\'\n");
				return (-1);
			}
		}
	}
	return (0);
}
