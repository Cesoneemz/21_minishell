/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:17:17 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/05 14:59:13 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

/* EXECUTER */
size_t		ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
void		ft_freesplit(char ***ptr);
int			ft_split_count(char const *s, char c);
int			execute(char **newargv, char **envp);
int			execute2(char *newcmd, char **newargv, char **envp);
int			exec_in_recurse1(int count, char **arg4, char **envp, int fd[2]);
char		**join_argv_arr(char *cmd, char **argv);
int			check_builtins(char *cmd);
int			ft_run_builtin(char **cmd_list, t_info *info);
int			ft_echo(char **arglist);
int			ft_built_env(char **arglist, t_env *env);
int			ft_exec_z(char *cmd_path, char **newargv, char **envp);
void		print_env_tokens(t_env *env);
char		**make_env_list(t_env *env);
int			ft_export_env(char **arglist, t_env *env);
t_env		*ft_lstlast_env(t_env *lst);
int			ft_unset_env(char **arglist, t_env **env);
int			ft_cd_parent2(char **arglist, t_env *env);
#endif
