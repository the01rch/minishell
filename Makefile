# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpires <kpires@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 19:41:59 by redrouic          #+#    #+#              #
#    Updated: 2024/11/25 16:34:06 by kpires           ###   ########.fr        #
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
			src/get_next_line.c\
			src/get_next_line_utils.c\
			src/parsing.c
CC		=	cc

OBJ		=	$(SRC:.c=.o)

NAME	=	minishell

RL = -lreadline

RM		=	rm -rf

CFLAGS	+=	-Wall -Wextra -Werror -g3

LIBFT = libft/bin/libft.a
LIBFT_DIR = libft
LIBFT_SRC = $(shell [ -d libft ] && ls libft/src*/*.c)


all: $(NAME)
	
$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) $(RL)
 
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


$(LIBFT): $(LIBFT_SRC) | $(LIBFT_DIR)
	@make all -C libft
	@$(AR) $(NAME) $(LIBFT)

clean: | $(LIBFT_DIR)
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
