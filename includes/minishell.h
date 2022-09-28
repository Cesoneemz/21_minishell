/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:17:17 by wlanette          #+#    #+#             */
/*   Updated: 2022/09/28 18:05:00 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
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
	char			exit_t;
}					t_info;

/* INITIALIZATION */

t_info			*ft_init_info(void);
t_env			*ft_init_env(char **envp);

/* ENV */

char			*ft_get_env(t_env *env, char *key);
void			ft_lstadd_back_env(t_env **lst, t_env *new);
t_env			*ft_lstnew_env(char *key, char *value);
t_env			*ft_init_env_node(void);

/* LEXER */

int				ft_lexer(char *str, t_tokens **tokens);
t_tokens		*ft_new_token(void);
int				ft_check_quotes(char *str);
int				ft_get_len_of_token(char *str, int index, t_tokens *tokens);
int				ft_finally_lex_analyze(t_tokens *tokens);
void			ft_lexer_loop(char *str, t_tokens **tokens);
int				ft_tokenize_sep(char *str, int index, t_tokens *tokens);
int				ft_tokenize_quotes(char *str, int index, t_tokens *tokens);
int				ft_tokenize_str(char *str, int index, t_tokens *tokens);
void			ft_get_type_of_token(t_tokens *tokens);

/* PARSER */

int				ft_parse_command(t_info **info, t_tokens *tokens);
int				ft_count_cmd(t_tokens *tokens);
int				ft_init_cmd(t_info **info, t_tokens *tokens);
void			ft_create_cmd(t_info *info, t_tokens **tokens, int index);
char			*ft_quotes_treatment(char *cmd, t_token_types type, \
									t_info *info);
char			*ft_dollar_treatment(char *cmd, t_info *info, int index);
int				ft_is_redirect(t_token_types type);
t_token_types	ft_get_new_type(t_token_types type);
int				ft_get_exec_line(t_info **info);

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

#endif