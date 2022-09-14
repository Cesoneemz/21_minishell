/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:17:17 by wlanette          #+#    #+#             */
/*   Updated: 2022/06/29 13:13:59 by wlanette         ###   ########.fr       */
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
	SEP,
	TRUNC,
	INPUT,
	APPEND,
	PIPE,
	HEREDOC,
	EXP_FIELD,
	FIELD
}			t_token_types;

typedef struct s_tokens
{
	int				len;
	t_token_types	type;
	char			*value;
	struct s_tokens	*next;
}				t_tokens;

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
}				t_cmd;

typedef struct s_env
{
	char	*key;
	char	*value;
}				t_env;

typedef struct s_info
{
	char			builtins[7];
	char			reserved_word[7];
	t_cmd			*cmd_list;
	int				cmd_count;
	t_list			*env;
	char			exit_t;
}					t_info;

/* INITIALIZATION */

t_info		*ft_init_info(void);
t_list		*ft_init_env(char **envp);

/* ENV */

char		*ft_get_env(t_list *env, char *key);

/* LEXER */

int			ft_lexer(char *str, t_tokens *tokens);
t_tokens	*ft_new_token(void);
int			ft_check_quotes(char *str);
int			ft_get_len_of_token(char *str, int index, t_tokens *tokens);

/* PARSER */

int			ft_parse_command(t_info *info, t_tokens *tokens);
int			ft_count_cmd(t_tokens *tokens);
int			ft_init_cmd(t_info *info, t_tokens *tokens);
int			ft_create_cmd(t_info *info, t_tokens **tokens, int index);
char		*ft_quotes_treatment(char *cmd, t_token_types type, t_info *info);
char		*ft_dollar_treatment(char *cmd, t_info *info, int index);
int			ft_count_args(t_tokens *tokens);


/* UTILS */

int			ft_is_space(char c);
char		*ft_remove_spaces(char *str);
void		ft_print_error(char *message);
int			ft_check_in_quotes(char *str, int pos, char quote, char other);
void		ft_free_tokens(t_tokens *tokens);

#endif