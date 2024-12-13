# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpires <kpires@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 19:41:59 by redrouic          #+#    #+#              #
#    Updated: 2024/12/13 16:06:40 by kpires           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	src/main.c\
			src/str2arr.c\
			src/gest_env.c\
			src/list.c\
			src/executer.c\
			src/expander.c\
			src/redir.c\
			src/signal.c\
			src/env.c

SLiB	=	lib/ft_strcmp.c\
			lib/ft_strlen.c\
			lib/ft_strncpy.c\
			lib/ft_strdup.c\
			lib/ft_concat.c\
			lib/ft_free.c

OBJ		=	$(SRC:.c=.o)

LOBJ	=	$(SLiB:.c=.o)

CC		=	cc

BIN		=	minishell

NAME	=	libft.a

RL		=	-lreadline

RM		=	rm -rf

CFLAGS	+=	-Wall -Wextra -Werror -g3

all: $(NAME) $(BIN)
	
$(NAME): $(LOBJ)
	ar rc $(NAME) $(LOBJ)
 
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(NAME) -o $(BIN) $(RL)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) $(LOBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(BIN)

re: fclean all

.PHONY: all clean fclean re
