/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 18:49:25 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 11:19:54 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exc_list	*new_exc_spot(t_global *global, t_type_node type)
{
	t_exc_list	*new;

	new = (t_exc_list *)malloc(sizeof(t_exc_list));
	if (!new)
		malloc_failed(global);
	new->type = type;
	new->redir = NULL;
	new->next = NULL;
	new->fd.in = -1;
	new->fd.out = -1;
	new->cmd_args = NULL;
	return (new);
}

t_exc_list	*last_exc_node(t_exc_list *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	add_back_exc(t_exc_list **head, t_exc_list *new)
{
	t_exc_list	*last_node;

	if (!new && !(*head))
		return ;
	if (!(*head))
		*head = new;
	else
	{
		last_node = last_exc_node((*head));
		last_node->next = new;
	}
}

int	exc_list_size(t_exc_list *exc)
{
	int	i;

	i = 0;
	while (exc)
	{
		i++;
		exc = exc->next;
	}
	return (i);
}
