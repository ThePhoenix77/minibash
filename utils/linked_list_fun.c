/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_fun.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 10:03:44 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 20:26:23 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*new_node(t_global *global)
{
	t_lst	*new;

	new = (t_lst *)malloc(sizeof(t_lst));
	if (new == NULL)
		malloc_failed(global);
	new->next = NULL;
	new->prev = NULL;
	new->content = NULL;
	new->type = WORD;
	new->state = GENERAL;
	new->len = 0;
	return (new);
}

t_lst	*last_node(t_lst *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

bool	add_back(t_lst **head, t_lst **new)
{
	t_lst	*last;

	if (*new == NULL)
		return (FAILURE);
	if (!(*head))
	{
		*head = *new;
		(*new)->next = NULL;
		(*new)->prev = NULL;
	}
	else
	{
		last = last_node(*head);
		(*new)->prev = last;
		last->next = *new;
	}
	return (SUCCESS);
}

void	free_lst(t_lst	**head)
{
	t_lst	*current;
	t_lst	*next_node;

	if (head == NULL || *head == NULL)
		return ;
	current = *head;
	while (current != NULL)
	{
		next_node = current->next;
		if (current->content)
			free(current->content);
		free(current);
		current = next_node;
	}
	*head = NULL;
}

void	add_list(t_global *global)
{
	t_lst	*new;

	new = new_node(global);
	new->content = global->content;
	new->state = global->state;
	new->type = global->type;
	new->len = ft_strlen(global->content);
	add_back(&global->head, &new);
	global->list_len++;
	global->content = NULL;
	global->type = WORD;
	global->state = GENERAL;
}
