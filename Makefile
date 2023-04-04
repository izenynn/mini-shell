# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/20 13:15:01 by dpoveda-          #+#    #+#              #
#   Updated: 2021/12/16 21:34:38 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                     VARS                                     #
# **************************************************************************** #

# COLORS
NOCOL=\033[0m
RED=\033[31m
GRN=\033[32m
YEL=\033[33m
BLU=\033[34m
MAG=\033[35m
CYN=\033[36m

# OS
UNAME_S := $(shell uname -s)

# **************************************************************************** #
#                                   PROGRAM                                    #
# **************************************************************************** #

NAME = minishell
#NAME = msh

BIN_DIR ?= /usr/local/bin

# **************************************************************************** #
#                                   COMPILER                                   #
# **************************************************************************** #

MAKE = make

CC = gcc

CFLAGS += -Wall -Wextra -Werror

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

SRC_DIR_MAIN	= main
SRC_DIR_BUILTIN	= built-in
SRC_DIR_EXEC	= exec
SRC_DIR_LEXER	= lexer
SRC_DIR_PARSER	= parser
SRC_DIR_PROMPT	= prompt
SRC_DIR_UTILS	= utils

OBJ_DIRS_NAME =	$(SRC_DIR_MAIN)		$(SRC_DIR_BUILTIN)	$(SRC_DIR_EXEC)		\
				$(SRC_DIR_LEXER)	$(SRC_DIR_PARSER)	$(SRC_DIR_PROMPT)	\
				$(SRC_DIR_UTILS)

OBJ_DIRS = $(addprefix $(OBJ_PATH)/, $(OBJ_DIRS_NAME))

SRC_ROOT =		main.c

SRC_MAIN = 		handle_line.c

SRC_BUILTIN =	cd.c				echo.c				env.c				\
				exit.c				export.c			pwd.c				\
				unset.c				cd_error.c			export_utils.c		\
				cd_utils.c			unset_utils.c

SRC_EXEC =		exec.c				exec_ast.c			exec_cmd.c			\
				utils.c				exec_heredoc.c		heredoc.c			\
				handle_zombies.c	redir.c				redir_types.c		\
				path.c

SRC_LEXER =		lexer.c				utils_1.c			utils_2.c			\
				pc_gen_st.c			pc_other_st.c		process_tokens.c	\
				token_utils.c		handle_expand.c		expand.c			\
				wildcards.c			wc_match.c			wc_match_frag.c		\
				wc_utils.c			wc_check.c

SRC_PARSER =	parser.c			parser_utils.c		ast_utils_1.c		\
				ast_utils_2.c		parse_cmd_line.c	parse_and_or_1.c	\
				parse_and_or_2.c	parse_job.c			parse_cmd.c			\
				parse_tok_lst.c		parse_redir.c		parse_redir_in.c	\
				parse_redir_out.c

SRC_PROMPT =	prompt.c

SRC_UTILS =		init.c				error_utils.c		signals.c			\
				custom_len.c		ft_getenv.c			env_utils.c			\
				init_utils.c		read_config.c		new_tmp.c

SRC_NAME =	$(SRC_ROOT)														\
			$(addprefix $(SRC_DIR_MAIN)/, $(SRC_MAIN))						\
			$(addprefix $(SRC_DIR_BUILTIN)/, $(SRC_BUILTIN))				\
			$(addprefix $(SRC_DIR_EXEC)/, $(SRC_EXEC))						\
			$(addprefix $(SRC_DIR_LEXER)/, $(SRC_LEXER))					\
			$(addprefix $(SRC_DIR_PARSER)/, $(SRC_PARSER))					\
			$(addprefix $(SRC_DIR_PROMPT)/, $(SRC_PROMPT))					\
			$(addprefix $(SRC_DIR_UTILS)/, $(SRC_UTILS))

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
$(NAME): $(OBJ) $(LFT_NAME)
	@printf "\n${YEL}LINKING:${NOCOL}\n"
	@printf "${BLU}"
	$(CC) $(CFLAGS) $(OBJ) $(LFT_NAME) -o $@ $(LDFLAGS) $(LDLIBS) $(CCFLAGS)
	@printf "${NOCOL}"
	@printf "\n${GRN}SUCCESS!${NOCOL}\n"
	@printf "${CYN}type \"./$(NAME)\" to start!${NOCOL}\n"

# INSTALL
install: $(NAME)
	install $(NAME) $(BIN_DIR)

# SANITIZE ADDRESS
ifeq ($(UNAME_S),Linux)
sanitize: CFLAGS += -pedantic -g3 -fsanitize=address -fsanitize=leak -fsanitize=undefined -fsanitize=bounds -fsanitize=null
endif
ifeq ($(UNAME_S),Darwin)
sanitize: CFLAGS += -pedantic -g3 -fsanitize=address
endif
sanitize: $(NAME)

# SANITIZE THREAD
thread: CFLAGS += -g3 -fsanitize=thread
thread: $(NAME)

# LIBFT
$(LFT_NAME): $(LFT)
	@printf "${MAG}"
	cp $(LFT) $(LFT_NAME)
	@printf "${NOCOL}"
$(LFT):
	@printf "\n${YEL}LIBFT:${NOCOL}\n"
	@printf "${MAG}"
	$(MAKE) all -sC $(LFT_DIR)
	@printf "${NOCOL}"

# OBJ
$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_DIRS)
	@printf "${BLU}"
	$(CC) $(CFLAGS) -c $< -o $@
	@printf "${NOCOL}"

# OBJ DIRS
$(OBJ_DIRS): | $(OBJ_PATH)
	@printf "${MAG}"
	mkdir -p $(OBJ_DIRS)
	@printf "${NOCOL}"
$(OBJ_PATH):
	@printf "${MAG}"
	mkdir -p $(OBJ_PATH)
	@printf "${NOCOL}"

# CLEAN
clean:
	@printf "${RED}"
	$(MAKE) clean -sC $(LFT_DIR)
	rm -rf $(LFT_NAME)
	rm -rf $(OBJ_PATH)
	@printf "${NOCOL}"

# FULL CLEAN
fclean: clean
	@printf "${RED}"
	$(MAKE) fclean -sC $(LFT_DIR)
	rm -rf $(NAME)
	@printf "${NOCOL}"

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
