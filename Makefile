# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/06 11:31:44 by wlanette          #+#    #+#              #
#    Updated: 2022/06/14 17:42:46 by wmiyu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
SRCS		= split_line.c launcher.c builtins.c main.c
OBJS		= $(SRCS:.c=.o)

CC			= clang
CFLAGS		= -Wall -Werror -Wextra -g
RM			= rm -rf

#all:
#	gcc -g -Wall -Werror -Wextra -lreadline split_line.c launcher.c builtins.c main.c -o minishell0

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)

clean:		
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
