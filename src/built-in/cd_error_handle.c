#include <sh.h>

void	print_error(const char *dir)
{
	write(STDERR_FILENO, "cd: no such file or directory: ",
		  ft_strlen("cd: no such file or directory: "));
	write(STDERR_FILENO, dir, ft_strlen(dir));
	write(STDERR_FILENO, "\n", 1);
	g_sh.status = 1;
}
