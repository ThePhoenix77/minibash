/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exc_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:09:21 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 19:19:11 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	args_arr_size(t_cmd_args *cmd_args)
{
	int			arg_count;
	t_cmd_args	*temp;

	arg_count = 0;
	temp = cmd_args;
	while (temp)
	{
		arg_count++;
		temp = temp->next;
	}
	return (arg_count);
}

void	add_cmd_args(t_global *global, char **cmd_ars, t_cmd_args *cmd_args)
{
	int	i;

	i = 1;
	if (cmd_ars)
	{
		while (cmd_args)
		{
			cmd_ars[i] = ft_strdup(cmd_args->content);
			if (!cmd_ars[i])
			{
				perror("minishell: malloc");
				free_2d_array(&cmd_ars);
				malloc_failed(global);
			}
			i++;
			cmd_args = cmd_args->next;
		}
	}
	cmd_ars[i] = NULL;
}

char	**get_args_arr(t_global *global, t_cmd_args *cmd_args, t_type_node type)
{
	char	**args_arr;

	args_arr = (char **)malloc((args_arr_size(cmd_args) + 1) * sizeof(char *));
	if (!args_arr)
		malloc_failed(global);
	if (cmd_args->content[0] == '\0')
		args_arr[0] = ft_strdup("\x02");
	else if (type == BUILTIN)
		args_arr[0] = ft_strdup(cmd_args->content);
	else
		args_arr[0] = get_path(cmd_args->content, global);
	if (!args_arr[0] && cmd_args->content[0] != '\0')
		args_arr[0] = ft_strjoin2("\x02", cmd_args->content);
	if (!args_arr[0])
		(free(args_arr), malloc_failed(global));
	add_cmd_args(global, args_arr, cmd_args->next);
	return (args_arr);
}

void	ft_cmd_err(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(ERR_CMD_NF, 2);
	exit(127);
}

void	check_builtins_cmds(t_exc_list *exc_node)
{
	while (exc_node)
	{
		if (exc_node->cmd_args)
		{
			if (ft_strcmp(exc_node->cmd_args->content, "echo") == SUCCESS)
				exc_node->type = BUILTIN;
			else if (ft_strcmp(exc_node->cmd_args->content, "cd") == SUCCESS)
				exc_node->type = BUILTIN;
			else if (ft_strcmp(exc_node->cmd_args->content, "pwd") == SUCCESS)
				exc_node->type = BUILTIN;
			else if (ft_strcmp(exc_node->cmd_args->content, "export") == 1)
				exc_node->type = BUILTIN;
			else if (ft_strcmp(exc_node->cmd_args->content, "unset") == SUCCESS)
				exc_node->type = BUILTIN;
			else if (ft_strcmp(exc_node->cmd_args->content, "env") == SUCCESS)
				exc_node->type = BUILTIN;
			else if (ft_strcmp(exc_node->cmd_args->content, "exit") == SUCCESS)
				exc_node->type = BUILTIN;
			else
				exc_node->type = CMD;
		}
		exc_node = exc_node->next;
	}
}
