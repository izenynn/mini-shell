/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:44:14 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/09 20:14:47 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

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
	exit(127);
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
			exit(127);
		}
		cmd_path = get_path(cmd->argv[0], path);
	}
	execve(cmd_path, cmd->argv, get_env_char());
	perror_exit(cmd_path);
}

/* redir */
int	redir_cmd(t_cmd *cmd, t_bool is_parent)
{
	int		fd_io[2];
	int		type;
	t_ast	*redir;

	fd_io[0] = -1;
	fd_io[1] = -1;
	// pipe
	if (cmd->io->is_pipe[FD_IN] == TRUE && !is_parent)
		dup2(cmd->io->fd_read, STDIN_FILENO);
	if (cmd->io->is_pipe[FD_OUT] == TRUE)
		dup2(cmd->io->fd_pipe[WRITE_END], STDOUT_FILENO);
	if (!is_parent && (cmd->io->is_pipe[FD_IN] || cmd->io->is_pipe[FD_OUT]))
	{
		close(cmd->io->fd_pipe[READ_END]);
		close(cmd->io->fd_pipe[WRITE_END]);
		close(cmd->io->fd_read);
	}
	// redir in
	redir = cmd->io->redir;
	while (redir != NULL)
	{
		type = ast_gettype(redir);
		if (type & AST_RD_TRUNC)
		{
			if (fd_io[FD_OUT] >= 0)
				close(fd_io[FD_OUT]);

			fd_io[FD_OUT] = open(redir->data, O_WRONLY | O_CREAT | O_TRUNC, 0664);
			if (fd_io[FD_OUT] == -1)
				return (perror_ret(redir->data, 1));
		}
		else if (type & AST_RD_APPEND)
		{
			if (fd_io[FD_OUT] >= 0)
				close(fd_io[FD_OUT]);

			fd_io[FD_OUT] = open(redir->data, O_WRONLY | O_CREAT | O_APPEND, 0664);
			if (fd_io[FD_OUT] == -1)
				return (perror_ret(redir->data, 1));
		}
		else if (type & AST_RD_INFILE)
		{
			if (fd_io[FD_IN] >= 0)
				close(fd_io[FD_IN]);

			fd_io[FD_IN] = open(redir->data, O_RDONLY);
			if (fd_io[FD_IN] == -1)
				return (perror_ret(redir->data, 1));
		}
		else if (type & AST_RD_HDOC)
		{
			if (fd_io[FD_IN] >= 0)
				close(fd_io[FD_IN]);
			fd_io[FD_IN] = open(redir->data, O_RDONLY);
			if (fd_io[FD_IN] == -1)
				return (perror_ret(redir->data, 1));
			if (unlink(redir->data) == -1)
				perror_ret("unlink", 1);
		}
		redir = redir->left;
	}
	if (fd_io[FD_IN] >= 0 && !is_parent)
	{
		dup2(fd_io[FD_IN], STDIN_FILENO);
		close(fd_io[FD_IN]);
	}
	if (fd_io[FD_OUT] >= 0)
	{
		dup2(fd_io[FD_OUT], STDOUT_FILENO);
		close(fd_io[FD_OUT]);
	}
	return (0);
}

/* execute command */
int	handle_exec_cmd(t_cmd *cmd)
{
	pid_t	pid;
	int		status;
	t_blti	*bi;

	if (cmd->argc < 0)
		return (1);

	// if no command
	if (cmd->argv[0] == NULL)
	{
		pid = fork();
		if (pid == -1)
			perror_ret("fork", 1);
		if (pid > 0)
		{
			if (!cmd->io->is_pipe[WRITE_END])
				g_sh.last_pid = pid;
			return (0);
		}
		else
		{
			if (redir_cmd(cmd, TRUE))
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
	}
	// check for built in if no pipes
	if (!cmd->io->is_pipe[READ_END] && !cmd->io->is_pipe[WRITE_END])
	{
		bi = g_sh.bi;
		while (bi != NULL)
		{
			if (!ft_strncmp(cmd->argv[0], bi->name, ft_strlen(bi->name) + 1))
			{
				if (redir_cmd(cmd, TRUE))
					return (1);
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
	}
	// not a built-in
	pid = fork();
	if (pid == -1)
		perror_ret("fork", 1);
	if (pid > 0)
	{
		if (!cmd->io->is_pipe[WRITE_END])
			g_sh.last_pid = pid;
	}
	else
	{
		sig_child();
		// check for built-in
		bi = g_sh.bi;
		while (bi != NULL)
		{
			if (!ft_strncmp(cmd->argv[0], bi->name, ft_strlen(bi->name) + 1))
			{
				if (redir_cmd(cmd, TRUE))
					exit(EXIT_FAILURE);
				status = bi->f(cmd->argv);
				// restore fd
				dup2(g_sh.fd_bak[0], STDIN_FILENO);
				dup2(g_sh.fd_bak[1], STDOUT_FILENO);
				exit(status);
			}
			bi = bi->next;
		}
		// exec cmd
		if (redir_cmd(cmd, FALSE))
			exit(EXIT_FAILURE);
		exec_cmd(cmd);
	}
	return (0);
}
