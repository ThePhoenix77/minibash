/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:30:02 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 12:53:56 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_failed(t_global *global)
{
	perror("minishell: fork");
	close_pipe(global->pipe);
}

void	wiat_childs(t_global *global, pid_t child1, pid_t child2)
{
	int	status;

	status = 0;
	close_pipe(global->pipe);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	global->exit_status = exit_status(status, global);
	sig_hnd();
}

int	execute_pipe(t_global *global, t_tree *root)
{
	pid_t	child1;
	pid_t	child2;

	if (pipe(global->pipe) < 0)
		return (perror("minishell: pipe:"), -1);
	child1 = fork();
	if (child1 == -1)
		return (fork_failed(global), -1);
	sig_ign();
	if (child1 == 0)
	{
		sig_dfl();
		(execute_left(global, root, global->pipe), exit(global->exit_status));
	}
	child2 = fork();
	if (child2 == -1)
		return (fork_failed(global), -1);
	if (child2 == 0)
	{
		sig_dfl();
		(execute_right(global, root, global->pipe), exit(global->exit_status));
	}
	else
		wiat_childs(global, child1, child2);
	return (1);
}

int	execute_tree(t_global *global, t_tree *root)
{
	if (root->type == PIPE_LINE)
		return (execute_pipe(global, root));
	else
		return (execute_cmd(global, root->cmd_args, root->type));
}
