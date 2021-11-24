/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:12:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/24 18:58:58 by acostal-         ###   ########.fr       */
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

/* init_utils.c  */
void	fill_env(char **env);

/* error_utils.c */
void	perror_exit(const char *s);
int		perror_ret(const char *s, int ret_code);

/* signals.c */
void	init_signals(void);

/* env_utils.c */
char	**get_env_char(void);

#endif
