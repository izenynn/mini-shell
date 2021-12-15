/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 11:21:20 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/12/14 00:34:09 by dpoveda-         ###   ########.fr       */
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

/* insert "and or" node on top */
void	ast_insert_and_or(t_ast **root, t_ast *new_root, t_bool last)
{
	if (root == NULL || new_root == NULL)
		return ;
	if (*root == NULL)
	{
		*root = new_root;
	}
	else
	{
		if (last == FALSE)
		{
			(*root)->right = new_root->left;
			new_root->left = (*root);
			*root = new_root;
		}
		else
		{
			(*root)->right = new_root;
		}
	}
}
