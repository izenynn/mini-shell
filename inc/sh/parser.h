/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:01:34 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/19 12:05:48 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*** INCLUDES ***/

# include <sh/lexer.h>
# include <sh/ast.h>

/*** PROTOTYPES ***/

/* parse.c */
int		parse(t_lexer *lex, t_ast *ast);

/* parser_utils.c */
int		is_term(int type, char **buff);

/* parse_cmd_line_1.c */
t_ast	*cmd_line(void);
t_ast	*cmd_line_1(void);
t_ast	*cmd_line_2(void);
t_ast	*cmd_line_3(void);
t_ast	*cmd_line_4(void);
t_ast	*cmd_line_5(void);

/* parse_cmd_line_2.c */

/* parse_job.c */
t_ast	*job(void);
t_ast	*job_1(void);
t_ast	*job_2(void);

/* parse_cmd.c */
t_ast	*cmd(void);
t_ast	*cmd_1(void);
t_ast	*cmd_2(void);
t_ast	*cmd_3(void);

/* parse_simple_cmd.c */
t_ast	*simple_cmd(void);
t_ast	*simple_cmd_1(void);

/* parse_tok_lst.c */
t_ast	*tok_lst(void);
t_ast	*tok_lst_1(void);
t_ast	*tok_lst_2(void);

#endif
