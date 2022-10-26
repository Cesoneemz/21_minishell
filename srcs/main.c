/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:29:43 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/26 01:39:20 by wlanette         ###   ########.fr       */
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

int	ft_main_loop(t_info **info, t_tokens **tokens, char *str)
{
	char	**cmd_list;
	char	**save;

	if (ft_lexer(str, tokens) == -1)
	{
		if (tokens)
			ft_free_tokens(tokens);
		return (-2);
	}
	(*info)->token_head = (*tokens);
	if (ft_parse_command(info, (*tokens)) == -1)
		return (-2);
	cmd_list = NULL;
	save = NULL;
	ft_get_exec_line(info, &cmd_list, &save);
	return (0);
}

void	main_2st_loop(t_info *info, char ***cmd_list, char ***env_list)
{
	(*cmd_list) = make_cmd_list2(info);
	(*env_list) = make_env_list(info->env);
	if (info->cmd_count == 1 && check_builtins2((*cmd_list)[1]))
		info->exit_code = ft_run_builtin2((*cmd_list), info);
	else
		info->exit_code = ft_exec_semi(dup(0), (*cmd_list), (*env_list));
	ft_freesplit(env_list);
	ft_freesplit(cmd_list);
}

int	main_1st_loop(t_info *info)
{
	t_tokens	*tokens;
	char		*str;
	char		**cmd_list;
	char		**env_list;

	while (1)
	{
		tokens = ft_new_token();
		str = ft_readline(" (_*_) MiniShell v.1.0 $> ");
		if (!str)
			exit(1);
		if (ft_strlen(str) <= 0 || !ft_check_str_is_empty(str) \
		|| ft_main_loop(&info, &tokens, str) == -2)
		{
			ft_free_tokens(&tokens);
			free(str);
			continue ;
		}
		main_2st_loop(info, &cmd_list, &env_list);
		ft_free_all(&tokens, &info, str);
	}
	ft_free_exit(&tokens, &info, str);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_info		*info;

	(void)argc;
	(void)argv;
	rl_catch_signals = 0;
	info = ft_init_info();
	info->env = ft_init_env(envp);
	ft_handle_global_signals();
	main_1st_loop(info);
	return (0);
}
