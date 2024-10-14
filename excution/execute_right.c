/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_right.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:51:00 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 15:36:49 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	dup_right_out(t_tree *root)
{
	if (root->right->fds.out != -1)
	{
		if (dup2(root->right->fds.out, 1) < 0)
			return (perror("minishell: dup2:"), FAILURE);
		close(root->right->fds.out);
	}
	return (SUCCESS);
}

int	execute_right(t_global *global, t_tree *root, int *pipe)
{
	if (root->right->type == CMD || root->right->type == BUILTIN)
	{
		if (root->right->redir)
		{
			if (handle_redirection(root->right->redir,
					&root->right->fds) == SUCCESS)
			{
				if (dup_right_out(root) == FAILURE)
					return (-1);
				if (root->right->fds.in != -1)
				{
					if (dup2(root->right->fds.in, 0) < 0)
						return (perror("minishell: dup2:"), -1);
					close(root->right->fds.in);
					execute_tree(global, root->right);
					return (close_pipe(pipe), SUCCESS);
				}
			}
		}
	}
	if (dup2(pipe[0], 0) < 0)
		return (perror("minishell: dup2:"), -1);
	close_pipe(global->pipe);
	execute_tree(global, root->right);
	return (SUCCESS);
}
