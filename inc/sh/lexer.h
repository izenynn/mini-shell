/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:43:21 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/18 13:27:09 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*** include ***/

# include <stddef.h>
# include <dirent.h>

/*** DATA ***/

typedef struct s_io		t_io;
typedef struct s_tok	t_tok;
typedef struct s_lexer	t_lexer;

/* token types ("GEN" stands for "general") */
enum e_tok_type {
	CHAR_GEN	= -1,
	CHAR_PIPE	= '|',
	CHAR_AMP	= '&',
	CHAR_QOUTE	= '\'',
	CHAR_DQOUTE	= '\"',
	CHAR_SC		= ';',
	CHAR_WS		= ' ',
	CHAR_ESCSEQ	= '\\',
	CHAR_TAB	= '\t',
	CHAR_NL		= '\n',
	CHAR_GT		= '>',
	CHAR_LS		= '<',
	CHAR_DL		= '$',
	CHAR_NULL	= '\0',
	CHAR_QUEST	= '?',
	CHAR_OPR	= '(',
	CHAR_CPR	= ')',
	CHAR_OCL	= '{',
	CHAR_CCL	= '}',
	TOK			= -1
};

/* states */
enum {
	ST_IN_QUOTE = 0,
	ST_IN_DQUOTE,
	ST_IN_ESC,
	ST_IN_CURLY,
	ST_GEN
};

/* token */
struct s_tok {
	char	*data;
	int		type;
	t_tok	*next;
};

/* lexer struct */
struct s_lexer {
	t_tok	*tok_lst;
	int		n_toks;
};

/* lexer support struct */
typedef struct s_lexsup {
	t_tok	*tok;
	char	c;
	int		type;
	int		st;
	int		i;
	int		j;
}	t_lexsup;

/* parse tokens support struct */
typedef struct s_toksup {
	int		cnt;
	int		semaphore;
	int		is_heredoc;
	t_tok	*prev;
	t_tok	*aux;
}	t_toksup;

/* expand support struct */
typedef struct s_expsup {
	int		start;
	int		end;
	int		curly;
	char	*name;
	char	*value;
}	t_expsup;

/* wildcards support struct */
typedef struct s_wcsup {
	const char	*stgt;
	const char	*swc;
	const char	*tgt_end;
	int			ret;
	int			st;
}	t_wcsup;

/*** PROTOTYPES ***/

/* lexer.c */
int		lexer_build(const char *line, const size_t len, t_lexer *lex);

/* pc_gen_st.c */
int		handle_gen_st(t_lexsup *ls, const char *line, const size_t sz);

/* pc_other_st.c */
void	handle_other_st(t_lexsup *ls);

/* process_tokens.c */
int		process_tokens(t_lexer *lex);

/* utils_1.c */
void	lexer_del(t_lexer *lex);
int		get_ctype(char c);
void	trim_quotes(char *dst, char *src);
int		init_ls(t_lexsup *ls, t_lexer *lex, const size_t sz);

/* utils_2.c */
void	rejoin_tokens(t_tok **tok, t_tok **prev, t_lexer *lex, t_tok *head);
void	insert_toklst(t_tok **tok, t_tok **prev, t_lexer *lex, t_tok *head);

/* token_utils.c */
void	del_node(t_tok **tok, t_tok *prev);
void	tok_del(t_tok *tok);
int		tok_init(t_tok *tok, size_t sz);

/* handle_expand.c */
int		handle_expand(t_tok **tok, t_tok **prev, t_lexer *lex, t_toksup *ts);

/* expand.c */
int		expand(t_tok *tok, int *start, int st);

/* wildcards.c */
int		handle_wildcards(t_tok **wc_tok, t_tok **prev, t_lexer *lex);

/* wc_check.c */
int		wc_check(t_tok *tok);

/* wc_match.c */
int		wc_match(const char *wildcard, const char *target);

/* wc_match_frag.c */
int		wc_match_fragment(const char **frag, const char **tgt,
			const char *tgt_end, int *st);

/* wc_utils.c */
void	sort_list(t_tok **head);
void	read_dir(t_tok **head, DIR *ls, struct dirent *list);
void	wc_put_error(t_tok *const *tok, t_tok *head);

#endif
