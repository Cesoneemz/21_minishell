/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joiner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 19:25:35 by Wmiyu             #+#    #+#             */
/*   Updated: 2022/09/14 19:27:53 by Wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strcpy(const char *src)
{
	int		i;
	int		len;
	char	*dst;

	i = 0;
	len = 0;
	while (src[i++])
		len++;
	dst = (char *)malloc(sizeof(char) + len);
	dst[len] = '\0';
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (dst);
}

char	**join_argv_arr(char *cmd, char **argv)
{
	int		arg_count;
	int		i;
	char	**res_arr;

	i = 0;
	arg_count = 0;
	while (argv[i++])
		arg_count++;
	res_arr = (char **)malloc(sizeof(char *) * (arg_count + 2));
	if (!res_arr)
		return (NULL);
	res_arr[arg_count + 1] = NULL;
	res_arr[0] = ft_strcpy(cmd);
	i = 0;
	while (argv[i])
	{
		res_arr[i + 1] = ft_strcpy(argv[i]);
		i++;
	}
	return (res_arr);
}
