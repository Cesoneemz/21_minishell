/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:29:43 by wlanette          #+#    #+#             */
/*   Updated: 2022/06/29 12:29:21 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_readline(char *prompt)
{
	char	*res;

	res = readline(prompt);
	if (res)
		add_history(res);
	return (res);
}

int	main(void)
{
	t_info	*info;
	char	*str;
	char	**tokens;

	info = ft_init_info();
	while (!info->exit_t)
	{
		str = ft_readline("minishell$>");
		if (str == NULL)
			info->exit_t = 1;
		tokens = ft_lexer(str);
	}
	free(info);
	return (0);
}
