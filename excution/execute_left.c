/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_left.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:49:16 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 11:33:52 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_left(t_global *global, t_tree *root, int *pipe)
{
	if (root->left->redir)
	{
		if (handle_redirection(root->left->redir, &root->left->fds) == SUCCESS)
		{
			if (root->left->fds.in != -1)
			{
				if (dup2(root->left->fds.in, 0) < 0)
					return (perror("minishell: dup2:"), -1);
				close(root->left->fds.in);
			}
			if (root->left->fds.out != -1)
			{
				if (dup2(root->left->fds.out, 1) < 0)
					return (perror("minishell: dup2:"), -1);
				(close(root->left->fds.out), execute_tree(global, root->left));
				return (close_pipe(pipe), SUCCESS);
			}
		}
	}
	if (dup2(pipe[1], 1) < 0)
		return (perror("minishell: dup2:"), -1);
	close(pipe[1]);
	close(pipe[0]);
	execute_tree(global, root->left);
	return (SUCCESS);
}
