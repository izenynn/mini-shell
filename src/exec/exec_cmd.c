/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:44:14 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/17 17:49:12 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* check for empty command */
static int	check_empty_cmd(t_cmd *cmd)
{
	pid_t	pid;

	if (cmd->argv[0] == NULL)
	{
		pid = fork();
		if (pid == -1)
			perror_ret("fork", 1);
		if (pid > 0)
		{
			if (!cmd->io->is_pipe[WRITE_END])
				g_sh.last_pid = pid;
			return (1);
		}
		else
		{
			if (redir_cmd(cmd, TRUE))
				exit(EXIT_FAILURE);
			exit(EXIT_SUCCESS);
		}
	}
	else if (cmd->argv[0][0] == '\0')
		return (error_ret(" : command not found\n", 1));
	return (0);
}

/* check for built-in and no pipes */
static int	check_builtin_no_pipes(t_cmd *cmd)
{
	t_blti	*bi;

	if (!cmd->io->is_pipe[READ_END] && !cmd->io->is_pipe[WRITE_END])
	{
		bi = g_sh.bi;
		while (bi != NULL)
		{
			if (!ft_strncmp(cmd->argv[0], bi->name, ft_strlen(bi->name) + 1))
			{
				if (redir_cmd(cmd, TRUE))
					return (-1);
				g_sh.status = bi->f(cmd->argv);
				dup2(g_sh.fd_bak[0], STDIN_FILENO);
				dup2(g_sh.fd_bak[1], STDOUT_FILENO);
				return (1);
			}
			bi = bi->next;
		}
	}
	return (0);
}

/* check for built-in in pipes */
static int	check_builtin_pipes(t_cmd *cmd)
{
	t_blti	*bi;
	int		status;

	bi = g_sh.bi;
	while (bi != NULL)
	{
		if (!ft_strncmp(cmd->argv[0], bi->name, ft_strlen(bi->name) + 1))
		{
			if (redir_cmd(cmd, TRUE))
				exit(EXIT_FAILURE);
			status = bi->f(cmd->argv);
			dup2(g_sh.fd_bak[0], STDIN_FILENO);
			dup2(g_sh.fd_bak[1], STDOUT_FILENO);
			exit(status);
		}
		bi = bi->next;
	}
	return (0);
}

/* execute command in child */
static int	exec_in_child(t_cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		perror_ret("fork", 1);
	if (pid > 0)
	{
		sig_ignore();
		if (!cmd->io->is_pipe[WRITE_END])
			g_sh.last_pid = pid;
	}
	else
	{
		sig_child();
		g_sh.is_child = TRUE;
		check_builtin_pipes(cmd);
		if (redir_cmd(cmd, FALSE))
			exit(EXIT_FAILURE);
		find_and_exec_cmd(cmd);
	}
	return (0);
}

/* execute command */
int	handle_exec_cmd(t_cmd *cmd)
{
	int		ret;

	if (cmd->argc < 0)
		return (1);
	if (check_empty_cmd(cmd) == 1)
		return (0);
	ret = check_builtin_no_pipes(cmd);
	if (ret != 0)
	{
		if (ret == -1)
			return (1);
		if (ret == 1)
			return (0);
	}
	exec_in_child(cmd);
	return (0);
}
