/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 12:19:25 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/10 17:40:19 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*update_the_env_var(t_global *global, char *name, char *new_val)
{
	t_env_list *var;
	char	   *new_cont;
	char	   *tmp;

	var = find_var(global->env_list, name);
	if (var)
	{	
		tmp = ft_strjoin(name, "=");
		if (!tmp)
			return (NULL);		
		new_cont = ft_strjoin(tmp, new_val);
		free(tmp);
		if (!new_cont)
			return (NULL);	
		free(var->content);	
		var->content = new_cont;
		return (var->content);
	}
	return (NULL);
}

void	update_pwd(t_global *global)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return ;
	}
	update_the_env_var(global, "PWD", cwd);
	free(cwd);
}

void	change_to_oldpwd(t_global *global)
{
	t_env_list	*old_pwd;
	char		*old_pwd_value;

	old_pwd = find_var(global->env_list, "OLDPWD");
	if (!old_pwd)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		global->exit_status = 1;
		return ;
	}
	old_pwd_value = get_env_value(old_pwd->content);
	if (old_pwd_value[0] == '\0')
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		global->exit_status = 1;
		return ;
	}
	if (!old_pwd_value || chdir(old_pwd_value) != 0)
	{
		perror("cd");
		global->exit_status = 1;
		return ;
	}
	ft_putstr_fd(old_pwd_value, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
}

int	oldpwd_check(t_global *global)
{
	if (!find_var(global->env_list, "OLDPWD"))
	{
		ft_putstr_fd("cd: OLDPWD not set\n", STDERR_FILENO);
		global->exit_status = 1;
		return (1);
	}
	return (0);
}

void	err_msg(char **args)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(" : ", 2);
}
