/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_multi_redir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 14:53:51 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 15:35:18 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir	*new_coipe_list(t_redir *node)
{
	t_redir	*new;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->file_name = ft_strdup(node->file_name);
	if (!new->file_name)
	{
		free(new);
		return (NULL);
	}
	new->file_type = node->file_type;
	new->type = node->type;
	new->next = NULL;
	return (new);
}

bool	open_redir_files(t_redir *node)
{
	int	fd;

	if (node->type == REDIR_OUT)
	{
		fd = open(node->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			return (perror("minishell: open"), FAILURE);
	}
	else if (node->type == DOUBLE_QUOTE)
	{
		fd = open(node->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			return (perror("minishell: open"), FAILURE);
	}
	else if (node->type == REDIR_IN)
	{
		fd = open(node->file_name, O_RDONLY, 0644);
		if (fd < 0)
			return (perror("minishell: open"), FAILURE);
	}
	if (node->file_type == HERE_DOC_FILE)
		return (unlink(node->file_name), SUCCESS);
	else if (node->type == ERROR_DIS)
		return (SUCCESS);
	return (close(fd), SUCCESS);
}

void	add_copie_list(t_global *global, t_redir **new_head, t_redir *old)
{
	t_redir	*new;

	new = NULL;
	new = new_coipe_list(old);
	if (!new)
		(free_redir_list(new_head), malloc_failed(global));
	add_back_redir(new_head, new);
}

bool	check_doubel_redir(t_global *global, t_redir **redir_list)
{
	t_redir	*tmp;
	t_redir	*new_head;

	new_head = NULL;
	tmp = *redir_list;
	while (tmp)
	{
		while (tmp->next && (tmp->type == tmp->next->type)
			&& (tmp->file_type != ERROR_DIS))
		{
			if (open_redir_files(tmp) == FAILURE)
				return (free_redir_list(&new_head), FAILURE);
			tmp = tmp->next;
		}
		add_copie_list(global, &new_head, tmp);
		if (tmp->file_type == ERROR_DIS)
			break ;
		tmp = tmp->next;
	}
	free_redir_list(redir_list);
	*redir_list = new_head;
	return (SUCCESS);
}
