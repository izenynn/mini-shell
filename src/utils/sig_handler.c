#include <sh.h>
/*
 * ctrl + c = 2 -> exit code = 130
 * ctrl + z = 18 -> exit code = 146
 * ctrl + \ = 3 -> exit code = 131
 * //TODO HANDLE ctrl + d
*/
//TODO set exit code on status global var
static void	sig_handler(int signum)
{
	printf("\n%d\n", signum);
	if (signum == 18)
		ft_exit(146);
	if (signum == 2)
		ft_exit(130);
	if (signum == 3)
		ft_exit(131);
}

int	sig_init(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTSTP, sig_handler);
	signal(SIGQUIT, sig_handler);
	return (0);
}
