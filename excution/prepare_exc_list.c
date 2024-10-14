/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_exc_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:57:24 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 13:59:58 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_node(t_global *global, t_lst **node)
{
	t_redir		*new_rd_node;
	t_exc_list	*new_exc_node;

	new_exc_node = new_exc_spot(global, CMD);
	add_back_exc(&global->root, new_exc_node);
	while ((*node) && (*node)->type != PIPE)
	{
		while (*node && ((*node)->type == WORD || (*node)->type == ENV))
			add_list_cmd(global, new_exc_node, node);
		if (*node && ((*node)->type == REDIR_IN
				|| (*node)->type == REDIR_OUT
				|| (*node)->type == DREDIR_OUT))
		{
			new_rd_node = new_vertex(global, *node);
			add_back_redir(&new_exc_node->redir, new_rd_node);
			*node = (*node)->next->next;
			while (*node && ((*node)->type == WORD || (*node)->type == ENV))
				add_list_cmd(global, new_exc_node, node);
		}
	}
}
