/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:14:12 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 15:34:26 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree	*new_tree_node(t_global *global, t_type_node type)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (!new)
		malloc_failed(global);
	new->type = type;
	new->fds.in = -1;
	new->fds.out = -1;
	new->cmd_args = NULL;
	new->redir = NULL;
	new->right = NULL;
	new->left = NULL;
	return (new);
}

void	free_tree(t_tree **root)
{
	if (*root == NULL)
		return ;
	free_tree(&(*root)->left);
	free_tree(&(*root)->right);
	if ((*root)->cmd_args)
		free_2d_array(&(*root)->cmd_args);
	if ((*root)->redir)
		free_redir_list(&(*root)->redir);
	free(*root);
	*root = NULL;
}

void	remove_node(t_exc_list **old)
{
	t_exc_list	*save;

	save = *old;
	*old = (*old)->next;
	if (save->cmd_args)
		free_cmd_list(&save->cmd_args);
	free(save);
}

void	last_nodes(t_global *global, t_tree *root, t_exc_list **end)
{
	root->left = new_tree_node(global, (*end)->type);
	if (*end && (*end)->cmd_args)
		root->left->cmd_args = get_args_arr(global,
				(*end)->cmd_args, (*end)->type);
	if (*end && (*end)->redir)
	{
		root->left->redir = (*end)->redir;
		(*end)->redir = NULL;
	}
	remove_node(end);
	global->exc_size--;
	root->right = new_tree_node(global, (*end)->type);
	if (*end && (*end)->cmd_args)
		root->right->cmd_args = get_args_arr(global,
				(*end)->cmd_args, (*end)->type);
	if (*end && (*end)->redir)
	{
		root->right->redir = (*end)->redir;
		(*end)->redir = NULL;
	}
	remove_node(end);
	global->exc_size--;
}

t_tree	*build_tree(t_global *global, t_exc_list **old)
{
	t_tree	*root;

	root = new_tree_node(global, PIPE_LINE);
	if (global->exc_size > 2)
	{
		root->left = new_tree_node(global, (*old)->type);
		if ((*old)->cmd_args)
			root->left->cmd_args = get_args_arr(global,
					(*old)->cmd_args, (*old)->type);
		if ((*old)->redir)
		{
			root->left->redir = (*old)->redir;
			(*old)->redir = NULL;
		}
		remove_node(old);
		global->exc_size--;
		root->right = build_tree(global, old);
	}
	else
		last_nodes(global, root, old);
	return (root);
}
