/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:32:50 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/12 10:05:37 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (result > (LONG_MAX - (*str - '0')) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			else
				return (LONG_MIN);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

char	*trim_whitespace(char *str)
{
	int		start;
	int		end;

	start = 0;
	while (str[start] && ft_isspace2(str[start]))
		start++;
	end = ft_strlen(str) - 1;
	while (end > start && ft_isspace2(str[end]))
		end--;
	return (ft_substr(str, start, end - start + 1));
}

int	is_valid_number(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	exit_error(t_global *global, char *arg)
{
	ft_putstr_fd("exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	global->exit_status = 255;
	exit(255);
}

void	ft_exit(t_global *global, char **args)
{
	char	*trimmed_arg;
	long	ex_status;

	if (global->root)
		ft_putstr_fd("exit\n", 1);
	if (!args[1])
		exit(global->exit_status);
	trimmed_arg = trim_whitespace(args[1]);
	if (!is_valid_number(trimmed_arg))
		exit_error(global, args[1]);
	ex_status = ft_atol(trimmed_arg);
	free(trimmed_arg);
	if (ex_status < 0 || ex_status > 255)
		ex_status = ex_status % 256;
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
		global->exit_status = 1;
		return ;
	}
	global->exit_status = ex_status;
	exit(ex_status);
}
