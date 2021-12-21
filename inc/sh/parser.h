/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:01:34 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/17 01:21:00 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*** INFO ***/

/*
 * Grammar
 *
 * <command line>		:	<and or> ';' <command line>
 * 						|	<and or> ';'
 * 						|	<and or>
 * 						;
 *
 * <and or>				:	<job> && <and or>
 * 						|	<job> || <and or>
 * 						|	<job>
 * 						|	'(' <command line> ')' && <and or>
 * 						|	'(' <command line> ')' || <and or>
 * 						|	'(' <command line> ')'
 * 						;
 *
 * <job>				:	'(' <command> ')' '|' <job>
 * 						|	    <command>     '|' <job>
 * 						|	'(' <command> ')'
 * 						|	    <command>
 * 						;
 *
 * <command>			:	<token list>
 * 						;
 *
 * <token list>			:	<name> <token list>
 * 						|	<token> <token list>
 * 						|	<redir> <token list>
 * 						|	(null)
 * 						;
 *
 * <redir>				:	<redir in>
 * 						|	<redir out>
 * 						;
 *
 * <redir in>			:	'<<' <file>
 * 						|	'<' <file>
 * 						;
 *
 * <redir out>			:	'>>' <file>
 * 						|	'>' <file>
 * 						;
 *
 */

/*
 * Create an ast recursively:
 *
 * cmd_line()		=> test all command line in order
 * cmd_line_1()		=> <and or> ';' <command line>
 * cmd_line_2()		=> <and or> ';'
 * cmd_line_3()		=> <and or>
 *
 * and_or()			=> test all "and or" in order
 * and_or_1()		=> <job> && <and or>
 * and_or_2()		=> <job> || <and or>
 * and_or_3()		=> <job>
 * and_or_4()		=> '(' <command line> ')' && <and or>
 * and_or_5()		=> '(' <command line> ')' || <and or>
 * and_or_6()		=> '(' <command line> ')'
 *
 * job()			=> test all job in order
 * job_1()			=> '(' <command> ')' '|' <job>
 * job_2()			=>     <command>     '|' <job>
 * job_3()			=> '(' <command> ')'
 * job_4()			=>     <command>
 *
 * cmd()			=> test all command in order
 * cmd_1()			=> <token list>
 *
 * tok_lst()		=> test token list
 * tok_lst_1()		=> <name> <token list>
 * tok_lst_2()		=> <token> <token list>
 * tok_lst_3()		=> <redir> <token list>
 * tok_lst_4()		=> (null)
 *
 * redir()			=> test all redirections in order
 * redir_1()		=> <redir in>
 * redir_2()		=> <redir out>
 *
 * redir_in()		=> test all in redirections in order
 * redir_in_1()		=> '<<' <file>
 * redir_in_2()		=> '<' <file>
 *
 * redir_out()		=> test all out redirections in order
 * redir_out_1()	=> '>>' <file>
 * redir_out_2()	=> '>' <file>
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

/* parse_and_or.c */
t_ast	*and_or(void);
t_ast	*and_or_1(void);
t_ast	*and_or_2(void);
t_ast	*and_or_3(void);
t_ast	*and_or_4(void);
t_ast	*and_or_5(void);
t_ast	*and_or_6(void);

/* parse_job.c */
t_ast	*job(void);
t_ast	*job_1(void);
t_ast	*job_2(void);
t_ast	*job_3(void);
t_ast	*job_4(void);

/* parse_cmd.c */
t_ast	*cmd(void);
t_ast	*cmd_1(void);

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

/* parse_tok_lst.c */
t_ast	*tok_lst(void);
t_ast	*tok_lst_1(void);
t_ast	*tok_lst_2(void);
t_ast	*tok_lst_3(void);
t_ast	*tok_lst_4(void);

#endif
