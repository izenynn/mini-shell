/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:57:48 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/21 16:23:35 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

/*** INCLUDES ***/

/* mishell includes */
# include <sh/builtin.h>
# include <sh/colors.h>
# include <sh/utils.h>
# include <sh/prompt.h>
# include <sh/lexer.h>
# include <sh/parser.h>
# include <sh/ast.h> 
# include <sh/exec.h>

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

/*** DEFINES ***/

/* path */
# ifndef PATH_MAX
#  define PATH_MAX 256
# endif

/*** DATA ***/

/* shell global struct
 *
 * status	=> last exit status
 * *env		=> enviroment vars
 * env_len	=> number of enviroment vars
 * *tok		=> to iterate tokens (used for creating the ast)
 */
typedef struct s_sh {
	int		status;
	t_list	*env;
	t_tok	*tok;
}	t_sh;

extern t_sh	g_sh;

#endif
