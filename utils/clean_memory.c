/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 20:49:33 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 15:20:04 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_memory(t_global *global)
{
	if (global->head != NULL)
		free_lst(&global->head);
	if (global->line_input != NULL)
		free(global->line_input);
	if (global->exp_head != NULL)
		free_exp_list(&global->exp_head);
	if (global->pre_head != NULL)
		free_lst(&global->pre_head);
	if (global->myenv)
		free_2d_array(&global->myenv);
	if (global->pre_head)
		free_lst(&global->pre_head);
	if (global->root)
		free_exc_list(&global->root);
	if (global->root_tree)
		free_tree(&global->root_tree);
}

void	free_2d_array(char ***leaks)
{
	int	i;

	if (leaks[0] == NULL || leaks[0][0] == NULL)
		return ;
	i = 0;
	while ((*leaks)[i])
		free((*leaks)[i++]);
	free(*leaks);
	*leaks = NULL;
}

void	free_cmd_list(t_cmd_args **head)
{
	t_cmd_args	*tmp;

	while (*head)
	{
		tmp = *head;
		(*head) = (*head)->next;
		if (tmp->content)
			free(tmp->content);
		if (tmp)
			free(tmp);
	}
	*head = NULL;
}

void	free_redir_list(t_redir **head)
{
	t_redir	*tmp;

	if ((*head) == NULL)
		return ;
	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		if (tmp->file_name)
			free(tmp->file_name);
		free(tmp);
	}
	*head = NULL;
}

void	free_exc_list(t_exc_list **head)
{
	t_exc_list	*tmp;

	while (*head)
	{
		tmp = (*head);
		*head = (*head)->next;
		free_cmd_list(&tmp->cmd_args);
		free_redir_list(&tmp->redir);
		free(tmp);
	}
}
