/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:55:05 by wmiyu             #+#    #+#             */
/*   Updated: 2022/06/14 16:45:07 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TOK_BUFSIZE 64
# define TOK_DELIM " \t\r\n\a"
# define CLOSE "\033[0m"
# define BOLDGREEN "\033[1m\033[49;32m"

char	**msh_split_line(char *line);
int		msh_launch(char **args);
int		msh_execute(char **args);
int		msh_num_builtins(char **builtin_str);
int		run_bultin_num(int fnum, char **args, char **builtin_str);

#endif
