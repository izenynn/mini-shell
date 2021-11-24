/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:38:35 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/24 18:46:48 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

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
	//add_blti(&bi, "alias", ft_alias);
	add_blti(&bi, "exit", ft_exit);
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
	aux = NULL;
	sh_lvl = ft_strdup("SHLVL=1");
	while (env[++i])
		ft_lstadd_back(&g_sh.env, ft_lstnew((void *)ft_strdup(env[i])));
	if (!env)
	{
		if (getcwd(pwd, PATH_MAX))
		{
			aux = ft_strjoin("PWD=", pwd);
			ft_lstadd_back(&g_sh.env, ft_lstnew((void *)ft_strdup(aux)));
		}
		ft_lstadd_back(&g_sh.env, ft_lstnew(ft_strdup((void *)sh_lvl)));
	}
	if (aux)
		free(aux);
	free(pwd);
	free(sh_lvl);
}

/* initialise global var */
static void	initialise_vars(void)
{
	g_sh.status = EXIT_SUCCESS;
	g_sh.bi = init_blti();
	dup2(STDIN_FILENO, g_sh.fd_bak[0]);
	dup2(STDOUT_FILENO, g_sh.fd_bak[1]);
}

/* initialise shell */
void	init_shell(void)
{
	extern char	**environ;

	fill_env(environ);
	initialise_vars();
	init_prompt();
	sig_parent();
}
