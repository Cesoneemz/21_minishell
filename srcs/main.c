/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:29:43 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/25 15:58:58 by wlanette         ###   ########.fr       */
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
	if (signal == 2)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		ft_print_error("Exit (core dumped)");
		exit (1);
	}
}

void	ft_free_all(t_info **info, t_tokens **tokens, char *str)
{
	ft_free_tokens(tokens);
	ft_free_cmd(info);
	free(str);
}

int	ft_main_loop(t_info **info, t_tokens **tokens, char *str)
{
	if (ft_lexer(str, tokens) == -1)
	{
		if (tokens)
			ft_free_tokens(tokens);
		free(str);
		return (-2);
	}
	(*info)->token_head = (*tokens);
	ft_parse_command(info, (*tokens));
}

int	main(int argc, char **argv, char **envp)
{
	t_info		*info;
	char		*str;
	t_tokens	*tokens;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	info = ft_init_info();
	info->env = ft_init_env(envp);
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (!info->exit_t)
	{
		tokens = ft_new_token();
		str = ft_readline("minishell$>");
		if (str == NULL || ft_strncmp(str, "exit", 5) == 0)
		{
			ft_free_exit(&tokens, &info, str);
			break ;
		}
		if (ft_main_loop(&info, &tokens, str) == -2)
			continue ;
		ft_free_all(&info, &tokens, str);
	}
	return (0);
}
