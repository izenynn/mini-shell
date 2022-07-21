/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:57:48 by dpoveda-          #+#    #+#             */
/*   Updated: 2022/07/21 11:36:20 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

/*** INCLUDES ***/

/* mishell includes */
# include "sh/main.h"
# include "sh/builtin.h"
# include "sh/colors.h"
# include "sh/utils.h"
# include "sh/signals.h"
# include "sh/prompt.h"
# include "sh/lexer.h"
# include "sh/parser.h"
# include "sh/ast.h"
# include "sh/exec.h"
# include "sh/read_config.h"

/* our own implementation of libc */
# include "libft.h"

/* standard libraries */
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

/* sys libraries */
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <dirent.h>

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
# ifndef TRUE
#  define TRUE 1
# endif
# ifndef FALSE
#  define FALSE 0
# endif

/* path */
# ifndef PATH_MAX
#  define PATH_MAX 256
# endif

/*** DATA ***/

/* shell global struct
 *
 * status		=> last exit status
 * *env			=> enviroment vars
 * *prev		=> to save previous token when we tokenize a enviroment variable
 * *tok			=> to iterate tokens (used for creating the ast)
 * **so_ast		=> save current "and or" ast node to attach nodes
 * *cmd_ast		=> save current command ast node to attach args and redirs
 * *bi			=> built-in list
 * fd_bak		=> backup STDIN and STDOUT fd
 * last_pid		=> last process in pipe pid
 * is_child		=> if a process is a child
 * is_expd		=> if token vars are already expanded
 * tokdel		=> if token was deleted during lexer
 */
typedef struct s_sh {
	int		status;
	t_list	**env;
	t_tok	*prev;
	t_tok	*tok;
	t_ast	**ao_ast;
	t_ast	*cmd_ast;
	t_blti	*bi;
	int		fd_bak[2];
	pid_t	last_pid;
	t_bool	is_child;
	t_bool	is_expd;
	t_bool	tokdel;
}	t_sh;

extern t_sh	g_sh;

#endif
