/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:04:55 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 11:05:08 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_list_size(t_global *global)
{
	int			list_size;
	t_env_list	*tmp;

	list_size = 0;
	tmp = global->env_list;
	while (tmp)
	{
		list_size++;
		tmp = tmp->next;
	}
	return (list_size);
}

void	env_list_2d_array(t_global *global)
{
	int			list_size;
	t_env_list	*tmp;
	int			i;

	list_size = env_list_size(global);
	tmp = global->env_list;
	i = 0;
	global->myenv = (char **)malloc(sizeof(char *) * (list_size + 1));
	if (!global->myenv)
		malloc_failed(global);
	while (tmp)
	{
		global->myenv[i] = ft_strdup(tmp->content);
		if (!global->myenv[i])
			malloc_failed(global);
		i++;
		tmp = tmp->next;
	}
	global->myenv[list_size] = NULL;
}
