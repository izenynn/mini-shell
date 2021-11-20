/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:12:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 13:17:07 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <libft/ft_lst.h>

/*** PROTOTYPES ***/

/* sig_handler.c */
int		sig_init(void);

/* get_env.c */
char	*ft_get_env(const char *path);

/* custom_len.c */
int		custom_len(const char *s);

/* list_filler.c */
t_list	*fill_list(t_list *env, char **environ);

/* init.c */
void	init_shell(void);

/* error_utils.c */
void	perror_exit(const char *s);

/* signals.c */
void	init_signals(void);

#endif
