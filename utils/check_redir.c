/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 08:52:51 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 19:54:36 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_af_sp(char *inp)
{
	int	i;

	i = 0;
	while (inp[i])
	{
		if (inp[i] == ' ')
		{
			while (inp[i] && inp[i] == ' ')
				i++;
			if (inp[i] == '\0')
				return (SUCCESS);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

void	set_error(t_global *global, t_lst *node)
{
	if (node->content)
		free(node->content);
	node->content = ft_strdup("minishell: ambiguous redirect");
	if (!node->content)
		malloc_failed(global);
	node->type = ERROR_DIS;
}

void	check_redir(t_global *global)
{
	t_lst	*tmp;

	tmp = global->head;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == DREDIR_OUT)
		{
			if (tmp->next->type == WHITE_SPACE)
				tmp = tmp->next->next;
			else
				tmp = tmp->next;
			if (tmp->state == GENERAL && (tmp->type == ENV_SPL
					|| tmp->type == ENV))
			{
				if (check_af_sp(tmp->content) == FAILURE
					|| !tmp->content || !tmp->content[0])
					set_error(global, tmp);
			}
		}
		tmp = tmp->next;
	}
}
