/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:38:35 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/21 13:33:13 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* initialise enviroment */
static void	fill_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_lstadd_back(&g_sh.env, ft_lstnew((void *)ft_strdup(env[i])));
}

/* initialise global var */
static void	initialise_vars(void)
{
	g_sh.status = EXIT_SUCCESS;
}

/* initialise shell */
void	init_shell(void)
{
	extern char	**environ;

	fill_env(environ);
	initialise_vars();
}
