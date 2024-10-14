/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:12:23 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 16:12:45 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	create_child(t_global *global, char **cmd_ars)
{
	int	child;

	child = fork();
	if (child < 0)
		return (perror("minishell: fork:"), FAILURE);
	(sig_ign(), save_tty(global));
	if (child == 0)
	{
		sig_dfl();
		handle_redir_once(global);
		if (global->root->cmd_args)
		{
			if (cmd_ars[0] && cmd_ars[0][0] == '\x02')
			{
				global->exit_status = 127;
				ft_cmd_err(cmd_ars[0]);
			}
			execute_cmd(global, cmd_ars, global->root->type);
		}
		exit(0);
	}
	waitpid(child, &global->exit_status, 0);
	global->exit_status = exit_status(global->exit_status, global);
	(signal(SIGINT, signals_handler), signal(SIGQUIT, signals_handler));
	return (SUCCESS);
}

int	execute_one_cmd(t_global *global)
{
	char	**cmd_ars;

	cmd_ars = NULL;
	if (global->root->cmd_args)
		cmd_ars = get_args_arr(global, global->root->cmd_args,
				global->root->type);
	if (execute_one_builtin(global, cmd_ars, global->root) == SUCCESS)
		return (free_2d_array(&cmd_ars), SUCCESS);
	create_child(global, cmd_ars);
	free_2d_array(&cmd_ars);
	return (SUCCESS);
}
