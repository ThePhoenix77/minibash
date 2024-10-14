/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:26:18 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 11:03:26 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*get_var_env(t_global *global, char *var)
{
	t_env_list	*tmp;
	int			len;

	tmp = global->env_list;
	len = ft_strlen_un_char(var, '=') + 1;
	while (tmp)
	{
		if (ft_strncmp(var, tmp->content, len) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

bool	update_env(t_env_list **env, char *new_val)
{
	int		i;
	int		len;
	int		len_add;
	char	*res;
	char	*tmp;

	i = 0;
	len = ft_strlen_un_char((*env)->content, '=') + 1;
	len_add = ft_strlen(new_val);
	res = malloc(sizeof(char) * (len + len_add + 1));
	if (!res)
		return (FAILURE);
	ft_strlcpy(res, (*env)->content, len + 1);
	tmp = res;
	res = ft_strjoin(res, new_val);
	if (!res)
		return (FAILURE);
	free((*env)->content);
	free(new_val);
	free(tmp);
	(*env)->content = res;
	res = NULL;
	return (SUCCESS);
}

bool	empty_env(t_global *global)
{
	char		*curr_path;
	t_env_list	*new;

	curr_path = getcwd(NULL, 0);
	if (curr_path == NULL)
		return (FAILURE);
	new = new_env_node(ft_strjoin("PWD=", curr_path));
	if (!new || !new->content)
	{
		free(curr_path);
		return (FAILURE);
	}
	free(curr_path);
	add_env_back(&global->env_list, new);
	new = new_env_node(ft_strdup("SHLVL=0"));
	if (!new || !new->content)
		return (FAILURE);
	add_env_back(&global->env_list, new);
	new = new_env_node(ft_strdup("_=./minishell"));
	if (!new || !new->content)
		return (FAILURE);
	add_env_back(&global->env_list, new);
	return (SUCCESS);
}
