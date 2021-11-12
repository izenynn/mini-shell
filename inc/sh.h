/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:57:48 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/12 11:57:11 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_H
# define SH_H

/*** INCLUDES ***/

/* mishell includes */
# include <sh/colors.h>

/* our own implementation of libc */
# include <libft.h>

/* standard libraries */
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

/* sys libraries */
# include <sys/types.h>
# include <sys/wait.h>

/* readline libraries */
# include <readline/readline.h>
# include <readline/history.h>

/* standard unix library */
# include <unistd.h>

/* terminal library */
# include <termios.h>
# include <term.h>

/*** DEFINES ***/

/* parse */
//# define MAXCHR 1000 // max number of letters to be supported
//# define MAXCMD 100 // max number of commands to be supported

/*** DATA ***/

typedef struct s_sh {
	/* last exit status */
	int		l_exit;
}	t_sh;

extern t_sh	g_sh;

/*** PROTOTYPES ***/

/* prompt/prompt.c */
char	*prompt_read_input(void);

/* prompt/prompt_init.c */
void	init_prompt(void);

/* utils/init.c */
void	init_shell();

/* utils/error_utils.c */
void	perror_exit(const char *s);

#endif
