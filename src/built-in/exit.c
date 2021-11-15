#include <sh.h>

void	ft_exit(int exit_code)
{
	if (exit_code == -999)
		exit(0);
	g_sh.status = exit_code;
	exit(exit_code);
}
