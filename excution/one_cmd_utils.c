/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 10:00:10 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 14:33:03 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redir_one_node(t_global *global, t_exc_list **exc_node)
{
	t_redir	*redir;

	redir = (*exc_node)->redir;
	if (handle_redirection(redir, &(*exc_node)->fd) == SUCCESS)
	{
		if ((*exc_node)->fd.in != -1)
		{
			global->save_fd.in = ft_dup(global->save_fd.in, 0);
			if (global->save_fd.in < 0)
				return (FAILURE);
			if (ft_dup2((*exc_node)->fd.in, 0) == FAILURE)
				return (reset_sett(&global->save_fd), FAILURE);
		}
		if ((*exc_node)->fd.out != -1)
		{
			global->save_fd.out = ft_dup(global->save_fd.out, 1);
			if (global->save_fd.out < 0)
				return (FAILURE);
			if (ft_dup2((*exc_node)->fd.out, 1) == FAILURE)
				return (reset_sett(&global->save_fd), FAILURE);
		}
	}
	return (SUCCESS);
}

bool	execute_one_builtin(t_global *global,
		char **cmd_args, t_exc_list *exc_node)
{
	if (exc_node->type == BUILTIN)
	{
		if (exc_node->redir)
			if (redir_one_node(global, &exc_node) == FAILURE)
				return (FAILURE);
		if (exc_node->type == BUILTIN)
			check_builtins(global, cmd_args);
		reset_sett(&global->save_fd);
		return (SUCCESS);
	}
	return (FAILURE);
}

void	handle_redir_once(t_global *global)
{
	if (global->root->redir)
	{
		if (handle_redirection(global->root->redir,
				&global->root->fd) == SUCCESS)
		{
			if (global->root->fd.in > 0)
			{
				if (dup2(global->root->fd.in, 0) < 0)
					perror("minishell : dup2:");
				close(global->root->fd.in);
			}
			if (global->root->fd.out > 0)
			{
				if (dup2(global->root->fd.out, 1) < 0)
					perror("minishell : dup2:");
				close(global->root->fd.out);
			}
		}
		else
			exit (1);
	}
}
