#include <sh.h>

void	ft_env(void)
{
	t_list	*head;

	head = g_sh.env;
	if (!g_sh.env)
		return ;
	while (g_sh.env)
	{
		printf("%s\n", (char *) g_sh.env->data);
		g_sh.env = g_sh.env->next;
	}
	g_sh.env = head;
}
