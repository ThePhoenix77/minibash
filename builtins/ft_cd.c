/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 09:32:38 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/10 17:39:12 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *content)
{
	char	*equal_sign;

	equal_sign = ft_strchr(content, '=');
	if (!equal_sign)
		return (NULL);
	return (equal_sign + 1);
}

char	*get_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}

void	set_oldpwd(t_global *global, char *the_pwd)
{
	t_env_list	*old_tmp;
	char		*old_tmp_val;

	old_tmp = find_var(global->env_list, "OLDPWD");
	if (!old_tmp)
	{
		add_or_update_env_var(global, "OLDPWD", "", SHOW);
		return ;
	}
	old_tmp_val = ft_strdup(old_tmp->content + 7);
	if (old_tmp_val)
	{
		if (old_tmp_val[0] == '\0')
			add_or_update_env_var(global, "OLDPWD", the_pwd, SHOW);
		else
			add_or_update_env_var(global, "OLDPWD", "", SHOW);

		free(old_tmp_val);
	}
}

void	update_oldpwd(t_global *global, char *the_pwd)
{
	t_env_list	*tmp;
	char		*old_pwd;

	tmp = find_var(global->env_list, "PWD");
	if (tmp)
	{
		old_pwd = ft_strdup(tmp->content + 4);
		if (old_pwd)
		{
			add_or_update_env_var(global, "OLDPWD", old_pwd, HIDE);
			free(old_pwd);
		}
	}
	else
		set_oldpwd(global, the_pwd);
}

char	*get_home_path(t_global *global)
{
	t_env_list	*home;
	char		*home_p;

	home = find_var(global->env_list, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		global->exit_status = 1;
		return (NULL);
	}
	home_p = get_env_value(home->content);
	if (!home_p)
	{
		ft_putstr_fd("cd: HOME value is invalid\n", STDERR_FILENO);
		global->exit_status = 1;
		return (NULL);
	}
	return (home_p);
}

void	handle_dash(t_global *global, char *the_pwd)
{
	if (oldpwd_check(global) == 1)
	{
		free(the_pwd);
		return ;
	}
	change_to_oldpwd(global);
	update_oldpwd(global, the_pwd);
	update_pwd(global);
	global->exit_status = 0;
	free(the_pwd);
}

void	handle_cd_path(t_global *global, char *new_p, char *the_pwd)
{
	if (chdir(new_p) != 0)
	{
		err_msg(&new_p);
		perror("");
		global->exit_status = 1;
		free(the_pwd);
		return ;
	}
	update_oldpwd(global, the_pwd);
	update_pwd(global);
	global->exit_status = 0;
	free(the_pwd);
}

void	ft_cd(t_global *global, char **args)
{
	char	*new_p;
	char	*the_pwd;

	the_pwd = get_pwd();
	if (!the_pwd)
		return ;
	if (args[1] && ft_strcmp(args[1], "-") == SUCCESS)
	{
		handle_dash(global, the_pwd);
		return ;
	}
	if (args[1])
		new_p = args[1];
	else
		new_p = get_home_path(global);
	if (!new_p || ft_strcmp(new_p, "") == SUCCESS)
	{
		free(the_pwd);
		return ;
	}
	handle_cd_path(global, new_p, the_pwd);
}
