# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 11:31:44 by wlanette          #+#    #+#              #
#    Updated: 2022/06/29 11:19:37 by wlanette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRCS		= ./srcs/main.c ./srcs/ft_init.c ./srcs/ft_lexer.c \
				./srcs/utils/ft_remove_spaces.c ./srcs/utils/ft_free_split.c ./srcs/utils/ft_strclen.c \
				./srcs/env/ft_env_utils.c
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
