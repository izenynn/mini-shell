#include <sh.h>

int	find_pos(const char *unset)
{
	int	i;

	i = 0;
	while (g_sh.env)
	{
		if (ft_strncmp((char *)g_sh.env->next->data, unset,
				   ft_strlen(unset)) == 0)
			break ;
		i++;
		g_sh.env = g_sh.env->next;
	}
	return (i);
}

void	delete_and_join(t_list *head, t_list *aux)
{
	aux = g_sh.env->next->next;
	ft_lstdelone(g_sh.env->next, free);
	g_sh.env->next = aux;
	g_sh.env = head;
}

int	ft_unset(const char *unset)
{
	t_list	*head;
	t_list	*aux;

	head = g_sh.env;
	aux = NULL;
	if (unset)
	{
		find_pos(unset);
		if (!g_sh.env)
		{
			g_sh.env = head;
			return (-1);
		}
		else
			delete_and_join(head, aux);
	}
	else
	{
		printf("%s\n", "unset: not enough arguments");
		return (-1);
	}
	return (0);
}
