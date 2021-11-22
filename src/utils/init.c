/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:38:35 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/22 17:41:41 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* initialise enviroment */
static void	fill_env(char **env)
{
	int		i;
	char	*pwd;
	char	*sh_lvl;
	char	*aux;

	i = -1;
	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
		return ;
	sh_lvl = ft_strdup("SHLVL=1");
	while (env[++i])
		ft_lstadd_back(&g_sh.env, ft_lstnew((void *)ft_strdup(env[i])));
	if (i == 0)
	{
		if (getcwd(pwd, PATH_MAX))
		{
			aux = ft_strjoin("PWD=", pwd);
			ft_lstadd_back(&g_sh.env, ft_lstnew((void *)aux));
		}
		ft_lstadd_back(&g_sh.env, ft_lstnew((void *)sh_lvl));
	}
	free(pwd);
	free(sh_lvl);
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
