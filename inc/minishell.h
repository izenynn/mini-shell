/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:57:48 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/12 11:18:54 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*** INCLUDES ***/

/* mishell includes */
# include <minishell/colors.h>

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

// structs and global vars go here

/*** PROTOTYPES ***/

/* terminal.c */
void	init_terminal(void);
char	*prompt_read_input(void);

/* terminal_utils.c */
void	die(const char *s);
void	welcome(void);

#endif
