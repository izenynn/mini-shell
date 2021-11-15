#include <sh.h>

int ft_changedir(const char *dir)
{
	if (!dir)
		return (1);
	if (chdir(dir) == -1)
		return (-1);
	else
		return (0);	
}
