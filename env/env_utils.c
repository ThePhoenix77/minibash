/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 10:54:04 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/08 20:20:55 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*new_env_node(char *content)
{
	t_env_list	*new;

	new = (t_env_list *)malloc(sizeof(t_env_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_env_list	*last_env_node(t_env_list *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

void	free_env_list(t_env_list **head)
{
	t_env_list	*tmp;

	if (!(*head))
		return ;
	while ((*head))
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp->content);
		free(tmp);
	}
	*head = NULL;
}

void	add_env_back(t_env_list **head, t_env_list *new)
{
	t_env_list	*last_node;

	if (!(new))
		return ;
	if (!(*head))
		*head = new;
	else
	{
		last_node = last_env_node(*head);
		last_node->next = new;
		new->prev = last_node;
	}
}

bool	check_env(t_global *global)
{
	int			i;
	t_env_list	*new;

	i = 0;
	if (!global->env || !global->env[0])
	{
		if (empty_env(global) == FAILURE)
			return (FAILURE);
	}
	else if (global->env || global->env[0])
	{
		while (global->env[i])
		{
			if (ft_strncmp("OLDPWD=", global->env[i], 7) == 0)
				i++;
			new = new_env_node(ft_strdup(global->env[i]));
			if (!new || !new->content)
				return (FAILURE);
			add_env_back(&global->env_list, new);
			i++;
		}
	}
	if (shell_level(global) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}