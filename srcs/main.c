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

static void	ft_signal_handler(int signal)
{
	rl_on_new_line();
	rl_redisplay();
	if (signal == SIGINT)
	{
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "  \b\b", 4);
}

int	main(int argc, char **argv, char **envp)
{
	t_info		*info;
	t_env		*env;
	char		*str;
	t_tokens	*tokens;

	(void)argc;
	(void)argv;
	info = ft_init_info();
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
	tokens = ft_new_token();
	while (!info->exit_t)
	{
		str = ft_readline("minishell$>");
		if (str == NULL || ft_strncmp(str, "exit", 5) == 0)
			info->exit_t = 1;
		str = ft_remove_spaces(str);
		ft_lexer(str, tokens);
	}
	free(info);
	return (0);
}
