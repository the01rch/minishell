# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpires <kpires@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/07 11:28:33 by kpires            #+#    #+#              #
#    Updated: 2024/11/26 09:33:14 by kpires           ###   ########.fr        #
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
HEADER = get_next_line.h
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
BIN = get_next_line.a
NAME = $(BIN_DIR)/$(BIN)

SRC =	get_next_line.c\
		get_next_line_utils.c


OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Progress vars
SRC_COUNT_TOT := $(shell expr $(shell echo -n $(SRC) | wc -w) - $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_COUNT_TOT) -lt 0; echo $$?),0)
	SRC_COUNT_TOT := $(shell echo -n $(SRC) | wc -w)
endif
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))
SRC_LIST_COUNT_TOT := $(shell expr $(shell echo -n $(SRC_LIST) | wc -w))
ifeq ($(shell test $(SRC_LIST_COUNT_TOT) -lt 0; echo $$?),0)
	SRC_LIST_COUNT_TOT := $(shell echo -n $(SRC_LIST) | wc -w)
endif
SRC_LIST_COUNT := 0
SRC_LIST_PCT = $(shell expr 100 \* $(SRC_LIST_COUNT) / $(SRC_LIST_COUNT_TOT))
SRC_CUSTOM_COUNT_TOT := $(shell expr $(shell echo -n $(SRC_CUSTOM) | wc -w))
ifeq ($(shell test $(SRC_CUSTOM_COUNT_TOT) -lt 0; echo $$?),0)
	SRC_CUSTOM_COUNT_TOT := $(shell echo -n $(SRC_CUSTOM) | wc -w)
endif
SRC_CUSTOM_COUNT := 0
SRC_CUSTOM_PCT = $(shell expr 100 \* $(SRC_CUSTOM_COUNT) / $(SRC_CUSTOM_COUNT_TOT))

all: $(NAME)

$(NAME): $(OBJ) | $(BIN_DIR)
	@$(AR) $(NAME) $^
	@$(PRINTF) "\r%100s\r$(BIN) is up to date!\n"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $<..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@$(PRINTF) "Cleaning up object files in Get next line...\n"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) -r $(BIN_DIR)
	@$(PRINTF) "Removed $(NAME)\n"

create_dirs:

norminette:
	@$(PRINTF) "\nChecking norm for Get next line...\n"
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR) inc/get_next_line.h

re: fclean
	@make all

git:
	git add .
	git commit
	git push

-include $(OBJ_DIR)/*.d

.PHONY: all clean fclean git norminette re