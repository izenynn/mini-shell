# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 21:43:51 by dpoveda-          #+#    #+#              #
#    Updated: 2021/11/10 09:54:04 by dpoveda-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                     VARS                                     #
# **************************************************************************** #

# COLORS
NOCOL=\033[0m
RED=\033[1;31m
YEL=\033[1;33m
ORG=\033[0;33m
GRN=\033[1;32m
DGRAY=\033[1;30m
BLU=\033[1;34m

# OS
UNAME_S := $(shell uname -s)

# **************************************************************************** #
#                                   PROGRAM                                    #
# **************************************************************************** #

NAME = minishell

# **************************************************************************** #
#                                   COMPILER                                   #
# **************************************************************************** #

MAKE = make

CC = gcc

CFLAGS += -Wall -Wextra -Werror

#CCFLAGS += -pthread

# **************************************************************************** #
#                                    PATHS                                     #
# **************************************************************************** #

SRC_PATH = src
OBJ_PATH = obj
INC_PATH = inc

# **************************************************************************** #
#                                    FLAGS                                     #
# **************************************************************************** #

CFLAGS += -I ./$(INC_PATH)

# **************************************************************************** #
#                                   SOURCES                                    #
# **************************************************************************** #

SRC_FILES =	main.c		sh_loop.c

SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))

OBJ_FILES = $(SRC_FILES:%.c=%.o)

OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_FILES))

# **************************************************************************** #
#                                     LIBS                                     #
# **************************************************************************** #

LFT_NAME = libft.a
LFT_DIR = libft
LFT = $(LFT_DIR)/$(LFT_NAME)

CFLAGS += -I ./$(LFT_DIR)/$(INC_PATH)

LDFLAGS = -L ./$(LFT_DIR)

LDLIBS = -lft

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

.PHONY: all sanitize thread clean fclean re norme

# all
all: $(NAME)

# name
$(NAME): $(LFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS) $(CCFLAGS)

# sanitize
ifeq ($(UNAME_S),Linux)
sanitize: CFLAGS += -pedantic -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -g3
endif
ifeq ($(UNAME_S),Darwin)
sanitize: CFLAGS += -pedantic -fsanitize=address -g3
endif
sanitize: $(NAME)

# thread
thread: CFLAGS += -fsanitize=thread -g3
thread: $(NAME)

# libft
$(LFT_NAME): $(LFT)
	cp $(LFT) $(LFT_NAME)
$(LFT):
	$(MAKE) all -sC $(LFT_DIR)

# obj
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

# obj path
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH) 2> /dev/null

# clean
clean:
	$(MAKE) clean -sC $(LFT_DIR)
	rm -rf $(LFT_NAME)
	rm -rf $(OBJ_PATH)

# fclean
fclean: clean
	$(MAKE) fclean -sC $(LFT_DIR)
	rm -rf $(NAME)

# re
re: fclean all

# norminette
norme:
	@printf "\n${GRN}##########${YEL} NORMINETTE ${GRN}##########${NOCOL}\n"
	@printf "\n${GRN}LIBFT:${BLU}\n\n"
	@norminette $(LFT_DIR)
	@printf "\n${GRN}MINISHELL:${BLU}\n\n"
	@norminette $(INC_PATH)
	@norminette $(SRC_PATH)
	@printf "${NOCOL}"

