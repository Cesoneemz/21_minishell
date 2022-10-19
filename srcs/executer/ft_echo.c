/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 23:20:57 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/18 17:27:59 by wmiyu            ###   ########.fr       */
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
		write(STDOUT_FILENO, "(empty)", 7);
	else if (arglist[1] && strncmp("-n", arglist[1], 2) == 0)
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
