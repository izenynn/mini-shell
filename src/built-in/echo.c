#include <sh.h>

int	ft_echo(const char *str, const char *flag)
{
	if (!str)
		return (1);
	if (ft_strncmp(flag, "-n", 3) == 0)
	{
		printf("%s", str);
		return (0);
	}
	else
	{
		printf("%s\n", str);
		return (0);
	}
}
