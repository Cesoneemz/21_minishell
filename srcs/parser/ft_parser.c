/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:05:58 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/15 05:06:01 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_command(t_info *info, t_tokens *tokens)
{
	int			index;
	int			jndex;
	int			args_count;
	t_tokens	*temp;

	if (!ft_init_cmd(info, tokens))
		return (-1);
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
			ft_create_cmd(info, &tokens, index);
	}
	tokens = temp;
	ft_free_tokens(tokens);
	return (1);
}
