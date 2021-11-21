/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:12:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/21 16:30:38 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <libft/ft_lst.h>

/*** PROTOTYPES ***/

/* sig_handler.c */
int		sig_init(void);

/* getenv.c */
char	*ft_getenv(const char *path);

/* custom_len.c */
int		get_var_len(const char *s);

/* list_filler.c */
t_list	*fill_list(t_list *env, char **environ);

/* init.c */
void	init_shell(void);

/* error_utils.c */
void	perror_exit(const char *s);
int		perror_ret(const char *s, int ret_code);

/* signals.c */
void	init_signals(void);

#endif
