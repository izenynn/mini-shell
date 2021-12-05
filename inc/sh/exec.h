/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:22:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/05 13:22:07 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*** INCLUDES ***/

# include <sh/ast.h>
# include <libft/ft_bool.h>

/*** DEFINE ***/

# define READ_END 0
# define WRITE_END 1

# define FD_IN 0
# define FD_OUT 1

/*** DATA ***/

/* binary flags for redir type */
/*enum e_redir {
	RD_TRUNC =		(1 << 0),
	RD_APPEND =		(1 << 1),
	RD_INFILE =		(1 << 2),
	RD_HDOC =		(1 << 3)
};*/

/*
 * struct s_io:
 * is_pipe[2]	=> is input and/or output in a pipe ?
 * ft_pipe[2]	=> file descriptors of the pipe
 * ft_read		=> previous pipe read end file descriptor
 * redir		=> redirection type (enum e_redir)
 * file[2]		=> input and output files for redirection (null if not redir)
 */
typedef struct s_io {
	t_bool	is_pipe[2];
	int		fd_pipe[2];
	int		fd_read;
	t_ast	*redir;
}	t_io;

typedef struct s_cmd {
	int		argc;
	char	**argv;
	t_io	*io;
}	t_cmd;

/*** PROTOTYPES ***/

/* exec_ast.c */
int		exec_ast(t_ast *ast);

/* exec_cmd.c */
t_io	*init_io(t_bool p_read, t_bool p_write, int fd_pipe[2], int fd_read);
int		handle_exec_cmd(t_cmd *cmd);
int		cmd_init(t_cmd *cmd, t_ast *ast, t_io *io);
void	cmd_del(t_cmd *cmd);

/* exec_utils */
void	handle_zombies(void);

/* exec_heredoc.c */
int	exec_heredoc(t_ast *ast);

/* heredoc.c */
int		handle_heredoc(t_ast *node);

/* utils.c */
char	*dir_join(char const *dir1, char const *dir2);

#endif
