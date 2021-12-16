/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:42:23 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/17 00:06:23 by dpoveda-         ###   ########.fr       */
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
void	find_and_exec_cmd(t_cmd *cmd)
{
	char	*path;
	char	*cmd_path;

	if (*cmd->argv[0] == '/' || !ft_strncmp(cmd->argv[0], "~/", 2)
		|| !ft_strncmp(cmd->argv[0], "./", 2)
		|| !ft_strncmp(cmd->argv[0], "../", 3))
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
