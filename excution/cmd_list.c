/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 09:37:44 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 11:17:41 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_args	*new_cmd_element(t_global *global, char *content)
{
	t_cmd_args	*new;

	new = (t_cmd_args *)malloc(sizeof(t_cmd_args));
	if (!new)
		malloc_failed(global);
	new->next = NULL;
	new->content = ft_strdup(content);
	if (!new->content)
	{
		free(new);
		malloc_failed(global);
	}
	return (new);
}

void	add_back_element(t_cmd_args **head, t_cmd_args *new)
{
	t_cmd_args	*last;

	if (!(*head) && !new)
		return ;
	if (!(*head))
		*head = new;
	else
	{
		last = *head;
		while (last->next)
			last = last->next;
		last->next = new;
	}
}

void	store_cmd_args(t_global *global, t_lst **node)
{
	t_cmd_args	*new;
	t_exc_list	*last;

	last = last_exc_node(global->root);
	while (*node && (*node)->type == WORD)
	{
		new = (t_cmd_args *)malloc(sizeof(t_cmd_args));
		if (!new)
			malloc_failed(global);
		new->next = NULL;
		add_back_element(&last->cmd_args, new);
		new->content = ft_strdup((*node)->content);
		if (!new->content)
			malloc_failed(global);
		*node = (*node)->next;
	}
}

void	add_list_cmd(t_global *global, t_exc_list *exc, t_lst **node)
{
	t_cmd_args	*new_cmd_node;

	new_cmd_node = new_cmd_element(global, (*node)->content);
	add_back_element(&exc->cmd_args, new_cmd_node);
	(*node) = (*node)->next;
}
