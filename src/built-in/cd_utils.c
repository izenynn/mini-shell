#include <sh.h>

void	home_handler(t_list *head)
{
	goto_home();
	locate_env(head);
}

void	set_env(t_list *head)
{
	locate_env(head);
	g_sh.env = head;
}

void	try_to_goto_olpwd(void)
{
	while (g_sh.env)
	{
		if (ft_strncmp("OLDPWD=", (char *)g_sh.env->data, 7) == 0)
			break ;
		g_sh.env = g_sh.env->next;
	}
}

int	set_oldpwd(t_list *head)
{
	char	*pwd;
	char	*aux;

	pwd = malloc(sizeof(char) * PATH_MAX);
	if (!pwd)
		return (1);
	try_to_goto_olpwd();
	if (!getcwd(pwd, PATH_MAX))
	{
		free(pwd);
		return (1);
	}
	aux = ft_strjoin("OLDPWD=", pwd);
	if (g_sh.env)
	{
		free(g_sh.env->data);
		g_sh.env->data = (void *)ft_strdup(aux);
	}
	else
		ft_lstadd_back(&g_sh.env, ft_lstnew((void *)aux));
	g_sh.env = head;
	free(pwd);
	free(aux);
	return (0);
}
