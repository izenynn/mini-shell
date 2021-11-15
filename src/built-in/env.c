#include <sh.h>

void	ft_env(void)
{
	int	i;

	i = -1;
	if (!g_sh.env)
		return ;
	while (g_sh.env[++i] != NULL)
		printf("%s\n", g_sh.env[i]);
}
