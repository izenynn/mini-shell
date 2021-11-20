/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:38:35 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 17:27:08 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static void	fill_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_lstadd_back(&g_sh.env, ft_lstnew((void *)ft_strdup(env[i])));
}

static void	initialise_vars()
{
	g_sh.status = EXIT_SUCCESS;
}

/* initialise shell */
void	init_shell()
{
	extern char	**environ;

	fill_env(environ);
	initialise_vars();
}
