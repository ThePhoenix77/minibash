/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 09:09:41 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 15:36:21 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_global *global, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == SUCCESS)
		return (ft_echo(global, cmd), SUCCESS);
	else if (ft_strcmp(cmd[0], "cd") == SUCCESS)
		return (ft_cd(global, cmd), SUCCESS);
	else if (ft_strcmp(cmd[0], "pwd") == SUCCESS)
		return (ft_pwd(global), SUCCESS);
	else if (ft_strcmp(cmd[0], "export") == SUCCESS)
		return (ft_export(global, cmd), SUCCESS);
	else if (ft_strcmp(cmd[0], "unset") == SUCCESS)
		return (ft_unset(global, cmd), SUCCESS);
	else if (ft_strcmp(cmd[0], "env") == SUCCESS)
		return (ft_env(global), SUCCESS);
	else if (ft_strcmp(cmd[0], "exit") == SUCCESS)
		return (ft_exit(global, cmd), SUCCESS);
	else
		return (FAILURE);
}

void	check_file_type(char **cmd)
{
	struct stat	file_struct;

	if (lstat(cmd[0], &file_struct) == -1)
		(perror("minishell: lstat"), exit(1));
	if (S_ISDIR(file_struct.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	if (!(file_struct.st_mode & S_IXUSR))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd[0], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
}

int	execute_cmd(t_global *global, char **cmd, t_type_node type)
{
	if (type == BUILTIN)
	{
		check_builtins(global, cmd);
		exit (global->exit_status);
	}
	if (cmd[0][0] == '\x02')
	{
		global->exit_status = 127;
		ft_cmd_err(cmd[0]);
	}
	if (access(cmd[0], F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		(perror(cmd[0]), exit(127));
	}
	check_file_type(cmd);
	if (execve(cmd[0], cmd, global->myenv) == -1)
		perror("minishell: execve:");
	exit(1);
}
