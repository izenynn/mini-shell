/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:04:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/16 12:12:46 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum {
	AST_PIPE =		(1 << 0),
	AST_BG =		(1 << 1),
	AST_SEQ =		(1 << 2),
	AST_REDIR_IN =	(1 << 3),
	AST_REDIR_OUT =	(1 << 4),
	AST_CMDPATH =	(1 << 5),
	AST_ARGS =		(1 << 6),
	AST_DATA =		(1 << 7),
}	ast_type;

typedef struct s_ast	t_ast;

struct s_ast {
	int		type;
	char	*data_sz;
	t_ast	*left;
	t_ast	*right;
};

#endif
