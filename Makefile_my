# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 11:31:44 by wlanette          #+#    #+#              #
#    Updated: 2022/09/13 18:03:24 by wmiyu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRCS		= 	./srcs/main.c \
				./srcs/ft_split.c\
				./srcs/pip8.c \
				./srcs/execute.c \
				./srcs/ft_strjoin.c 
				
OBJS		= $(SRCS:.c=.o)

INCS		= ./includes/
INCS_HEADER	= ./includes/minishell.h

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I$(INCS) -g
RM			= rm -rf

LIBFT		= ./includes/libft/libft.a

all:		$(NAME)

$(NAME):	$(OBJS) $(INCS_HEADER)
			$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

$(LIBFT):	
			@make bonus -C ./includes/libft/

clean:		
#			@make clean -C ./includes/libft/
			$(RM) $(OBJS)

fclean:		clean
#			@make fclean -C ./includes/libft/
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
