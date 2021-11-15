#include <sh.h>

static void	print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
		printf("%s\n", env[i]);
}

static int	sort_env(void)
{
	int		i;
	int		j;
	char	c;
	int		n_index;
	char	**sorted_env;

	c = 'A';
	n_index = -1;
	i = 0;
	while (g_sh.env[i])
		i++;
	sorted_env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!sorted_env)
		return (-1);
	while (c >= 32 && c <= 122)
	{
		j = -1;
		while (g_sh.env[++j] != NULL)
		{
			if (g_sh.env[j][0] == c)
				sorted_env[++n_index] = ft_strdup(g_sh.env[j]);
		}
		++c;
	}
	if (sorted_env != NULL)
		print_env(sorted_env);
	return (0);
}

int	ft_export(char *new_env)
{
	int	i;
	int	env_tl;

	i = -1;
	if (!g_sh.env)
		return (-1);
	if (!new_env && g_sh.env)
		return (sort_env());
	else
	{
		env_tl = 0;
		while (g_sh.env[++i])
			env_tl += ft_strlen(g_sh.env[i]);
		g_sh.env = ft_realloc(g_sh.env, env_tl + ft_strlen(new_env) + 1);
		if (g_sh.env)
		{
			g_sh.env[i] = new_env;
			g_sh.env[i + 1] = NULL;
		}
	}
	return (0);
}
