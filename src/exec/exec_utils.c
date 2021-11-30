/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:16:04 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/30 13:26:28 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* get error message support func. */
static char	*get_msg_2(int status)
{
	if (status == 143)
		return (ft_strdup("terminated"));
	else if (status == 0)
		return (ft_strdup(""));
	else if (status == 152)
		return (ft_strdup("cputime limit exceeded"));
	else if (status == 153)
		return (ft_strdup("filesize limit exceeded"));
	else if (status == 155)
		return (ft_strdup("profiling time alarm"));
	else if (status == 138)
		return (ft_strdup("user signal 1"));
	else if (status == 140)
		return (ft_strdup("user signal 2"));
	return (NULL);
}

/* get error message */
static char	*get_msg(int status)
{
	if (status == 129)
		return (ft_strdup("hangup"));
	else if (status == 1)
		return (ft_strdup(""));
	else if (status == 131)
		return (ft_strdup("quit"));
	else if (status == 132)
		return (ft_strdup("illegal instruction"));
	else if (status == 133)
		return (ft_strdup("trace/BPT trap"));
	else if (status == 136)
		return (ft_strdup("floating exception"));
	else if (status == 137)
		return (ft_strdup("killed"));
	else if (status == 135)
		return (ft_strdup("bus error"));
	else if (status == 139)
		return (ft_strdup("segmentation fault"));
	else if (status == 159)
		return (ft_strdup("bad system call"));
	else if (status == 141)
		return (ft_strdup("broken pipe"));
	else if (status == 142)
		return (ft_strdup("alarm clock"));
	return (get_msg_2(status));
}

/* handle signaled exit */
static int	handle_signal_exit(int status)
{
	int		exit_st;
	char	*msg;

	exit_st = WTERMSIG(status) + 128;
	ft_putchar_fd('\n', STDERR_FILENO);
	msg = get_msg(exit_st);
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
	if (WCOREDUMP(status))
		ft_putstr_fd(" (core dumped)\n", STDERR_FILENO);
	else
		ft_putchar_fd('\n', STDERR_FILENO);
	return (exit_st);
}

/* handle zombie process */
void	handle_zombies(void)
{
	pid_t	pid;
	int		status;

	status = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid <= 0)
			break ;
		if (WIFEXITED(status))
			g_sh.status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_sh.status = handle_signal_exit(status);
	}
}
