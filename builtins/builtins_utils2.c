/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:32:30 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/01 09:32:31 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_new_content(char *key, char *value)
{
	size_t	total_len;
	char	*new_content;

	if (value)
		total_len = ft_strlen(key) + ft_strlen(value) + 2;
	else
		total_len = ft_strlen(key) + 1;
	new_content = malloc(total_len);
	if (!new_content)
	{
		perror("malloc");
		return (NULL);
	}
	ft_strcpy(new_content, key);
	if (value)
	{
		new_content[ft_strlen(key)] = '=';
		ft_strcpy(new_content + ft_strlen(key) + 1, value);
	}
	return (new_content);
}

int	starts_with(char *str, char *prest)
{
	return (ft_strncmp(str, prest, ft_strlen(prest)) == 0);
}

void	update_env_var(t_env_list *env_var, char *new_content)
{
	free(env_var->content);
	env_var->content = new_content;
}

t_env_list	*create_new_node(char *new_content, int type)
{
	t_env_list	*new_node;

	new_node = malloc(sizeof(t_env_list));
	if (!new_node)
	{
		perror("malloc");
		free(new_content);
		return (NULL);
	}
	new_node->content = new_content;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->type = type;
	return (new_node);
}

void	add_or_update_env_var(t_global *global, char *key,
		char *value, int type)
{
	t_env_list	*env_var;
	char		*new_content;
	t_env_list	*new_node;

	env_var = find_var(global->env_list, key);
	new_content = create_new_content(key, value);
	if (!new_content)
		return ;
	if (env_var)
	{
		update_env_var(env_var, new_content);
		env_var->type = type;
	}
	else
	{
		new_node = create_new_node(new_content, type);
		if (new_node)
			add_export_node(&global->env_list, new_node);
	}
}
