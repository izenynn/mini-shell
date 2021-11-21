/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpoveda- <me@izenynn.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:24:41 by dpoveda-          #+#    #+#             */
/*   Updated: 2021/11/21 19:09:52 by dpoveda-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/*void execute_simple_command(ASTreeNode* simple_cmd_node,
                             bool async,
                             bool stdin_pipe,
                             bool stdout_pipe,
                             int pipe_read,
                             int pipe_write,
                             char* redirect_in,
                             char* redirect_out
                            )
{
    CommandInternal cmdinternal;
    init_command_internal(simple_cmd_node, &cmdinternal, async, stdin_pipe, stdout_pipe,
                          pipe_read, pipe_write, redirect_in, redirect_out
                         );
	execute_command_internal(&cmdinternal);
	destroy_command_internal(&cmdinternal);
}

void execute_command(ASTreeNode* cmdNode,
                      bool async,
                      bool stdin_pipe,
                      bool stdout_pipe,
                      int pipe_read,
                      int pipe_write)
{
    if (cmdNode == NULL)
        return;

    switch (NODETYPE(cmdNode->type))
    {
    case NODE_REDIRECT_IN:		// right side contains simple cmd node
        execute_simple_command(cmdNode->right,
                               async,
                               stdin_pipe,
                               stdout_pipe,
                               pipe_read,
                               pipe_write,
                               cmdNode->szData, NULL
                              );
        break;
    case NODE_REDIRECT_OUT:		// right side contains simple cmd node
        execute_simple_command(cmdNode->right,
                               async,
                               stdin_pipe,
                               stdout_pipe,
                               pipe_read,
                               pipe_write,
                               NULL, cmdNode->szData
                              );
        break;
    case NODE_CMDPATH:
        execute_simple_command(cmdNode,
                               async,
                               stdin_pipe,
                               stdout_pipe,
                               pipe_read,
                               pipe_write,
                               NULL, NULL
                              );
        break;
    }
}

void execute_pipeline(ASTreeNode* t, bool async)
{
    int file_desc[2];

    pipe(file_desc);
    int pipewrite = file_desc[1];
    int piperead = file_desc[0];

	// read input from stdin for the first job
    execute_command(t->left, async, false, true, 0, pipewrite);
    ASTreeNode* jobNode = t->right;

    while (jobNode != NULL && NODETYPE(jobNode->type) == NODE_PIPE)
    {
        close(pipewrite); // close the write end
        pipe(file_desc);
        pipewrite = file_desc[1];

        execute_command(jobNode->left, async, true, true, piperead, pipewrite);
        close(piperead);
        piperead = file_desc[0];

        jobNode = jobNode->right;
    }

    piperead = file_desc[0];
    close(pipewrite);
	
	// write output to stdout for the last job
    execute_command(jobNode, async, true, false, piperead, 0);	// only wait for the last command if necessary
    close(piperead);
}*/

/* interpret simple cmd */
static void	simple_cmd()
{
	;
}

/* interpret cmd */
static void	exec_cmd()
{
	;
}

/* interpret pipe */
static void	exec_pipe(t_ast *ast, t_bool async)
{
	;
}

/* interpret job */
static void	exec_job(t_ast *ast, t_bool async)
{
	if (ast == NULL)
		return ;
	if (ast_gettype(ast) == AST_PIPE)
		exec_pipe(ast, async);
	else
		exec_cmd(ast, async, FALSE, FALSE, 0, 0);
}

/* interpret command line */
static void	exec_cmd_line(t_ast *ast)
{
	if (ast == NULL)
		return ;
	if (ast_gettype(ast) == AST_SEQ)
	{
		exec_job(ast->left, FALSE);
		exec_cmd_line(ast->right);
	}
	else if (ast_gettype(ast) == AST_BG)
	{
		exec_job(ast->right, TRUE);
		exec_cmd_line(ast->right);
	}
	else
		exec_job(ast, FALSE);
}

/* execute syntax tree */
void	exec_ast(t_ast *ast)
{
	exec_cmd_line(ast);
}
