/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 12:55:05 by wmiyu             #+#    #+#             */
/*   Updated: 2022/09/13 17:20:23 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

# define TOK_BUFSIZE 64
# define TOK_DELIM " \t\r\n\a"

size_t	ft_strlen(const char *str);
char	**msh_split_line(char *line, const char *sep);
int		msh_launch(char **args);
int		msh_execute(char **args);
int		msh_num_builtins(char **builtin_str);
int		run_bultin_num(int fnum, char **args, char **builtin_str);
void	main_pipex2(int argc, char **argv, char **envp);
void	pipetokens_proceed(char	*line, char **envp);
char	**ft_split(char const *s, char c);
int		ft_split_count(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		child_proc_n(char *arg, char **envp);
int		child_proc_l(char *arg, char **envp);
int		execute(char **newargv, char **envp);
int		exec_in_recurse(int count, char **arg4, char **envp, int fd[2]);

#endif
