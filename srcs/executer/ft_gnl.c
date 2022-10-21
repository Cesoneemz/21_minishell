/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 00:28:15 by Wmiyu             #+#    #+#             */
/*   Updated: 2022/10/21 18:55:52 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

char	*get_line(char *reminder)
{
	char	*line;
	int		i;

	i = 0;
	if (!reminder[i])
		return (0);
	while (reminder[i] && reminder[i] != '\n')
		i++;
	line = (char *) malloc (i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (reminder[i] && reminder[i] != '\n')
	{
		line[i] = reminder[i];
		i++;
	}
	if (reminder[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*reset_reminder(char *reminder)
{
	char	*minusline;
	int		i;
	int		len2;

	i = 0;
	while (reminder[i] && reminder[i] != '\n')
		i++;
	if (!reminder[i])
	{
		free(reminder);
		return (0);
	}
	len2 = ft_strlen(reminder) - i;
	minusline = (char *) malloc (len2 + 1);
	if (!minusline)
		return (NULL);
	minusline[len2] = '\0';
	while (--len2 >= 0)
		minusline[len2] = reminder[i + 1 + len2];
	free(reminder);
	return (minusline);
}

int	check_for_eol(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*reminder;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (check_for_eol(reminder) && bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		reminder = ft_strjoin(reminder, buffer);
	}
	free(buffer);
	buffer = get_line(reminder);
	reminder = reset_reminder(reminder);
	return (buffer);
}
