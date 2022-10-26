/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:17:17 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/26 09:25:38 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <termios.h>
# include <term.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include "./libft/libft.h"

typedef enum s_token_types
{
	WORD,
	BUILTIN,
	SEP,
	TRUNC,
	INPUT,
	APPEND,
	PIPE,
	HEREDOC,
	EXP_FIELD,
	FIELD,
	FILE_IN,
	FILE_OUT,
	FILE_OUT_APPEND,
	HEREDOC_ENDLINE
}			t_token_types;

typedef struct s_tokens
{
	int				len;
	t_token_types	type;
	char			*value;
	struct s_tokens	*next;
}				t_tokens;

typedef struct s_redir
{
	int			redir_in_fd;
	int			redir_out_fd;
	int			dup_fd_in;
	int			dup_fd_out;
}				t_redir;

typedef struct s_cmd_line
{
	char				*arg;
	t_token_types		type;
}					t_cmd_line;

typedef struct s_cmd
{
	t_tokens	*sep_tokens;
	char		**exec_line;
	t_redir		*redir;
}				t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_info
{
	t_cmd			*cmd_list;
	t_tokens		*token_head;
	int				cmd_count;
	int				cmd_with_args_count;
	t_env			*env;
	char			exit_code;
}					t_info;

/* INITIALIZATION */

t_info			*ft_init_info(void);
t_env			*ft_init_env(char **envp);
int				ft_check_str_is_empty(char *str);

/* ENV */

char			*ft_get_env(t_env *env, char *key);
void			ft_lstadd_back_env(t_env **lst, t_env *new);
t_env			*ft_lstnew_env(char *key, char *value);
t_env			*ft_init_env_node(void);
void			ft_set_env(t_env **env, char *key, char *value);
void			ft_init_env_misc(t_env **env);

/* LEXER */

int				ft_lexer(char *str, t_tokens **tokens);
t_tokens		*ft_new_token(void);
int				ft_check_quotes(char *str);
int				ft_get_len_of_token(char *str, int index, t_tokens *tokens);
int				ft_finally_lex_analyze(t_tokens *tokens);
void			ft_lexer_loop(char *str, t_tokens **tokens);
int				ft_tokenize_sep(char *str, int index, t_tokens *tokens);
int				ft_tokenize_quotes(char *str, int index, t_tokens *tokens, \
									char quote);
int				ft_tokenize_str(char *str, int index, t_tokens *tokens);
void			ft_get_type_of_token(t_tokens *tokens);
int				ft_check_pipes(t_tokens *temp, t_tokens *prev);

/* PARSER */

int				ft_parse_command(t_info **info, t_tokens *tokens);
int				ft_count_cmd(t_tokens *tokens);
int				ft_init_cmd(t_info **info, t_tokens *tokens);
int				ft_create_cmd(t_info *info, t_tokens **tokens, int index);
char			*ft_parse_cmd_part_2(int *index, t_info **info, char *cmd, \
									t_token_types type);
char			*ft_quotes_treatment(char *cmd, t_token_types type, \
									t_info *info);
char			*ft_dollar_treatment(char *cmd, t_info *info, int *index);
char			*ft_word_treatment(char *cmd, int *index, char c);
int				ft_is_redirect(t_token_types type);
t_token_types	ft_get_new_type(t_token_types type);
int				ft_get_exec_line(t_info **info, char ***cmd_list, char ***save);
char			*ft_add_char_to_str(char *str, char c);
char			*ft_check_dollar_exceptions(char *cmd, \
int *index, t_info *info);
void			ft_rebuild_cmd(char **array, t_tokens **new_list);
int				ft_is_head(t_token_types type);
int				ft_get_redirection_count(t_tokens *temp);
int				ft_is_field(t_token_types type);
void			ft_free_all_lists(char **cmd_list);
char			**ft_get_redirect(t_tokens *temp);
char			*ft_parse_cmd_part3(t_token_types type, char *cmd, int *index);

/* SIGNALS */

void			ft_handle_global_signals(void);
void			ft_handle_fork_signals(void);

/* UTILS */

int				ft_is_space(char c);
char			*ft_remove_spaces(char *str);
void			ft_print_error(char *message);
int				ft_check_in_quotes(char *str, int pos, char quote, char other);
void			ft_free_tokens(t_tokens **tokens);
void			ft_free_cmd(t_info **info);
void			ft_free_env(t_env **env);
int				ft_is_builtin(char *str);
void			ft_free_exit(t_tokens **tokens, t_info **info, char *str);
void			ft_free_all(t_tokens **tokens, t_info **info, char *str);

#endif