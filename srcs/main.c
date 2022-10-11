/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:29:43 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/07 16:49:21 by wmiyu            ###   ########.fr       */
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
	if (signal == 2)
	{
		printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
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
	if (ft_parse_command(info, (*tokens)) == -1)
		return (-2);
	return (0);
}

char	**make_cmd_list(t_info *info);

int	main(int argc, char **argv, char **envp)
{
	t_info		*info;
	char		*str;
	t_tokens	*tokens;
	char		**cmd_list;
	int			most_recent_code;

	(void)argc;
	(void)argv;
	//rl_catch_signals = 0;
	most_recent_code = 0;
	info = ft_init_info();
	info->env = ft_init_env(envp);
	signal(SIGINT, ft_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		tokens = ft_new_token();
		str = ft_readline(" (_*_) MiniShell v.0.15e $> ");
		if (ft_strlen(str) <= 0)
			continue ;
		if (ft_strncmp(str, "$?", 2) == 0)
		{
			printf("-minishell: %d: command not found \n", most_recent_code);
			continue ;
		}	
		if (ft_main_loop(&info, &tokens, str) == -2)
			continue ;
	//	print_tmp_tokens(info);
		cmd_list = make_cmd_list(info);
		if (info->cmd_count == 1 &&  check_builtins(cmd_list[0]))
		{
			most_recent_code = ft_run_builtin(cmd_list, info);
		}
		else
			most_recent_code = exec_in_recurse1(info->cmd_count, cmd_list, make_env_list(info->env), NULL);
		info->exit_code = most_recent_code;
/*=-=-=-=-=-==-=======---=-=-=-=-=-=-=-=-=-=-=-=-=-
		if (most_recent_code == 153)
			most_recent_code = ft_cd_parent(cmd_list);
		else if (most_recent_code == 154)
			most_recent_code = ft_built_env(cmd_list, envp);
=-=-=-=-=-==-=======---=-=-=-=-=-=-=-=-=-=-=-=-=-*/
		ft_freesplit(&cmd_list);
		ft_free_all(&info, &tokens, str);
	}
	return (0);
}
