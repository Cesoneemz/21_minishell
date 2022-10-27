# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/05 18:30:46 by wlanette          #+#    #+#              #
#    Updated: 2022/10/27 15:45:42 by wmiyu            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang
CC_FLAGS = -Wall -Werror -Wextra -fsanitize=address -g
INCLUDE_FLAGS = -I./includes/ -I $(LIBFT_PATH)
L_FLAGS = -lreadline
#READLINE = -L /Users/$(USER)/.brew/opt/readline/lib
#READLINE_INC = -I /Users/$(USER)/.brew/opt/readline/include
READLINE = -L/opt/homebrew/opt/readline/lib
READLINE_INC = -I/opt/homebrew/opt/readline/include

RM = rm -f

# EXECUTABLE
NAME = ./minishell
LIBFT_NAME = $(LIBFT_PATH)libft.a

# PATHS
SRC_PATH = ./srcs/
OBJ_PATH = ./obj/
LIBFT_PATH = ./includes/libft/

SRC =	$(SRC_PATH)main.c $(SRC_PATH)ft_init.c $(SRC_PATH)lexer/ft_lexer.c $(SRC_PATH)signals/signals.c\
		$(SRC_PATH)utils/ft_print_error.c $(SRC_PATH)lexer/ft_validators.c $(SRC_PATH)lexer/ft_lexer_utils.c\
		$(SRC_PATH)lexer/ft_init_tokens.c $(SRC_PATH)utils/ft_is_space.c $(SRC_PATH)utils/ft_free_tokens.c \
		$(SRC_PATH)env/ft_env.c $(SRC_PATH)parser/ft_count_cmds.c $(SRC_PATH)parser/ft_init_cmds.c \
		$(SRC_PATH)parser/ft_parser.c $(SRC_PATH)parser/ft_treatment.c $(SRC_PATH)env/ft_env_list.c \
		$(SRC_PATH)env/ft_env_set.c $(SRC_PATH)lexer/ft_validators_2.c $(SRC_PATH)parser/ft_parser_validators.c\
		$(SRC_PATH)parser/ft_parser_utils.c $(SRC_PATH)utils/ft_free_in_loop.c $(SRC_PATH)parser/ft_cmd_rebuild.c\
		$(SRC_PATH)executer/ft_builtins.c $(SRC_PATH)parser/ft_parser_additional.c \
		$(SRC_PATH)executer/ft_execute.c $(SRC_PATH)executer/ft_joiner.c \
		$(SRC_PATH)executer/ft_file_redir.c $(SRC_PATH)executer/ft_split.c $(SRC_PATH)executer/ft_strjoin.c \
		$(SRC_PATH)executer/ft_make_cmd.c $(SRC_PATH)executer/ft_cd.c $(SRC_PATH)executer/ft_pwd.c \
		$(SRC_PATH)executer/ft_echo.c $(SRC_PATH)executer/ft_built_env.c \
		$(SRC_PATH)executer/ft_make_env.c $(SRC_PATH)executer/ft_exec_semi.c  \
		$(SRC_PATH)executer/ft_here_doc.c $(SRC_PATH)executer/ft_gnl.c
				
#OBJ = $(SRCS:.c=.o)
OBJ = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRC))

LIBFT_SRC = $(LIBFT_PATH)*.c

# COLORS
Y = "\033[33m"
R = "\033[31m"
G = "\033[32m"
B = "\033[34m"
X = "\033[0m"
UP = "\033[A"
CUT = "\033[K"

all: $(NAME)

# @$(CC) $(CC_FLAGS) $(INCLUDE_FLAGS) $(L_FLAGS) $(LIBFT_NAME) $(OBJ) -o $(NAME)
$(NAME): $(OBJ) $(LIBFT_NAME)
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@$(CC) $(OBJ) $(READLINE) $(READLINE_INC) $(CC_FLAGS) $(LIBFT_PATH)libft.a $(L_FLAGS) -o $(NAME)
	@echo $(G)Finished [$(NAME)]$(X)
	
$(LIBFT_NAME): $(LIBFT_SRC)
	@echo $(Y)Compiling [$(LIBFT_NAME)]...$(X)
	@make -C $(LIBFT_PATH) bonus

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@echo $(Y)Compiling [$@]...$(X)
	@mkdir -p $(dir $@)
	@$(CC) $(CC_FLAGS) $(INCLUDE_FLAGS) $(READLINE_INC) -o $@ -c $<
	@printf $(UP)$(CUT)
	@echo $(G)Finished [$@]$(X)
	@printf $(UP)$(CUT)

clean:
	@make -C $(LIBFT_PATH) clean
	@if [ -d "$(OBJ_PATH)" ]; then \
		$(RM) -r $(OBJ_PATH); \
		echo $(R)Cleaning" "[$(OBJ_PATH)]...$(X); \
	fi;

fclean: clean
	@make -C $(LIBFT_PATH) fclean
	@if [ -f "$(NAME)" ]; then \
		$(RM) $(NAME); \
		echo $(R)Cleaning" "[$(NAME)]...$(X); \
	fi;

re: fclean all

# TESTING RULES
norm:
	@echo $(G)Checking Norminette...$(X)
	norminette | grep Error | egrep --color '.*Error!|$$'
	@echo $(G)Done$(X)

run: all
	$(NAME)

.PHONY: all, clean, fclean, re, norm
