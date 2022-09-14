/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:29:43 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/14 19:22:58 by Wmiyu            ###   ########.fr       */
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
	char		*str;
	t_tokens	*tokens;
    int         index = 0;

	(void)argc;
	(void)argv;
	info = ft_init_info();
	info->env = ft_init_env(envp);
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, ft_signal_handler);
	while (!info->exit_t)
	{
		tokens = ft_new_token();
		str = ft_readline("minishell$>");
		if (str == NULL || ft_strncmp(str, "exit", 5) == 0)
			info->exit_t = 1;
		if (ft_lexer(str, tokens) == -1)
		{
			ft_print_error("Invalid syntax");
			continue ;
		}
		ft_parse_command(info, tokens);

		exec_in_recurse2(info->cmd_count, info, envp, NULL);
	}
	free(info);
	return (0);
}
