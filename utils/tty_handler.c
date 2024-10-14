/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tty_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:15:25 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 16:51:42 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_tty(t_global *global)
{
	if (tcgetattr(STDIN_FILENO, &global->t_termios) == -1)
	{
		perror("minishell: tcgetattr");
		malloc_failed(global);
	}
}

void	reset_tty(t_global *global)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &global->t_termios) == -1)
	{
		perror("minishell: tcsetattr");
		malloc_failed(global);
	}
}

void	malloc_failed(t_global *global)
{
	free_memory(global);
	if (global->content)
		free(global->content);
	if (global->env_list)
		free_env_list(&global->env_list);
	global->exit_status = 1;
	exit(1);
}
