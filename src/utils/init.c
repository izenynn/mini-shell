/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:38:35 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/23 14:02:01 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/*static void	add_blti(t_blti **head, char *name, void (*f)(char **))
{
	t_blti	*new;
	t_blti	*aux;

	new = (t_blti *)malloc(sizeof(t_blti));
	if (new == NULL)
		perror_exit("malloc");
	new->name = name;
	new->f = f;
	if (*head != NULL)
	{
		aux = *head;
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	else
		*head = new;
}*/

/* initialise built ins */
static t_blti	*init_blti(void)
{
	t_blti	*bi;

	bi = NULL;
	/*add_blti(&bi, "echo", ft_echo);
	new_blti(&bi, "cd", ft_changedir);
	new_blti(&bi, "pwd", ft_get_wdir);
	new_blti(&bi, "export", ft_export);
	new_blti(&bi, "unset", ft_unset);
	new_blti(&bi, "env", ft_env);
	//new_blti(&bi, "alias", ft_changedir());
	new_blti(&bi, "exit", ft_exit);*/
	return (bi);
}

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
	g_sh.bi = init_blti();
}

/* initialise shell */
void	init_shell(void)
{
	extern char	**environ;

	fill_env(environ);
	initialise_vars();
}
