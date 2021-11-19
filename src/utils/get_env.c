#include <sh.h>

char	*ft_get_env(const char *path)
{
	int		path_size;
	char	*ret;
	t_list	*head;

	head = g_sh.env;
	path_size = ft_strlen(path);
	while (g_sh.env)
	{
		if (ft_strncmp(path, (char *)g_sh.env->data, path_size) == 0)
		{
			ret = ft_substr((char *)g_sh.env->data, 0, path_size);
			g_sh.env = head;
			return (ret);
		}
		g_sh.env = g_sh.env->next;
	}
	return (NULL);
}
