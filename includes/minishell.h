/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 11:17:17 by wlanette          #+#    #+#             */
/*   Updated: 2022/06/06 13:34:16 by wlanette         ###   ########.fr       */
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

typedef int	(*t_builtin_ptr)(t_list *, t_info *);

typedef struct s_info
{
	t_builtin_ptr	builtins[7];
	char			reserved_word[7];
	char			**envp;
	t_list			envp_list;
	char			envp_f;
	char			exit_t;
}					t_info;

t_info		*ft_init_info(void);

#endif