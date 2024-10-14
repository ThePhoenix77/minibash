/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:32:53 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/07 21:04:38 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_key(char *arg, char *plus_equal)
{
	int	key_length;

	key_length = plus_equal - arg;
	return (ft_strndup(arg, key_length));
}

char	*concat_env_value(t_env_list *env_var, char *value, int key_length)
{
	return (ft_strjoin(env_var->content + key_length + 1, value));
}

void	plus_checker(t_global *global, char *arg)
{
	char		*plus_equal;
	char		*key;
	char		*value;
	char		*new_value;
	t_env_list	*env_var;

	plus_equal = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (!plus_equal)
		return ;
	key = extract_key(arg, plus_equal);
	value = ft_strdup(plus_equal + 2);
	env_var = find_var(global->env_list, key);
	if (env_var && value)
		new_value = concat_env_value(env_var, value, plus_equal - arg);
	else
		new_value = value;
	add_or_update_env_var(global, key, new_value, HIDE);
	free(key);
	free(value);
	if (env_var && new_value)
		free(new_value);
}

int	is_valid_identifier(char *arg)
{
	int	i;

	i = 1;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (0);
	while (arg[i] && arg[i] != '=')
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	process_export_cmd(t_global *global, char **args)
{
	int		i;
	char	*equal_pos;

	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]) || args[i][0] == '=')
		{
			ft_putstr_fd("bash: export: `", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			global->exit_status = 1;
		}
		else
		{
			equal_pos = ft_strchr(args[i], '=');
			if (equal_pos)
				(*equal_pos = '\0',
			add_or_update_env_var(global, args[i], equal_pos + 1, 0));
			else
				add_or_update_env_var(global, args[i], NULL, 0);
		}
		i++;
	}
}

void	ft_export(t_global *global, char **args)
{
	global->exit_status = 0;
	if (!args[1])
		export_without_args(global);
	else if ((name_checker(args[1])))
	{
		ft_putstr_fd("export: Invalid variable name.\n", 2);
		global->exit_status = 1;
	}
	else
		process_export_cmd(global, args);
	global->exit_status = 0;
}
