/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:38:35 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/17 19:46:38 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* handle flags */
void	handle_flags(int argc, char *argv[])
{
	if (argc > 1)
	{
		if (!ft_strncmp(argv[1], "-c\0", 3))
		{
			if (argc < 3)
			{
				write(STDERR_FILENO, "-c: option requires an argument\n", 32);
				exit(2);
			}
			else
			{
				handle_line(argv[2], FALSE);
				exit(g_sh.status);
			}
		}
		else
		{
			write(STDERR_FILENO, "error: no valid arguments\n", 26);
			exit(127);
		}
	}
}

/* add built in to built in list */
static void	add_blti(t_blti **head, char *name, int (*f)(char **))
{
	t_blti	*new;
	t_blti	*aux;

	new = (t_blti *)malloc(sizeof(t_blti));
	if (new == NULL)
		perror_exit("malloc");
	new->name = name;
	new->f = f;
	new->next = NULL;
	if (*head != NULL)
	{
		aux = *head;
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	else
		*head = new;
}

/* initialise built ins */
static t_blti	*init_blti(void)
{
	t_blti	*bi;

	bi = NULL;
	add_blti(&bi, "echo", ft_echo);
	add_blti(&bi, "cd", ft_changedir);
	add_blti(&bi, "pwd", ft_get_wdir);
	add_blti(&bi, "export", ft_export);
	add_blti(&bi, "unset", ft_unset);
	add_blti(&bi, "env", ft_env);
	add_blti(&bi, "exit", ft_exit);
	return (bi);
}

/* initialise global var */
static void	initialise_vars(void)
{
	g_sh.status = EXIT_SUCCESS;
	g_sh.bi = init_blti();
	g_sh.is_child = FALSE;
	g_sh.is_expd = FALSE;
	g_sh.fd_bak[0] = dup(STDIN_FILENO);
	g_sh.fd_bak[1] = dup(STDOUT_FILENO);
}

/* initialise shell */
void	init_shell(void)
{
	extern char	**environ;

	fill_env(environ);
	initialise_vars();
	sig_parent();
	read_config();
}
