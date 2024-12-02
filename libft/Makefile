# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpires <kpires@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/07 11:28:33 by kpires            #+#    #+#              #
#    Updated: 2024/12/02 10:10:22 by kpires           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL=/bin/bash
UNAME = $(shell uname -s)
PRINTF = echo
ifeq ($(UNAME), Linux)
	PRINTF = echo -e
endif

PRINTF = printf
CC = gcc -MD
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
HEADER = libft.h
SRC_DIR = src
SRC_LIST_DIR = src_list_dir
SRC_CUSTOM_DIR = src_custom_dir
OBJ_DIR = obj
OBJ_LIST_DIR = obj_list_dir
OBJ_CUSTOM_DIR = obj_custom_dir
BIN_DIR = bin
BIN = libft.a
NAME = $(BIN_DIR)/$(BIN)

SRC =	ft_atoi.c ft_bzero.c	\
	ft_calloc.c ft_putendl_fd.c		\
	ft_itoa.c ft_putchar_fd.c		\
	ft_putstr_fd.c ft_memccpy.c		\
	ft_memchr.c ft_memcmp.c			\
	ft_memcpy.c ft_isalnum.c		\
	ft_isalpha.c ft_isascii.c		\
	ft_isdigit.c ft_isprint.c		\
	ft_memmove.c ft_memset.c		\
	ft_split.c ft_strchr.c			\
	ft_strdup.c ft_strjoin.c		\
	ft_strlcat.c ft_strlcpy.c		\
	ft_strlen.c ft_strmapi.c		\
	ft_strncmp.c ft_strnstr.c		\
	ft_strrchr.c ft_strtrim.c		\
	ft_substr.c ft_tolower.c		\
	ft_toupper.c ft_putnbr_fd.c

SRC_LIST = ft_lstadd_back.c	\
	ft_lstadd_front.c	\
	ft_lstclear.c		\
	ft_lstdelone.c		\
	ft_lstiter.c		\
	ft_lstlast.c		\
	ft_lstsize.c		\
	ft_lstnew.c			\
	ft_lstmap.c			\
	ft_lstget_at.c

SRC_CUSTOM = ft_putnbr_base_fd.c ft_putstrn_fd.c		\
	ft_putnchar_fd.c ft_isspace.c ft_uitoa.c	\
	ft_nbrlen.c ft_strrncmp.c ft_countchar.c	\
	ft_strenlarge.c ft_recursive_power.c		\
	ft_chartostr.c ft_sqrt.c ft_newvector.c		\
	ft_euclideandistance.c  ft_atoi2.c			\
	ft_free_matrix.c ft_dup_matrix.c			\
	ft_strchr_i.c ft_putmatrix_fd.c				\
	ft_matrixlen.c ft_strchars_i.c				\
	ft_between_chars.c ft_subsplit.c			\
	ft_extend_matrix.c ft_matrixtolst.c			\
	ft_lsttomatrix.c ft_matrix_replace_in.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_LIST = $(addprefix $(OBJ_LIST_DIR)/, $(SRC_LIST:.c=.o))

OBJ_CUSTOM = $(addprefix $(OBJ_CUSTOM_DIR)/, $(SRC_CUSTOM:.c=.o))

# Progress vars
SRC_COUNT_TOT := $(shell expr $(shell echo -n $(SRC) | wc -w) - $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_COUNT_TOT) -lt 0; echo $$?),0)
	SRC_COUNT_TOT := $(shell echo -n $(SRC) | wc -w)
endif
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))
SRC_LIST_COUNT_TOT := $(shell expr $(shell echo -n $(SRC_LIST) | wc -w) - $(shell ls -l $(OBJ_LIST_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_LIST_COUNT_TOT) -lt 0; echo $$?),0)
	SRC_LIST_COUNT_TOT := $(shell echo -n $(SRC_LIST) | wc -w)
endif
SRC_LIST_COUNT := 0
SRC_LIST_PCT = $(shell expr 100 \* $(SRC_LIST_COUNT) / $(SRC_LIST_COUNT_TOT))
SRC_CUSTOM_COUNT_TOT := $(shell expr $(shell echo -n $(SRC_CUSTOM) | wc -w) - $(shell ls -l $(OBJ_CUSTOM_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_CUSTOM_COUNT_TOT) -lt 0; echo $$?),0)
	SRC_CUSTOM_COUNT_TOT := $(shell echo -n $(SRC_CUSTOM) | wc -w)
endif
SRC_CUSTOM_COUNT := 0
SRC_CUSTOM_PCT = $(shell expr 100 \* $(SRC_CUSTOM_COUNT) / $(SRC_CUSTOM_COUNT_TOT))

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_LIST) $(OBJ_CUSTOM) | $(BIN_DIR)
	@$(AR) $(NAME) $^
	@$(PRINTF) "\r%100s\r$(BIN) is up to date!\n"

bonus: $(OBJ_LIST) | $(BIN_DIR)
	@$(AR) $(NAME) $^
	@$(PRINTF) "\r%100s\rBonus $(BIN) is up to date!\n"

additional: $(OBJ_CUSTOM) | $(BIN_DIR)
	@$(AR) $(NAME) $^
	@$(PRINTF) "\r%100s\rAdditional $(BIN) is up to date!\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $<..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_LIST_DIR)/%.o: $(SRC_LIST_DIR)/%.c | $(OBJ_LIST_DIR)
	@$(eval SRC_LIST_COUNT = $(shell expr $(SRC_LIST_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $<..." "" $(SRC_LIST_COUNT) $(SRC_LIST_COUNT_TOT) $(SRC_LIST_PCT)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_CUSTOM_DIR)/%.o: $(SRC_CUSTOM_DIR)/%.c | $(OBJ_CUSTOM_DIR)
	@$(eval SRC_CUSTOM_COUNT = $(shell expr $(SRC_CUSTOM_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $<..." "" $(SRC_CUSTOM_COUNT) $(SRC_CUSTOM_COUNT_TOT) $(SRC_CUSTOM_PCT)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_LIST_DIR):
	@mkdir -p $(OBJ_LIST_DIR)

$(OBJ_CUSTOM_DIR):
	@mkdir -p $(OBJ_CUSTOM_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@$(PRINTF) "Cleaning up object files in libft...\n"
	@$(RM) -r $(OBJ_DIR)
	@$(RM) -r $(OBJ_LIST_DIR)
	@$(RM) -r $(OBJ_CUSTOM_DIR)

fclean: clean
	@$(RM) -r $(BIN_DIR)
	@$(PRINTF) "Removed $(NAME)\n"

create_dirs:

norminette:
	@$(PRINTF) "\nChecking norm for libft...\n"
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR) $(SRC_LIST_DIR) $(SRC_CUSTOM_DIR) inc/libft.h

re: fclean
	@make all

git:
	git add .
	git commit
	git push

-include $(OBJ_DIR)/*.d
-include $(OBJ_LIST_DIR)/*.d
-include $(OBJ_CUSTOM_DIR)/*.d

.PHONY: all bonus additional clean fclean git norminette re