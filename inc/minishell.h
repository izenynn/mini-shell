/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:57:48 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/11 13:33:07 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*** INCLUDES ***/

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

/* colors (ayu_dark theme) */
# define NOCOL "\x1b[0m"

# define FG_DEF "\x1b[39m"
# define BG_DEF "\x1b[49m"

# define FG_BLK "\x1b[30m"
# define FG_RED "\x1b[31m"
# define FG_GRN "\x1b[32m"
# define FG_YEL "\x1b[33m"
# define FG_BLU "\x1b[34m"
# define FG_MAG "\x1b[35m"
# define FG_CYN "\x1b[36m"
# define FG_WHT "\x1b[37;m"

# define FG_BBLK "\x1b[90m"
# define FG_BRED "\x1b[91m"
# define FG_BGRN "\x1b[92m"
# define FG_BYEL "\x1b[93m"
# define FG_BBLU "\x1b[94m"
# define FG_BMAG "\x1b[95m"
# define FG_BCYN "\x1b[96m"
# define FG_BWHT "\x1b[97m"

# define BG_BLK "\x1b[40m"
# define BG_RED "\x1b[41m"
# define BG_GRN "\x1b[42m"
# define BG_YEL "\x1b[43m"
# define BG_BLU "\x1b[0;44m"
# define BG_MAG "\x1b[0;45m"
# define BG_CYN "\x1b[0;46m"
# define BG_WHT "\x1b[0;47;m"

# define BG_BBLK "\x1b[100m"
# define BG_BRED "\x1b[101m"
# define BG_BGRN "\x1b[102m"
# define BG_BYEL "\x1b[103m"
# define BG_BBLU "\x1b[104m"
# define BG_BMAG "\x1b[105m"
# define BG_BCYN "\x1b[106m"
# define BG_BWHT "\x1b[107;m"

/* parse */
# define MAXCHR 1000 // max number of letters to be supported
# define MAXCMD 100 // max number of commands to be supported

/*** DATA ***/

// structs and global vars go here

/*** PROTOTYPES ***/

/* terminal.c */
void	init_terminal(void);

/* terminal_utils.c */
void	die(const char *s);
void	welcome(void);

#endif
