/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:42:24 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/09 14:33:35 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* handle here document read until delim */
static void	read_input(char *delim, int fd)
{
	char	*line;

	line = readline("> ");
	while (line != NULL)
	{
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
		{
			close(fd);
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putendl_fd(line, fd);
		free(line);
		line = readline("> ");
	}
	write(STDERR_FILENO, "warning: here-doc delimited by end-of-file\n", 43);
	close(fd);
	free(line);
	exit (EXIT_SUCCESS);
}

/* read input in a child */
static int	handle_read(char *delim, int fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror_ret("fork", 1));
	if (pid > 0)
	{
		sig_ignore();
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status) && WTERMSIG(status) + 128 == 130)
		{
			write(STDOUT_FILENO, "\n", 1);
			return (1);
		}
		sig_parent();
	}
	else
	{
		sig_heredoc();
		read_input(delim, fd);
	}
	return (0);
}

/* handle here document "<<" */
int	handle_heredoc(t_ast *node)
{
	char	*file;
	int		fd;

	file = new_tmp();
	if (file == NULL)
	{
		ft_putstr_fd("error: cannot create file for heredoc\n", STDERR_FILENO);
		return (1);
	}
	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("error: cannot open file for heredoc\n", STDERR_FILENO);
		free(file);
		return (1);
	}
	if (handle_read(node->data, fd))
	{
		free(file);
		return (1);
	}
	close(fd);
	free(node->data);
	node->data = file;
	return (0);
}
