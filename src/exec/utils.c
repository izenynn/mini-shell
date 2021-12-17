/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:48:15 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/17 01:26:06 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* initialise arguments of cmd struct */
static int	cmd_init_args(t_cmd *cmd, t_ast *ast, t_ast *aux)
{
	int		i;
	size_t	len;

	i = 0;
	while (aux && (ast_gettype(aux) == AST_ARG || ast_gettype(aux) == AST_CMD))
	{
		aux = aux->right;
		i++;
	}
	cmd->argv = (char **)malloc(sizeof(char *) * (i + 1));
	if (cmd->argv == NULL)
		perror_ret("malloc", 1);
	aux = ast;
	i = 0;
	while (aux && (ast_gettype(aux) == AST_ARG || ast_gettype(aux) == AST_CMD))
	{
		len = ft_strlen(aux->data);
		cmd->argv[i] = (char *)malloc(sizeof(char) * (len + 1));
		ft_strcpy(cmd->argv[i], aux->data);
		aux = aux->right;
		i++;
	}
	cmd->argv[i] = NULL;
	cmd->argc = i;
	return (0);
}

/* initialise cmd struct */
int	cmd_init(t_cmd *cmd, t_ast *ast, t_io *io)
{
	if (ast == NULL || ast_gettype(ast) != AST_CMD)
	{
		cmd->argc = 0;
		return (-1);
	}
	if (ast->data == NULL)
	{
		cmd->argc = 0;
		cmd->argv = (char **)malloc(sizeof(char *));
		if (cmd->argv == NULL)
			perror_ret("malloc", 1);
		cmd->argv[0] = NULL;
		cmd->io = io;
		return (0);
	}
	if (cmd_init_args(cmd, ast, ast) == 1)
		return (1);
	cmd->io = io;
	return (0);
}

/* free cmd struct */
void	cmd_del(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->argc)
		free(cmd->argv[i]);
	free(cmd->argv);
	free(cmd->io);
	cmd->argc = 0;
}

/* initialise io struct */
t_io	*init_io(t_bool p_read, t_bool p_write, int fd_pipe[2], int fd_read)
{
	t_io	*io;

	io = (t_io *)malloc(sizeof(t_io));
	io->is_pipe[READ_END] = p_read;
	io->is_pipe[WRITE_END] = p_write;
	if (p_read || p_write)
	{
		io->fd_pipe[READ_END] = fd_pipe[READ_END];
		io->fd_pipe[WRITE_END] = fd_pipe[WRITE_END];
		io->fd_read = fd_read;
	}
	io->redir = 0;
	return (io);
}

/* join two strings with a '/' between them */
char	*dir_join(char const *dir1, char const *dir2)
{
	char	*save;
	char	*out;

	if (!dir1 || !dir2)
		return (NULL);
	out = malloc(ft_strlen(dir1) + ft_strlen(dir2) + 2);
	if (!out)
		return (NULL);
	save = out;
	while (*dir1)
		*out++ = *dir1++;
	*out++ = '/';
	while (*dir2)
		*out++ = *dir2++;
	*out = '\0';
	return (save);
}
