/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 10:42:36 by wlanette          #+#    #+#             */
/*   Updated: 2022/06/29 13:48:55 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc_str(char *str, char c)
{
	char	*result;
	char	*s_str;
	char	*tmp;

	result = (char *)malloc(sizeof(char) * 2);
	if (!result)
		return (NULL);
	s_str = str;
	if (!s_str)
	{
		s_str = (char *)malloc(sizeof(char));
		if (!s_str)
			return (NULL);
		s_str[0] = '\0';
	}
	result[0] = c;
	result[1] = '\0';
	tmp = result;
	result = ft_strjoin(s_str, result);
	free(tmp);
	free(s_str);
	return (result);
}
