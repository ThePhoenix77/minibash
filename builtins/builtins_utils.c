/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:32:23 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/07 20:51:31 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_ptr;

	dest_ptr = dest;
	while (*src)
	{
		*dest_ptr++ = *src++;
	}
	*dest_ptr = '\0';
	return (dest);
}

void	export_without_args(t_global *global)
{
	t_env_list	*tmp;
	char		*equal_sign;

	tmp = global->env_list;
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		equal_sign = ft_strchr(tmp->content, '=');
		if (equal_sign)
		{
			write(1, tmp->content, equal_sign - tmp->content);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(equal_sign + 1, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
		{
			ft_putstr_fd(tmp->content, 1);
			ft_putstr_fd("\n", 1);
		}
		tmp = tmp->next;
	}
}

t_env_list	*find_var(t_env_list *env_list, char *key)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	while (env_list)
	{
		if (ft_strncmp(env_list->content, key, key_len) == 0
			&& (env_list->content[key_len] == '='
				|| env_list->content[key_len] == '\0'))
			return (env_list);
		env_list = env_list->next;
	}
	return (NULL);
}

int	is_valid_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	name_checker(char *s)
{
	int	i;

	i = 0;
	if (!s || s[0] == '\0')
		return (-1);
	if (!ft_isalpha(s[0]) && s[0] != '_')
		return (-1);
	while (s[i] && s[i] != '=' && !(s[i] == '+' && s[i + 1] == '='))
	{
		if (!is_valid_name_char(s[i]))
			return (-1);
		i++;
	}
	if (s[i] == '+' && s[i + 1] == '=' && i == 0)
		return (-1);
	return (0);
}
