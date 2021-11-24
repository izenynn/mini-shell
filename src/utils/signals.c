/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 23:56:06 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/24 01:06:28 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* restore signals for child */
static void	handle_sig_child(int signal)
{
	if (signal == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (signal == SIGQUIT)
		write(STDOUT_FILENO, "    quit\n", 9);
}

/* parent signals */
static void	handle_sig_parent(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		print_prompt_cwd();
		rl_redisplay();
	}
}

/* initialise signals for child */
void	sig_child(void)
{
	signal(SIGINT, handle_sig_child);
	signal(SIGQUIT, handle_sig_child);
}

/* initialise signals for parent */
void	sig_parent(void)
{
	signal(SIGINT, handle_sig_parent);
	//signal(SIGQUIT, SIG_IGN);
}

/* ignore signals */
void	sig_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}
