/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:42:24 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/05 01:11:03 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* handle here document read until delim */
static void heredoc_read(char *delim, int fd[2], t_bool is_parent)
{
	char	*line;
	//char	*aux;

	close(fd[READ_END]);
	//aux = ft_strjoin(delim, "\n");
	//line = ft_get_next_line(STDIN_FILENO);
	line = readline("> ");
	while (line)
	{
		//if (!ft_strncmp(line, aux, ft_strlen(aux) + 1))
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
		{
			close(fd[WRITE_END]);
			//close(WRITE_END);
			free(line);
			//free(aux);
			exit(EXIT_SUCCESS);
		}
		if (!is_parent)
			ft_putendl_fd(line, fd[WRITE_END]);
			//ft_putstr_fd(line, fd[WRITE_END]);
		free(line);
		//line = ft_get_next_line(STDIN_FILENO);
		line = readline("> ");
	}
	close(fd[WRITE_END]);
	//close(WRITE_END);
	free(line);
	//free(aux);
}

/* handle here document "<<" */
int	handle_heredoc(char *delim, t_bool is_parent, int out_fd)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (perror_ret("pipe", 1));
	pid = fork();
	if (pid < 0)
		return (perror_ret("fork", 1));
	if (pid > 0)
	{
		close(fd[WRITE_END]);
		if (!is_parent)
			dup2(fd[READ_END], out_fd);
		close(fd[READ_END]);
		waitpid(pid, NULL, 0);
	}
	else
	{
		heredoc_read(delim, fd, is_parent);
	}
	return (0);
}
