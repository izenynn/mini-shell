/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:01:34 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/02 18:56:42 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*** INFO ***/

/*
 * Grammar
 *
 * <command line>		:	<job> ';' <command line>
 * 						|	<job> ';'
 * 						|	<job>
 * 						;
 *
 * <job>				:	<command> '|' <job>
 * 						|	<command>
 * 						;
 *
 * <command>			:	<name> <token list>
 * 						;
 *
 * <token list>			:	<token> <token list>
 * 						;
 *
 */

/*
 * Create an ast recursively:
 *
 * cmd_line()		=>	test all command line in order
 * cmd_line_1()		=>	<job> ';' <command line>
 * cmd_line_2()		=>	<job> ';'
 * cmd_line_3()		=>	<job>
 *
 * job()			=>	test all job in order
 * job_1()			=>	<command> '|' <job>
 * job_2()			=>	<command>
 *
 * cmd()			=>	test all command in order
 * cmd_1()			=>	<redir in> <simple command> <redir out>
 * cmd_2()			=>	<redir out> <simple command> <redir in>
 * cmd_3()			=>	<simple command> <redir>
 * cmd_4()			=>	<redir> <simple command>
 * cmd_5()			=>	<simple command>
 *
 * redir()			=>	test all redirections in order
 * redir_1()		=>	<redir in> <redir out>
 * redir_2()		=>	<redir in> <redir out>
 * redir_3()		=>	<redir in>
 * redir_4()		=>	<redir out>
 *
 * redir_in()		=>	test all in redirections in order
 * redir_in_1()		=>	'<<' <file>
 * redir_in_2()		=>	'<' <file>
 *
 * redir_out()		=>	test all out redirections in order
 * redir_out_1()	=>	'>>' <file>
 * redir_out_2()	=>	'>' <file>
 *
 * simple_cmd()		=>	test simple cmd
 * simple_cmd_1()	=>	<name> <token list>
 *
 * tok_lst()		=>	test token list
 * tok_lst_1()		=>	<token> <token list>
 * tok_lst_2()		=>	<token> <token list>
 * tok_lst_3()		=>	<token> <token list>
 * tok_lst_4()		=>	(null)
 *
 */

/*** INCLUDES ***/

# include <sh/lexer.h>
# include <sh/ast.h>

/*** PROTOTYPES ***/

/* parse.c */
int		parse(t_lexer *lex, t_ast **ast);

/* parser_utils.c */
int		is_term(int type, char **buff);

/* parse_cmd_line.c */
t_ast	*cmd_line(void);
t_ast	*cmd_line_1(void);
t_ast	*cmd_line_2(void);
t_ast	*cmd_line_3(void);

/* parse_job.c */
t_ast	*job(void);
t_ast	*job_1(void);
t_ast	*job_2(void);

/* parse_cmd_1.c */
t_ast	*cmd(void);
t_ast	*cmd_1(void);
t_ast	*cmd_2(void);

/* parse_cmd_2.c */
t_ast	*cmd_3(void);
t_ast	*cmd_4(void);
t_ast	*cmd_5(void);

/* parse_redir.c */
t_ast	*redir(void);
t_ast	*redir_1(void);
t_ast	*redir_2(void);

/* parse_redir_in.c */
t_ast	*redir_in(void);
t_ast	*redir_in_1(void);
t_ast	*redir_in_2(void);

/* parse_redir_out.c */
t_ast	*redir_out(void);
t_ast	*redir_out_1(void);
t_ast	*redir_out_2(void);

/* parse_simple_cmd.c */
t_ast	*simple_cmd(void);
t_ast	*simple_cmd_1(void);

/* parse_tok_lst.c */
t_ast	*tok_lst(void);
t_ast	*tok_lst_1(void);
t_ast	*tok_lst_2(void);
t_ast	*tok_lst_3(void);

#endif
