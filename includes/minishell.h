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
	NONE,
	ARG,
	TRUNC,
	INPUT,
	APPEND,
	PIPE,
	HEREDOC
}			t_token_types;

typedef struct s_tokens
{
	int				index;
	t_token_types 	type;
	char			*value;
	struct s_tokens	*next;
}				t_tokens;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_info
{
	char			builtins[7];
	char			reserved_word[7];
	char			**envp;
	t_list			envp_list;
	char			envp_f;
	char			exit_t;
}					t_info;

/* INITIALIZATION */

t_tokens	*ft_init_tokens_node(void);
t_env		*ft_init_env_node(void);
t_env		*ft_init_env_struct(char **envp);
t_info		*ft_init_info(void);

/* ENV */

char		*ft_get_env_vars(char *str, t_env *env);
t_env		*ft_get_env(t_env *env, char *var);

/* LEXER */

t_tokens	*ft_lexer(char *str, t_env *env);

/* UTILS */

char		*ft_remove_spaces(char *str);
void		ft_free_split(char **split);
int			ft_strclen(char *str, char c);


#endif