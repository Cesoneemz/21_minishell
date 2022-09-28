# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 11:31:44 by wlanette          #+#    #+#              #
#    Updated: 2022/09/28 23:03:11 by wmiyu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRCS		= ./srcs/main.c ./srcs/ft_init.c ./srcs/lexer/ft_lexer.c \
				./srcs/utils/ft_print_error.c ./srcs/lexer/ft_validators.c ./srcs/lexer/ft_lexer_utils.c\
				./srcs/lexer/ft_init_tokens.c ./srcs/utils/ft_is_space.c ./srcs/utils/ft_free_tokens.c \
				./srcs/env/ft_env.c ./srcs/parser/ft_count_cmds.c ./srcs/parser/ft_init_cmds.c \
				./srcs/parser/ft_parser.c ./srcs/parser/ft_treatment.c ./srcs/env/ft_env_list.c \
				./srcs/parser/ft_parser_utils.c ./srcs/utils/ft_free_in_loop.c \
				./srcs/executer/ft_builtins.c ./srcs/executer/ft_exec_z.c \
				./srcs/executer/ft_execute.c ./srcs/executer/ft_joiner.c \
				./srcs/executer/ft_pip11.c ./srcs/executer/ft_split.c ./srcs/executer/ft_strjoin.c \
				./srcs/executer/ft_make_cmd.c
OBJS		= $(SRCS:.c=.o)

INCS		= ./includes/
INCS_HEADER	= ./includes/minishell.h

CC			= cc
CFLAGS		= -I$(INCS) -g
RM			= rm -rf

LIBFT		= ./includes/libft/libft.a

all:		$(NAME) $(LIBFT)

$(NAME):	$(OBJS) $(INCS_HEADER) $(LIBFT)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include -o $(NAME)

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
