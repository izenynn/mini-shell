/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:44:14 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/25 19:56:27 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

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

/* get redir type of input */
int	redir_getin(int redir)
{
	return (redir & ((~RD_TRUNC) & (~RD_APPEND)));
}

/* get redir type of output */
int	redir_getout(int redir)
{
	return (redir & ((~RD_INFILE) & (~RD_HEREDOC)));
}

/* search command in path */
static char	*get_path(char *cmd, const char *path)
{
	char	*file;
	char	*dir;
	int		diff;

	while (*path)
	{
		diff = ft_strchr(path, ':') - path;
		if (diff < 0)
			diff = ft_strlen(path);
		dir = ft_substr(path, 0, diff);
		file = dir_join(dir, cmd);
		free(dir);
		if (access(file, X_OK) == 0)
			return (file);
		free(file);
		if (ft_strlen(path) < (size_t)diff)
			break ;
		path += diff;
		if (*path)
			path++;
	}
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
	return (NULL);
}

/* execute command */
static void	exec_cmd(t_cmd *cmd)
{
	char	*path;
	char	*cmd_path;

	if (*cmd->argv[0] == '/' || *cmd->argv[0] == '.' || *cmd->argv[0] == '~')
		cmd_path = cmd->argv[0];
	else
	{
		path = ft_getenv("PATH");
		if (path == NULL)
		{
			ft_putstr_fd(cmd->argv[0], STDERR_FILENO);
			ft_putstr_fd(": command not found\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
		cmd_path = get_path(cmd->argv[0], path);
	}
	execve(cmd_path, cmd->argv, get_env_char());
	perror_exit(cmd_path);
}

/* redir */
void	redir(t_cmd *cmd)
{
	int	fd_io[2];

	dup2(g_sh.fd_bak[0], STDIN_FILENO);
	dup2(g_sh.fd_bak[1], STDOUT_FILENO);
	if (redir_getin(cmd->io->redir) == RD_INFILE)
	{
		fd_io[FD_IN] = open(cmd->io->files[FD_IN], O_RDONLY);
		if (fd_io[FD_IN] == -1)
			perror_exit("open");
		dup2(fd_io[FD_IN], STDIN_FILENO);
	}
	if (redir_getout(cmd->io->redir) == RD_TRUNC)
	{
		fd_io[FD_OUT] = open(cmd->io->files[FD_OUT], O_WRONLY | O_CREAT | O_TRUNC, 0664);
		if (fd_io[FD_OUT] == -1)
			perror_exit("open");
		dup2(fd_io[FD_OUT], STDOUT_FILENO);
	}
	if (cmd->io->is_pipe[FD_IN] == TRUE)
		dup2(cmd->io->fd_read, STDIN_FILENO);
	if (cmd->io->is_pipe[FD_OUT] == TRUE)
		dup2(cmd->io->fd_pipe[WRITE_END], STDOUT_FILENO);
}

/* execute command */
int	handle_exec_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	t_blti	*bi;

	// TODO free cmd->io struct somewhere
	if (cmd->argc < 0)
		return (1);

	// check for built in
	bi = g_sh.bi;
	while (bi != NULL)
	{
		if (!ft_strncmp(cmd->argv[0], bi->name, ft_strlen(bi->name) + 1))
		{
			redir(cmd);
			g_sh.status = bi->f(cmd->argv);
			// restore fd
			//close();
			//close();
			dup2(g_sh.fd_bak[0], STDIN_FILENO);
			dup2(g_sh.fd_bak[1], STDOUT_FILENO);
			return (0);
		}
		bi = bi->next;
	}
	// not a built-in
	pid = fork();
	if (pid == -1)
		perror_ret("fork", 1);
	if (pid > 0)
	{
		if (!ft_strncmp(cmd->argv[0], "exit", 5))
		{
			waitpid(pid, &status, 0);
			g_sh.status = WEXITSTATUS(status);
			exit(g_sh.status);
		}
		waitpid(pid, &status, WNOHANG);
		g_sh.status = WEXITSTATUS(status);
		if (g_sh.status != EXIT_SUCCESS)
			return (1);
	}
	else
	{
		sig_child();
		// redir
		redir(cmd);
		if (cmd->io->is_pipe[FD_IN] || cmd->io->is_pipe[FD_OUT])
		{
			close(cmd->io->fd_pipe[READ_END]);
			close(cmd->io->fd_pipe[WRITE_END]);
			close(cmd->io->fd_read);
		}
		// exec cmd
		exec_cmd(cmd);
	}
	return (0);
} 

/* initialise cmd struct */
int	cmd_init(t_cmd *cmd, t_ast *ast, t_io *io)
{
	t_ast	*aux;
	int		i;

	if (cmd == NULL || ast_gettype(ast) != AST_CMD)
	{
		cmd->argc = 0;
		return (-1);
	}
	aux = ast;
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
		cmd->argv[i] = (char *)malloc(sizeof(char) * (ft_strlen(aux->data) + 1));
		strcpy(cmd->argv[i], aux->data);
		aux = aux->right;
		i++;
	}
	cmd->argv[i] = NULL;
	cmd->argc = i;
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
