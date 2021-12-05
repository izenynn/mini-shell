/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:42:24 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/05 13:34:06 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* create temp file for heredoc */
static char	*new_file()
{
	char		*file;
	char		*aux1;
	char		*aux2;
	int			i;

	i = 0;
	while (++i)
	{
		aux2 = ft_itoa(i);
		aux1 = ft_strjoin(TMPDIR "/ms_hd_", aux2);
		free(aux2);
		file = ft_strjoin(aux1, ".tmp");
		free(aux1);
		if (access(file, F_OK) == -1)
			return (file);
		free(file);
	}
	return (NULL);
}

/* handle here document read until delim */
static void read_input(char *delim, int fd)
{
	char	*line;
	//char	*aux;

	//aux = ft_strjoin(delim, "\n");
	//line = ft_get_next_line(STDIN_FILENO);
	line = readline("> ");
	while (line)
	{
		//if (!ft_strncmp(line, aux, ft_strlen(aux) + 1))
		if (!ft_strncmp(line, delim, ft_strlen(delim) + 1))
		{
			close(fd);
			//close(WRITE_END);
			free(line);
			//free(aux);
			exit(EXIT_SUCCESS);
		}
		//if (!is_parent)
		//	ft_putendl_fd(line, fd);
		ft_putendl_fd(line, fd);
			//ft_putstr_fd(line, fd[WRITE_END]);
		free(line);
		//line = ft_get_next_line(STDIN_FILENO);
		line = readline("> ");
	}
	close(fd);
	//close(WRITE_END);
	free(line);
	//free(aux);
}

/* read input in a child */
static int	handle_read(char *delim, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (perror_ret("fork", 1));
	if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		read_input(delim, fd);
	return (0);
}

/* handle here document "<<" */
int	handle_heredoc(t_ast *node)
{
	char	*file;
	int		fd;

	file = new_file();
	if (file == NULL)
	{
		ft_putstr_fd("error: cannot create file for heredoc\n", STDERR_FILENO);
		return (1);
	}
	fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		free(file);
		perror_ret(file, 1);
	}
	if (handle_read(node->data, fd))
		return (1);
	close(fd);
	// change node
	free(node->data);
	node->data = file;
	return (0);
}
