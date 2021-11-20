/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:43:21 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 12:06:58 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*** include ***/

# include <stddef.h>

/*** DATA ***/

typedef struct s_io		t_io;
typedef struct s_tok	t_tok;
typedef struct s_lexer	t_lexer;

/* token types ("GEN" stands for "general") */
enum e_tok_type {
	CHAR_GEN = -1,
	CHAR_PIPE = '|',
	CHAR_AMP = '&',
	CHAR_QOUTE = '\'',
	CHAR_DQOUTE = '\"',
	CHAR_SC = ';',
	CHAR_WS = ' ',
	CHAR_ESCSEQ = '\\',
	CHAR_TAB = '\t',
	CHAR_NL = '\n',
	CHAR_GT = '>',
	CHAR_LS = '<',
	CHAR_NULL = '\0',
	TOK = -1,
};

/* states */
enum {
	ST_IN_QUOTE = 0,
	ST_IN_DQUOTE,
	ST_IN_ESC,
	ST_GEN,
};

/*struct s_io {
	int	fd_stdin;
	int	fd_stdout;
	int	fd_stderr;
};

struct s_tok {
	char	*cmd;
	char	**args;
	t_io	io;
	t_tok	*next;
};*/

struct s_tok {
	char	*data;
	int		type;
	t_tok	*next;
};

struct s_lexer {
	t_tok	*tok_lst;
	int		n_toks;
};

/*** PROTOTYPES ***/

/* lexer/lexer.c */
int	lexer_build(char *line, size_t len, t_lexer *lex);

#endif
