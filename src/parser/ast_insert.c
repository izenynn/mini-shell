/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:21:20 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/03 13:07:34 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/* insert and ast node */
void	ast_insert(t_ast *root, t_ast *node, t_bool on_right)
{
	t_ast	*aux;

	if (root == NULL || node == NULL)
		return ;
	if (on_right)
	{
		aux = root->right;
		root->right = node;
		node->right = aux;
		node->left = NULL;
	}
	else
	{
		aux = root->left;
		root->left = node;
		node->left = aux;
		node->right = NULL;
	}
}
