/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 21:59:17 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/20 12:47:53 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh/ast.h"
#include <sh.h>

/* global var */
t_sh	g_sh;

/*********************************************************/
#define COUNT 10
// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(t_ast *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("t: %d\n", root->type);
	if (root->type == AST_CMD || root->type == AST_ARG)
		printf("s: %s\n", root->data);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(t_ast *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}
/*********************************************************/

void print_ast(t_ast *ast)
{
	if (ast == NULL)
		return ;
	printf("-------------------------------------------\n");
	printf("type: %d\n", ast->type);
	if (ast->type & AST_DATA)
		printf("data: %s\n", ast->data);
	printf("left: %p, right: %p\n", (void *)ast->left, (void *)ast->right);
	printf("-------------------------------------------\n");
	print_ast(ast->right);
	print_ast(ast->left);
}

/* main */
int	main(void)
{
	char	*line;
	t_lexer	lex;
	t_ast	*ast;

	/* initialise shell */
	init_shell();

	/* initialise terminal */
	init_prompt();

	/* minishell loop */
	while (1)
	{
		// TODO handle signals

		line = prompt_read_input();
		if (line == NULL || ft_strlen(line) <= 0)
			continue ;

		/* lexer */
		if (!lexer_build(line, ft_strlen(line), &lex))
			continue ;
		free(line);

		// TODO remove this, is only for tests
		t_tok *tmp;
		tmp = lex.tok_lst;
		while (tmp)
		{
			//printf("type: %d, data: %s\n", tmp->type, tmp->data);
			tmp = tmp->next;
		}

		/* parse the tokens into an abstract syntax tree */
		if (lex.n_toks == 0 || parse(&lex, &ast))
			continue ;

		print_ast(ast);
		//print2D(&ast);
		// TODO execute parse ast
		// TODO ast_del(exec_ast)
		// TODO lexer_destroy(&lex)
		// TODO free all
	}

	/* shutdown and cleanup */
	// TODO

	return (EXIT_SUCCESS);
}

/* MAIN TO TEST BUILTINS */

//int	main(void)
//{
//	extern char	**environ;
//	char		*line;
//	t_lexer		lex;
//	t_list		*env;
//
//	/* initialise lex */
//	(void)line;
//	env = NULL;
//	lex.tok_lst = NULL;
//	env = fill_list(env, environ);
//	g_sh.env = env;
//	/* initialise shell */
//	init_shell();
//
//	/* initialise terminal */
//	init_prompt();

//	/* minishell loop */
//	/*while (1)
//	{
//		line = prompt_read_input();
// 		prompt_process_input();
//
//		 TESTS
//		printf("\nline: %s\n\n", line);
//
//		/* lexer */
////		lexer_build(line, ft_strlen(line), &lex);
//
////		t_tok *tmp;
////		tmp = lex.tok_lst;
////		while (tmp)
////		{
////			printf("type: %d, data: %s\n", tmp->type, tmp->data);
////			tmp = tmp->next;
////		}
//
////		 TODO parse the tokens into an abstract syntax tree
////
//// 		TODO free all before looping again
////	}
//
//	/* shutdown and cleanup */
//// 		TODO
//	char **xport;
//	xport = malloc(sizeof(char *) * 3);
//	xport[0] = ft_strdup("a=1");
//	xport[1] = ft_strdup("b=2");
//	xport[2] = NULL;
//	ft_export(NULL);
//	printf("\n\n\n\n");
//	ft_export(xport);
//	ft_env();
//	ft_unset("b");
//	ft_env();
//	return (EXIT_SUCCESS);
//}
