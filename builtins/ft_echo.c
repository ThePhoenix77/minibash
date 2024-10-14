/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:32:19 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/07 11:37:20 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_all_n(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_global *global, char **args)
{
	int	i;
	int	nl_flag;
	int	args_num;
	int	start_index;

	args_num = arg_size(args);
	nl_flag = 1;
	i = 1;
	while (args[i] && is_all_n(args[i]))
	{
		nl_flag = 0;
		i++;
	}
	start_index = i;
	i = start_index;
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (i < start_index + args_num - 1 && args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (nl_flag)
		ft_putstr_fd("\n", STDOUT_FILENO);
	global->exit_status = 0;
}
