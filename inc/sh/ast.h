/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 12:04:56 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/02 18:52:27 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

/*** DEFINES ***/

#include <libft/ft_bool.h>

/*** DATA ***/

typedef enum e_asttype{
	AST_PIPE =		(1 << 0),
	AST_SEQ =		(1 << 1),
	AST_REDIR =		(1 << 2),
	AST_RD_INFILE =	(1 << 3),
	AST_RD_HDOC =	(1 << 4),
	AST_RD_TRUNC =	(1 << 5),
	AST_RD_APPEND =	(1 << 6),
	AST_CMD =		(1 << 7),
	AST_SIMPLECMD =	(1 << 8),
	AST_ARG =		(1 << 9),
	AST_DATA =		(1 << 10)
}	t_asttype;

typedef struct s_ast	t_ast;

struct s_ast {
	int		type;
	char	*data;
	t_ast	*left;
	t_ast	*right;
};

/*** PROTOTYPES ***/

/* ast_utils.c */
int		ast_gettype(t_ast *ast);
void	ast_del(t_ast *ast);
void	ast_attach(t_ast *root, t_ast *left, t_ast *right);
void	ast_settype(t_ast *ast, t_asttype type);
void	ast_setdata(t_ast *ast, char *data);

/* ast_insert.c */
void	ast_insert(t_ast *root, t_ast *node, t_bool on_right);

#endif
