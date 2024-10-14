/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:27:23 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 15:35:55 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pre_list(t_global *global)
{
	t_lst	*new;

	new = new_node(global);
	new->content = ft_strdup(global->content);
	if (!global->content)
	{
		free(new);
		malloc_failed(global);
	}
	new->type = global->type;
	new->state = global->state;
	add_back(&global->pre_head, &new);
	if (global->content)
		free(global->content);
	global->content = NULL;
}

void	split_env(t_global *global, t_lst *tmp)
{
	char	**spl_env;
	int		i;

	i = 0;
	spl_env = ft_split(tmp->content, ' ');
	if (!spl_env)
		malloc_failed(global);
	while (spl_env[i])
	{
		global->content = ft_strdup(spl_env[i]);
		if (!global->content)
			malloc_failed(global);
		global->type = WORD;
		global->state = GENERAL;
		add_pre_list(global);
		i++;
	}
	free_2d_array(&spl_env);
}

bool	join_cont2(t_global *global, t_lst *tmp)
{
	t_lst	*last_pnode;
	int		len;
	char	*save;

	last_pnode = last_node(global->pre_head);
	if (!last_pnode)
		return (FAILURE);
	len = ft_strlen_un_char(tmp->next->content, ' ');
	save = ft_substr(tmp->next->content, 0, len);
	if (!save)
		malloc_failed(global);
	update_line(&tmp->next->content, len, global);
	global->content = ft_strjoin2(last_pnode->content, save);
	if (!global->content)
		malloc_failed(global);
	if (last_pnode)
		free(last_pnode);
	if (save)
		free(save);
	last_pnode->content = global->content;
	global->content = NULL;
	return (SUCCESS);
}

int	join_cont(t_global *global, t_lst *tmp)
{
	t_lst	*node;

	if (!tmp->next || tmp->next->state == GENERAL)
		return (FAILURE);
	if (tmp->next->type == WORD || tmp->next->type == ENV)
	{
		node = last_node(global->pre_head);
		if (!node || !(node->content || tmp->next->content))
			return (FAILURE);
		global->content = ft_strjoin2(node->content, tmp->next->content);
		if (!global->content)
			malloc_failed(global);
		free(node->content);
		node->content = global->content;
		return (3);
	}
	if (tmp->next->type == ENV_SPL)
		join_cont2(global, tmp);
	return (SUCCESS);
}

void	bulid_list_exc(t_global *global)
{
	t_lst		*mv_node;
	t_lst		*save;

	mv_node = global->pre_head;
	save = global->pre_head;
	while (mv_node)
	{
		if (mv_node->type == PIPE)
			mv_node = mv_node->next;
		create_node(global, &mv_node);
	}
}
