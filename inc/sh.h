/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:57:48 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/14 10:30:17 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

/*** INCLUDES ***/

/* mishell includes */
# include <sh/main.h>
# include <sh/builtin.h>
# include <sh/colors.h>
# include <sh/utils.h>
# include <sh/signals.h>
# include <sh/prompt.h>
# include <sh/lexer.h>
# include <sh/parser.h>
# include <sh/ast.h> 
# include <sh/exec.h>
# include <sh/read_config.h>

/* our own implementation of libc */
# include <libft.h>

/* standard libraries */
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

/* sys libraries */
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

/* signals */
# include <signal.h>

/* readline libraries */
# include <readline/readline.h>
# include <readline/history.h>

/* standard unix library */
# include <unistd.h>

/* terminal library */
# include <termios.h>
# include <term.h>

/* open() */
# include <fcntl.h>

/*** DEFINES ***/

/* temp files */
# define TMPDIR "/tmp"

/* bool */
# define TRUE 1
# define FALSE 0

/* path */
# ifndef PATH_MAX
#  define PATH_MAX 256
# endif

/*** DATA ***/

/* shell global struct
 *
 * status	=> last exit status
 * *env		=> enviroment vars
 * *tok		=> to iterate tokens (used for creating the ast)
 * *cmd_ast	=> save current command ast node to attach args and redirs
 * *bi		=> built-in list
 * fd_bak	=> backup STDIN and STDOUT fd
 * last_pid	=> last process in pipe pid
 */
typedef struct s_sh {
	int		status;
	t_list	**env;
	t_tok	*tok;
	t_ast	*cmd_ast;
	t_blti	*bi;
	int		fd_bak[2];
	pid_t	last_pid;
}	t_sh;

extern t_sh	g_sh;
#endif
