/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_gnl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 15:16:14 by wmiyu             #+#    #+#             */
/*   Updated: 2022/06/01 13:33:54 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_next_line(char **line, int fd)
{
	int		i;
	char	*buffer;
	char	c;
	int		rd;

	i = 0;
	c = '\0';
	rd = 0;
	buffer = malloc(100000);
	if (!buffer)
		return (-1);
	rd = read(fd, &c, 1);
	while (rd > 0 && c != '\n')
	{
		buffer[i++] = c;
		rd = read(fd, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (rd);
}
