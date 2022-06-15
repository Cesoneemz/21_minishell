/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 18:02:01 by wmiyu             #+#    #+#             */
/*   Updated: 2022/05/31 18:05:38 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(char *msg)
{
	perror(msg);
	exit (EXIT_FAILURE);
}

void	usage(void)
{
	write(1, "Error: Bad arguments\n", 21);
	write(1, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 37);
	exit (EXIT_SUCCESS);
}

void	usage_bonus(void)
{
	write(1, "Error: Bad arguments\n", 21);
	write(1, "Usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 51);
	write(1, "Usage: ./pipex here_doc LIMITER cmd cmd1 file\n", 46);
	exit (EXIT_SUCCESS);
}
