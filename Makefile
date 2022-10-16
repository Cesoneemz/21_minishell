# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 11:31:44 by wlanette          #+#    #+#              #
#    Updated: 2022/10/16 16:55:12 by wmiyu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRCS		= ./srcs/main.c ./srcs/ft_init.c ./srcs/lexer/ft_lexer.c \
				./srcs/utils/ft_print_error.c ./srcs/lexer/ft_validators.c ./srcs/lexer/ft_lexer_utils.c\
				./srcs/lexer/ft_init_tokens.c ./srcs/utils/ft_is_space.c ./srcs/utils/ft_free_tokens.c \
				./srcs/env/ft_env.c ./srcs/parser/ft_count_cmds.c ./srcs/parser/ft_init_cmds.c \
				./srcs/parser/ft_parser.c ./srcs/parser/ft_treatment.c ./srcs/env/ft_env_list.c \
				./srcs/env/ft_env_set.c ./srcs/lexer/ft_validators_2.c\
				./srcs/parser/ft_parser_utils.c ./srcs/utils/ft_free_in_loop.c \
				./srcs/executer/ft_builtins.c ./srcs/executer/ft_exec_z.c \
				./srcs/executer/ft_execute.c ./srcs/executer/ft_joiner.c \
				./srcs/executer/ft_file_redir.c ./srcs/executer/ft_split.c ./srcs/executer/ft_strjoin.c \
				./srcs/executer/ft_make_cmd.c ./srcs/executer/ft_cd.c \
				./srcs/executer/ft_echo.c ./srcs/executer/ft_built_env.c \
				./srcs/executer/ft_make_env.c ./srcs/executer/ft_exec_semi.c  \
				./srcs/executer/ft_here_doc.c
OBJS		= $(SRCS:.c=.o)

INCS		= ./includes/
INCS_HEADER	= ./includes/minishell.h

CC			= clang
CFLAGS		= -I$(INCS) -g -Wall -Wextra -I/opt/homebrew/opt/readline/include -L/opt/homebrew/opt/readline/lib -lreadline 
RM			= rm -rf

LIBFT		= ./includes/libft/libft.a
READLINE    = -I/opt/homebrew/opt/readline/include -L/opt/homebrew/opt/readline/lib -lreadline

all:		$(NAME) $(LIBFT)

$(NAME):	$(OBJS) $(INCS_HEADER) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
			

$(LIBFT):	
			@make bonus -C ./includes/libft/

clean:		
			@make clean -C ./includes/libft/
			$(RM) $(OBJS)

fclean:		clean
			@make fclean -C ./includes/libft/
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
