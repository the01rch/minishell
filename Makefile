# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpires <kpires@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/04 19:41:59 by redrouic          #+#    #+#              #
#    Updated: 2025/01/11 17:02:16 by redrouic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=	src/main.c\
			src/utils.c\
			src/free.c\
			src/fill_struct.c\
			src/parsing/str2arr.c\
			src/parsing/env2list.c\
			src/parsing/gest_err.c\
			src/parsing/expander.c\
			src/redir/out_in.c\
			src/redir/ft_redir.c\
			src/redir/ft_heredoc.c\
			src/redir/redir_utils.c\
			src/builtins/ft_export.c\
			src/builtins/ft_unset.c\
			src/builtins/ft_cd.c\
			src/builtins/builtins.c\
			src/executor/executor.c\
			src/executor/ft_exec.c\
			src/executor/ft_one.c\
			src/executor/ft_pipes.c\

SLiB	=	lib/ft_strcmp.c\
			lib/ft_strlen.c\
			lib/ft_strncpy.c\
			lib/ft_strncmp.c\
			lib/ft_strdup.c\
			lib/ft_strlcat.c\
			lib/ft_memcpy.c\
			lib/ft_isalnum.c\
			lib/ft_calloc.c\
			lib/ft_strlcpy.c\
			lib/ft_isdigit.c\
			lib/ft_atoi.c\
			lib/ft_itoa.c\
			lib/ft_is_nb.c\
			lib/ft_perror.c\
			lib/ft_substr.c\

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
