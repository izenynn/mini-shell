#include <sh.h>

void	update_env(void)
{
	char	*n_path;

	n_path = ft_get_wdir();
	g_sh.env->data = ft_strdup("PWD=");
	g_sh.env->data = ft_realloc(g_sh.env->data, sizeof(char)
			* (ft_strlen(n_path) + 5));
	g_sh.env->data = ft_strcat((char *)g_sh.env->data, n_path);
}

int	ft_changedir(const char *dir)
{
	t_list	*head;

	head = g_sh.env;
	if (!dir)
		return (1);
	if (chdir(dir) == -1)
		return (-1);
	else
	{
		while (g_sh.env)
		{
			if (ft_strncmp("PWD=", (char *)g_sh.env->data, 4) == 0)
			{
				update_env();
				g_sh.env = head;
				return (0);
			}
			g_sh.env = g_sh.env->next;
		}
	}
	return (1);
}
