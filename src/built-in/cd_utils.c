#include <sh.h>

void	update_var(char *var_name, char *var)
{
	t_list	*head;
	char	*content;
	char	*tmp;

	head = g_sh.env;
	tmp = ft_strjoin(var_name, "=");
	free(var_name);
	content = ft_substr(var, get_var_len(var) + 1,
			ft_strlen(var) - ft_strlen(tmp));
	while (g_sh.env)
	{
		if (ft_strncmp(tmp, (char *)g_sh.env->data, ft_strlen(tmp)) == 0)
			break ;
		g_sh.env = g_sh.env->next;
	}
	free(g_sh.env->data);
	g_sh.env->data = ft_strjoin(tmp, content);
	g_sh.env = head;
	free(tmp);
	free(content);
}

void	try_to_goto_olpwd(void)
{
	while (g_sh.env && g_sh.env->data)
	{
		if (ft_strncmp("OLDPWD=", (char *)g_sh.env->data, 7) == 0)
			break ;
		g_sh.env = g_sh.env->next;
	}
}

void	set_values(const char *aux)
{
	if (g_sh.env)
	{
		free(g_sh.env->data);
		g_sh.env->data = (void *)ft_strdup(aux);
	}
	else
		ft_lstadd_back(&g_sh.env, ft_lstnew((void *)aux));
}

int	set_oldpwd(t_list *head)
{
	char	*pwd;
	char	*aux;

	pwd = ft_getenv("PWD");
	try_to_goto_olpwd();
	if (!pwd)
	{
		pwd = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
		if (!getcwd(pwd, PATH_MAX))
		{
			free(pwd);
			return (1);
		}
	}
	aux = ft_strjoin("OLDPWD=", pwd);
	set_values(aux);
	g_sh.env = head;
	free(pwd);
	free(aux);
	return (0);
}
