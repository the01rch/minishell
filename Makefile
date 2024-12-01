# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpires <kpires@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 19:41:59 by redrouic          #+#    #+#              #
#    Updated: 2024/11/29 14:52:34 by kpires           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	src/main.c\
			src/utils.c\
			src/str2arr.c\
			src/gest_env.c\
			src/list.c\
			src/exec.c\
			src/signals.c\
			src/error.c\
			src/env.c\
			src/prompt.c\
			src/custom_cmd.c\
			src/parsing.c\
			src/builtins.c\
			src/ft_split_quotes.c
CC		=	cc

OBJ_DIR = obj
OBJ		=	$(SRC:src/%.c=$(OBJ_DIR)/%.o)

NAME	=	minishell

RL = -lreadline

RM		=	rm -rf

CFLAGS	+=	-Wall -Wextra -Werror -g3

LIBFT = libft/bin/libft.a
LIBFT_DIR = libft
LIBFT_SRC = $(shell [ -d libft ] && ls libft/src*/*.c)

GNL = get_next_line/bin/get_next_line.a
GNL_DIR = get_next_line
GNL_SRC = $(shell [ -d get_next_line ] && ls get_next_line/src*/*.c)

all: $(OBJ_DIR) $(NAME)
	
$(NAME): $(LIBFT) $(GNL) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(GNL) -o $(NAME) $(RL)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(GNL): $(GNL_SRC) | $(GNL_DIR)
	@make all -C get_next_line
	@$(AR) $(NAME) $(GNL)

$(LIBFT): $(LIBFT_SRC) | $(LIBFT_DIR)
	@make all -C libft
	@$(AR) $(NAME) $(LIBFT)
	
clean: | $(LIBFT_DIR)
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re