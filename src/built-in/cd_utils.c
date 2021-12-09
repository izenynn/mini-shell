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

void	try_to_goto_olpwd(t_list *head)
{
	t_list	*aux;

	aux = head;
	while (aux && aux->data)
	{
		if (ft_strncmp("OLDPWD=", (char *)aux->data, 7) == 0)
			break ;
		aux = aux->next;
	}
}

void	set_values(t_list *env, const char *aux)
{
	if (env != NULL)
	{
		free(env->data);
		env->data = (void *)ft_strdup(aux);
	}
	else
		ft_lstadd_back(&g_sh.env, ft_lstnew((void *)ft_strdup(aux)));
}

int	set_oldpwd(t_list *env)
{
	char	*pwd;
	char	*aux;

	pwd = ft_getenv("PWD");
	try_to_goto_olpwd(g_sh.env);
	if (env == NULL)
	{
		free(pwd);
		return (1);
	}
	if (pwd == NULL)
	{
		pwd = (char *)malloc(sizeof(char) * (PATH_MAX + 1));
		if (getcwd(pwd, PATH_MAX) == NULL)
		{
			free(pwd);
			return (1);
		}
	}
	aux = ft_strjoin("OLDPWD=", pwd);
	set_values(env, aux);
	free(pwd);
	free(aux);
	return (0);
}
