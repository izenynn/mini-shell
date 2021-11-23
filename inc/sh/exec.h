/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:22:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/23 16:33:57 by dpoveda-         ###   ########.fr       */
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

 enum e_redir {
	RD_TRUNC =		(1 << 0),
	RD_APPEND =		(1 << 1),
	RD_INFILE =		(1 << 2),
	RD_HEREDOC =	(1 << 3)
};

typedef struct s_io {
	t_bool	pipe[2];
	int		fd_pipe[2];
	int		redir;
	char	*files[2];
}	t_io;

typedef struct s_cmd {
	int		argc;
	char	**argv;
	t_io	*io;
}	t_cmd;

/*** PROTOTYPES ***/

/* exec.c */
int		exec_ast(t_ast *ast);

/* cmd_utils.c */
t_io	*init_io(t_bool pipe_in, t_bool pipe_out, int fd_pipe[2]);
int		handle_exec_cmd(t_cmd *cmd);
int		cmd_init(t_cmd *cmd, t_ast *ast, t_io *io);
void	cmd_del(t_cmd *cmd);

/* utils.c */
char	*dir_join(char const *dir1, char const *dir2);

#endif
