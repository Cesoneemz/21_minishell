/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 01:11:25 by Wmiyu             #+#    #+#             */
/*   Updated: 2022/09/28 22:05:42 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executer.h"

static void	ft_strxlcpy(const char *str1, char *dst, int x, int l)
{
	int		i;

	i = 0;
	while (i < l)
	{
		dst[i] = str1[x + i];
		i++;
	}
	dst[i] = '\0';
}

int	ft_split_count(char const *s, char c)
{
	size_t	i;
	size_t	y;
	size_t	n;

	i = 0;
	y = 0;
	n = 0;
	while (i <= ft_strlen(s))
	{
		while (i <= ft_strlen(s))
		{
			if (s[i] == c || i == ft_strlen(s))
			{
				if (i - y)
					n++;
				y = ++i;
				break ;
			}
			i++;
		}
	}
	return (n);
}

static void	ft_freeleek(char **ed)
{
	while (*ed)
	{
		free(*ed++);
	}
	free (ed);
}

static void	ft_fillme(size_t i, const char *s, char c, char **ed)
{
	size_t	y;
	size_t	n;

	y = 0;
	n = 0;
	while (i <= ft_strlen(s))
	{
		while (i <= ft_strlen(s))
		{
			if (s[i] == c || i == ft_strlen(s))
			{
				if (i - y)
				{
					ed[n] = (char *)malloc(sizeof(char) * (i - y + 1));
					if (!ed[n])
						ft_freeleek(ed);
					ft_strxlcpy(s, ed[n], y, i - y);
					n++;
				}
				y = ++i;
				break ;
			}
			i++;
		}
	}
}

char	**ft_split(char const *s, char c)
{
	size_t	n;
	size_t	i;
	char	**ed;

	if (!s)
		return (NULL);
	n = ft_split_count(s, c);
	ed = (char **)malloc(sizeof(char *) * (n + 1));
	if (!ed)
		return (NULL);
	ed[n] = NULL;
	i = 0;
	ft_fillme(i, s, c, ed);
	return (ed);
}
