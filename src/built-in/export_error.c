#include <sh.h>

int	error_handle(char *new_env)
{
	if ((new_env[0] >= 'A' && new_env[0] <= 'Z')
		|| (new_env[0] >= 'a' && new_env[0] <= 'z')
		|| new_env[0] == '_')
		return (0);
	else
	{
		write(STDERR_FILENO, "export: ", 8);
		write(STDERR_FILENO, new_env, ft_strlen(new_env));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, "not a valid identifier\n", 23);
	}
	return (1);
}
