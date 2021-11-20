/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:43:21 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 14:10:57 by dpoveda-         ###   ########.fr       */
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

/* lexer.c */
int		lexer_build(char *line, size_t len, t_lexer *lex);

/* lexer_utils.c */
void	lexer_del(t_lexer *lex);
int		get_ctype(char c);
void	trim_quotes(char *dst, char *src);

/* token_utils.c */
void	tok_del(t_tok *tok);
void	tok_init(t_tok *tok, size_t sz);

#endif
