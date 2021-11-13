/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 12:12:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/13 12:14:50 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*** PROTOTYPES ***/

/* utils/init.c */
void	init_shell(void);

/* utils/error_utils.c */
void	perror_exit(const char *s);

/* utils/signals.c */
void	init_signals(void);

#endif
