#include <sh.h>

int	ft_unset(char *unset)
{
	int	i;
	int	env_tl;

	i = -1;
	env_tl = 0;
	if (!g_sh.env)
		return (-1);
	if (unset)
	{
		while (g_sh.env[++i])
			env_tl += ft_strlen(g_sh.env[i]);
		g_sh.env = ft_realloc(g_sh.env, env_tl + ft_strlen(unset));
		if (!g_sh.env)
			return (-1);
	}
	else
	{
		printf("%s\n", "unset: not enough arguments");
		return (-1);
	}
	return (0);
}
