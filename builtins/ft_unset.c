/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:33:00 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/02 16:13:47 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_is_valid(char *str)
{
	int	i;

	i = 1;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	remove_env_node(t_global *global, t_env_list *node)
{
	if (node->prev)
		node->prev->next = node->next;
	else
		global->env_list = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->content);
	free(node);
}

void	ft_unset(t_global *global, char **args)
{
	t_env_list	*env_var;
	int			i;

	i = 1;
	global->exit_status = 0;
	while (args[i])
	{
		if (!unset_is_valid(args[i]))
		{
			ft_putstr_fd("unset: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			global->exit_status = 1;
		}
		else
		{
			env_var = find_var(global->env_list, args[i]);
			if (env_var)
				remove_env_node(global, env_var);
		}
		i++;
	}
}
