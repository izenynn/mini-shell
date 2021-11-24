/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 00:40:12 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/24 00:41:15 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

/*** PROTOTYPES ***/

/* utils/signals.c */
void	sig_child(void);
void	sig_parent(void);
void	sig_ignore(void);

#endif
