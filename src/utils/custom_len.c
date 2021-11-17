#include <sh.h>

int	custom_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '=')
		i++;
	return (i);
}
