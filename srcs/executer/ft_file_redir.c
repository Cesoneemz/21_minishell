/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 15:25:21 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/15 21:11:01 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

int	param_count(char ***par)
{
	int	t_cnt;
	int	i;

	i = 0;
	t_cnt = 0;
	while (*(par[0] + i))
	{
		i++;
		t_cnt++;
	}
	return (t_cnt);
}

void	param_shift(char ***par, int offset)
{
	int	t_cnt;
	int	i;

	i = 0;
	t_cnt = param_count(par);
	while (i < t_cnt - offset)
	{
		*(par[0] + i) = *(par[0] + i + offset);
		i++;
	}	
	*(par[0] + i) = NULL;
	t_cnt = param_count(par);
}

int	file_in_redir(char *filename, char *redirect)
{
	int	file;

	(void)redirect;
	//printf(" FOUND < REDIRECT: %s %s\n", redirect, filename);
	file = -1;
	file = open(filename, O_RDONLY, 0777);
	if (file == -1)
	{
		perror(filename);
		return (-1);
	}
	dup2(file, STDIN_FILENO);
	close(file);
	return (file);
}

int	file_opn_redir(char *filename, char *redirect)
{
	int	file;
	int	file_mode;

	//printf(" FOUND > REDIRECT: %s %s\n", redirect, filename);
	file = -1;
	if (redirect[0] == '>' && redirect[1] == '>' )
		file_mode = O_WRONLY | O_CREAT | O_APPEND;
	else
		file_mode = O_WRONLY | O_CREAT | O_TRUNC;
	file = open(filename, file_mode, 0777);
	if (file == -1)
	{
		perror(filename);
		return (-1);
	}
	dup2(file, STDOUT_FILENO);
	close(file);
	return (file);
}
