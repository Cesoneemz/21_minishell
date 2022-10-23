/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 13:14:46 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/23 19:12:42 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_str_is_empty(char *str)
{
	int	index;
	int	flag;

	index = 0;
	flag = 0;
	while (str[index] != '\0')
	{
		if (!ft_is_space(str[index]))
		{
			flag = 1;
			break ;
		}
		index++;
	}
	return (flag);
}

t_info	*ft_init_info(void)
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->cmd_list = NULL;
	info->cmd_count = 0;
	info->exit_code = 0;
	return (info);
}
