# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/09 21:43:51 by dpoveda-          #+#    #+#              #
#    Updated: 2021/11/12 10:33:19 by dpoveda-         ###   ########.fr        #
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

SRC_DIR_BUILTIN = built-in
SRC_DIR_EXEC = exec
SRC_DIR_LEXER = lexer
SRC_DIR_PARSER = parser
SRC_DIR_PROMPT = prompt

OBJ_DIRS_NAME =	$(SRC_DIR_BUILTIN)	$(SRC_DIR_EXEC)		$(SRC_DIR_LEXER)	\
				$(SRC_DIR_PARSER)	$(SRC_DIR_PROMPT)

OBJ_DIRS = $(addprefix $(OBJ_PATH)/, $(OBJ_DIRS_NAME))

SRC_MAIN =	main.c

SRC_BUILTIN =

SRC_EXEC =

SRC_LEXER =

SRC_PARSER =

SRC_PROMPT = terminal.c		terminal_utils.c

SRC_NAME =	$(SRC_MAIN)												\
			$(addprefix $(SRC_DIR_BUILTIN)/, $(SRC_BUILTIN))		\
			$(addprefix $(SRC_DIR_EXEC)/, $(SRC_EXEC))				\
			$(addprefix $(SRC_DIR_LEXER)/, $(SRC_LEXER))			\
			$(addprefix $(SRC_DIR_PARSER)/, $(SRC_PARSER))			\
			$(addprefix $(SRC_DIR_PROMPT)/, $(SRC_PROMPT))

OBJ_NAME = $(SRC_NAME:%.c=%.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/, $(OBJ_NAME))

# **************************************************************************** #
#                                     LIBS                                     #
# **************************************************************************** #

LFT_NAME = libft.a
LFT_DIR = libft
LFT = $(LFT_DIR)/$(LFT_NAME)

CFLAGS += -I ./$(LFT_DIR)/$(INC_PATH)

LDFLAGS = -L ./$(LFT_DIR)

LDLIBS = -lft

LDLIBS += -lreadline

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

.PHONY: all sanitize thread clean fclean re norme

# ALL
all: $(NAME)

# NAME
$(NAME): $(LFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS) $(CCFLAGS)

# SANITIZE ADDRESS
ifeq ($(UNAME_S),Linux)
sanitize: CFLAGS += -pedantic -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null -g3
endif
ifeq ($(UNAME_S),Darwin)
sanitize: CFLAGS += -pedantic -fsanitize=address -g3
endif
sanitize: $(NAME)

# SANITIZE THREAD
thread: CFLAGS += -fsanitize=thread -g3
thread: $(NAME)

# LIBFT
$(LFT_NAME): $(LFT)
	cp $(LFT) $(LFT_NAME)
$(LFT):
	$(MAKE) all -sC $(LFT_DIR)

# OBJ
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_DIRS)
	$(CC) $(CFLAGS) -c $< -o $@

# OBJ DIRS
$(OBJ_DIRS): | $(OBJ_PATH)
	mkdir -p $(OBJ_DIRS)
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

# CLEAN
clean:
	$(MAKE) clean -sC $(LFT_DIR)
	rm -rf $(LFT_NAME)
	rm -rf $(OBJ_PATH)

# FULL CLEAN
fclean: clean
	$(MAKE) fclean -sC $(LFT_DIR)
	rm -rf $(NAME)

# RE
re: fclean all

# NORMINETTE
norme:
	@printf "\n${GRN}##########${YEL} NORMINETTE ${GRN}##########${NOCOL}\n"
	@printf "\n${GRN}LIBFT:${BLU}\n\n"
	@norminette $(LFT_DIR)
	@printf "\n${GRN}MINISHELL:${BLU}\n\n"
	@norminette $(INC_PATH)
	@norminette $(SRC_PATH)
	@printf "${NOCOL}"
