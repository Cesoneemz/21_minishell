/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:29:43 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/18 18:11:36 by wlanette         ###   ########.fr       */
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

void	ft_free_all(t_info **info, t_tokens **tokens)
{
	ft_free_tokens(tokens);
	ft_free_cmd(info);
	free(info);
}

int	main(int argc, char **argv, char **envp)
{
	t_info		*info;
	char		*str;
	t_tokens	*tokens;

	(void)argc;
	(void)argv;
	info = ft_init_info();
//	info->env = ft_init_env(envp);
	while (!info->exit_t)
	{
		tokens = ft_new_token();
		str = ft_readline("minishell$>");
		if (str == NULL || ft_strncmp(str, "exit", 5) == 0)
		{
			info->exit_t = 1;
			ft_free_all(&info, &tokens);
		}
		if (ft_lexer(str, &tokens) == -1)
		{
			ft_print_error("Invalid syntax");
			continue ;
		}
		info->token_head = tokens;
		ft_parse_command(&info, tokens);
		ft_free_tokens(&tokens);
		ft_free_cmd(&info);
		free(str);
	}
	return (0);
}
