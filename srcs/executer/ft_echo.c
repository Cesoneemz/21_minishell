/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:20:57 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/23 15:19:07 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	ft_echo(char **arglist)
{
	int	i;
	int	n_opt;

	i = 0;
	n_opt = 0;
	if (!arglist[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	else if (arglist[1] && ft_strncmp("-n", arglist[1], 2) == 0)
	{
		i++;
		n_opt = 1;
	}
	while (arglist[++i])
	{
		write(STDOUT_FILENO, arglist[i], ft_strlen(arglist[i]));
		write(STDOUT_FILENO, " ", 1);
	}
	if (!n_opt)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
