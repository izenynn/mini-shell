/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 00:42:24 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/06 14:12:00 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* get new temp file name */
static char	*get_fname(char *dir)
{
	char	*name;
	char	*aux;
	int		i;

	i = 0;
	while (++i < 100)
	{
		// "/ms_1"
		aux = ft_itoa(i);
		name = ft_strjoin("/.ms_", aux);
		free(aux);

		// "/ms_1.tmp"
		aux = name;
		name = ft_strjoin(aux, ".tmp");
		free(aux);

		// "/tmp/ms_1"
		aux = name;
		name = ft_strjoin(dir, aux);
		free(aux);

		// check access
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
	}
	return (NULL);
}

/* create temp file for heredoc */
static char	*new_tmp()
{
	char		*file;
	char		*aux;

	file = NULL;
	if (access(TMPDIR, R_OK | W_OK) == 0)
	{
		//file = get_fname(TMPDIR);
		if (file != NULL)
			return (file);
	}

	aux = ft_getenv("HOME");
	if (aux != NULL)
	{
		//if (access(aux, R_OK | W_OK) == 0)
		//	file = get_fname(aux);
		free(aux);
		if (file != NULL)
			return(file);
	}

	aux = (char *)malloc((PATH_MAX + 1) * sizeof(char));
	getcwd(aux, PATH_MAX);
	if (aux != NULL)
	{
		if (access(aux, R_OK | W_OK) == 0)
			file = get_fname(aux);
		free(aux);
		if (file != NULL)
			return(file);
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

	file = new_tmp();
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
