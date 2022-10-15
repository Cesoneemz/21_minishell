/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:29:43 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/15 21:34:43 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

static char	*ft_readline(char *prompt)
{
	char	*res;

	res = readline(prompt);
	if (ft_strlen(res) > 0)
		add_history(res);
	return (res);
}

static void	ft_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		ft_print_error("Exit (core dumped)");
		write(1, "\b\b  \b\b", 7);
		exit (1);
	}
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
	if (ft_parse_command(info, (*tokens)) == -1)
		return (-2);
	return (0);
}

int	main_1st_loop(t_info *info)
{
	t_tokens	*tokens;
	char		*str;
	char		**cmd_list;

	while (1)
	{
		tokens = ft_new_token();
		str = ft_readline(" (_*_) MiniShell v.0.20e $> ");
		if (!str)
			break ;
		if (ft_strlen(str) <= 0)
			continue ;
		if (ft_main_loop(&info, &tokens, str) == -2)
			continue ;
		cmd_list = make_cmd_list2(info);
		if (info->cmd_count == 1 && check_builtins2(cmd_list[1]))
			info->exit_code = ft_run_builtin2(cmd_list, info);
		else
			info->exit_code = ft_exec_semi(dup(STDIN_FILENO), \
			cmd_list, make_env_list(info->env));
		ft_freesplit(&cmd_list);
		ft_free_all(&info, &tokens, str);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info		*info;

	(void)argc;
	(void)argv;
	//rl_catch_signals = 0;
	info = ft_init_info();
	info->env = ft_init_env(envp);
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	return (main_1st_loop(info));
}
/*
		//print_tmp_tokens(info);
		//printf("count: %d\n\n", count_tmp_tokens2(info));
		//printf("\t _info->exit_code: %d\n", info->exit_code);
*/