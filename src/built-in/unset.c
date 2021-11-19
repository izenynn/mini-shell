#include <sh.h>

void	find_pos(const char *unset)
{
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(unset) + 2));
	if (!tmp)
		return ;
	tmp = ft_strcat((char *)unset, "=");
	while (g_sh.env)
	{
		if (ft_strncmp((char *)g_sh.env->next->data, tmp,
				   ft_strlen(unset)) == 0)
			break ;
		g_sh.env = g_sh.env->next;
	}
	free(tmp);
}

void	delete_and_join(t_list *head, t_list *aux)
{
	aux = g_sh.env->next->next;
	ft_lstdelone(g_sh.env->next, free);
	g_sh.env->next = aux;
	g_sh.env = head;
	free(aux);
}

int	ft_unset(char **unset)
{
	t_list	*head;
	t_list	*aux;
	int		i;

	head = g_sh.env;
	aux = NULL;
	i = -1;
	if (unset)
	{
		while (unset[++i])
		{
			find_pos(unset[i]);
			if (!g_sh.env)
				g_sh.env = head;
			else
				delete_and_join(head, aux);
		}
	}
	else
	{
		printf("%s\n", "unset: not enough arguments");
		return (-1);
	}
	g_sh.env = head;
	return (0);
}
