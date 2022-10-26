/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:03:49 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/25 15:07:36 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_error(char *message)
{
	char	*res;

	if (message)
	{
		res = ft_strjoin("minishell: ", message);
		write(2, res, ft_strlen(res));
		free(res);
	}
	return ;
}
