/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_node_expn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:52:02 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 15:37:50 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	find_dollar(t_lst *node)
{
	int	i;

	i = 0;
	while (node->content[i])
	{
		if (node->content[i] == '$' && ft_is_valid_expnd(node->content[i + 1]))
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

int	tilde_exp(t_global *global, t_lst **node)
{
	t_env_list	*tmp;
	int			len;
	char		*res;
	char		*save;

	tmp = get_var_env(global, "HOME=");
	if (!tmp)
		return (FAILURE);
	res = ft_strdup(tmp->content);
	if (!res)
		malloc_failed(global);
	len = ft_strlen_un_char(res, '=') + 1;
	update_line(&res, len, global);
	if ((*node)->content[0] == '/')
	{
		save = res;
		res = ft_strjoin2(res, "/");
		free(save);
		if (!res)
			malloc_failed(global);
		update_line(&(*node)->content, 1, global);
	}
	save = (*node)->content;
	(*node)->content = ft_strjoin2(res, (*node)->content);
	return (free(save), free(res), SUCCESS);
}

bool	check_expand(t_global *global)
{
	t_lst	*tmp;

	tmp = global->head;
	while (tmp)
	{
		if ((tmp->type == WORD && tmp->state == IN_DQUOTE)
			|| (tmp->type == WORD && tmp->state == GENERAL))
		{
			if (tmp->type == WORD && tmp->state == GENERAL
				&& (tmp->content[0] == '~'
					&& (!tmp->content[1] || tmp->content[1] == '/')))
			{
				update_line(&tmp->content, 1, global);
				if (tilde_exp(global, &tmp) == FAILURE)
					return (ft_putstr_fd("Home not set\n", 2), FAILURE);
			}
			if (find_dollar(tmp) == SUCCESS)
				tmp->type = ENV;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
