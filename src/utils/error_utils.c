/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:45:54 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/26 17:04:02 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* exit printint perror */
void	perror_exit(const char *s)
{
	if (s)
		perror(s);
	exit(EXIT_FAILURE);
}

/* return with custom error code */
int	perror_ret(const char *s, int ret_code)
{
	if (s)
		perror(s);
	return (ret_code);
}

/* return with custom error code */
int	error_ret(const char *s, int ret_code)
{
	write(STDERR_FILENO, s, ft_strlen(s));
	return (ret_code);
}
