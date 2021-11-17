/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:57:48 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/16 12:22:18 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

/*** INCLUDES ***/

/* mishell includes */
# include <sh/built-in.h>
# include <sh/colors.h>
# include <sh/utils.h>
# include <sh/prompt.h>
# include <sh/lexer.h>
# include <sh/parser.h>
# include <sh/ast.h>

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

/* prompt */

# define MAXCHR 1000 // max number of letters to be supported
# define MAXCMD 100 // max number of commands to be supported

/*** DATA ***/

/*
 * l_exit => last exit status
 */
typedef struct s_sh {
	int		status;
	char	**env;
	int		env_len;
	//extern int status;
}	t_sh;

extern t_sh	g_sh;

#endif
