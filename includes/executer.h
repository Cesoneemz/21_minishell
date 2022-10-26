/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:17:17 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/23 14:29:30 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "minishell.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

/* EXECUTER */
size_t			ft_strlen(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
void			ft_freesplit(char ***ptr);
int				ft_split_count(char const *s, char c);
int				ft_echo(char **arglist);
int				ft_pwd(char **arglist);
int				ft_built_env(char **arglist, t_env *env);
int				ft_write_env(char **arglist, char	**env_list);
int				ft_exec_z(char *cmd_path, char **newargv, char **envp);
char			**make_env_list(t_env *env);
int				ft_export_env(char **arglist, t_env *env);
t_env			*ft_lstlast_env(t_env *lst);
int				ft_unset_env(char **arglist, t_env **env);
int				ft_cd_parent2(char **arglist, t_env *env);
char			*find_cmd_in_path(char *cmd, char **envp);
char			**make_cmd_list2(t_info *info);
int				ft_exec_semi(int tmp_fd, char **argv, char **envp);
int				param_count(char ***par);
void			param_shift(char ***par, int offset);
int				file_in_redir(char *filename, char *redirect);
int				file_opn_redir(char *filename, char *redirect);
int				check_builtins2(char *cmd);
int				check_builtins3(char *cmd);
int				ft_run_builtin2(char **arglist, t_info *info);
int				ft_run_builtin3(char **arglist, char **envp);
int				ft_putstr_fd2(char *str, char *arg);
int				ft_try_heredoc(int i, char **argv, int *tmp_fd);
void			ft_try_open_redir(int t_cnt, char **argv);
int				ft_heredoc_mode(char *delim);
void			print_tmp_tokens(t_info *info);
char			*get_next_line(int fd);
#endif
