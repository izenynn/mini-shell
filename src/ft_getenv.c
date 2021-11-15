#include <minishell.h>

const char	*ft_get_env(const char *path)
{
	int	i;
	int	path_size;
	int	c_len;

	i = -1;
	path_size = ft_strlen(path);
	while (sh.env[++i])
	{
		c_len = ft_strlen(sh.env[i]);
		if (ft_strncmp(path, sh.env[i], ft_strlen(path)) == 0)
			return (ft_substr(sh.env[i], path_size, (c_len - path_size)));
	}
	return (NULL);
}
