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

t_info		*ft_init_info(void);

/* LEXER */

void		ft_lexer(char *str, t_tokens *tokens);
t_tokens	*ft_new_token(void);
int			ft_check_quotes(char *str);

/* UTILS */

int			ft_is_space(char c);
char		*ft_remove_spaces(char *str);
void		ft_print_error(char *message);
int			ft_check_in_quotes(char *str, int pos, char quote, char other);

#endif