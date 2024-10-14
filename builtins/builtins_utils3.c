/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:32:34 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 09:50:12 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_size(char **args)
{
	int	args_num;
	int	i;

	args_num = 0;
	i = 1;
	while (args[i] != NULL)
	{
		args_num++;
		i++;
	}
	return (args_num);
}

char	*ft_strndup(char *src, int n)
{
	int		i;
	char	*dup;

	i = 0;
	dup = (char *)malloc(n + 1);
	if (!dup)
		return (NULL);
	while (src[i] && i < n)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	existing_var_case(t_global *global, char *key)
{
	t_env_list	*existing_var;

	existing_var = find_var(global->env_list, key);
	if (!existing_var || existing_var->content == NULL)
		add_or_update_env_var(global, key, NULL, SHOW);
	free(key);
}

void	handle_key_value(t_global *global, char *content)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	size_t	key_length;

	equal_sign = ft_strchr(content, '=');
	if (equal_sign)
	{
		key_length = equal_sign - content;
		key = ft_strndup(content, key_length);
		value = ft_strdup(equal_sign + 1);
		if (key && value)
		{
			add_or_update_env_var(global, key, value, HIDE);
			free(key);
			free(value);
		}
	}
	else
	{
		key = ft_strdup(content);
		if (key)
			existing_var_case(global, key);
	}
}

void	add_export_node(t_env_list **head, t_env_list *new)
{
	t_env_list	*last;

	if (!head || !new)
		return ;
	if (*head == NULL)
		*head = new;
	else
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = new;
		new->prev = last;
	}
}
