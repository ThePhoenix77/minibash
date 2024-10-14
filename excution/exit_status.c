/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:45:40 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 16:13:14 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status(int status, t_global *global)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WTERMSIG(status) != SIGINT)
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			reset_tty(global);
			printf("Quit: ");
			printf("%d", WTERMSIG(status));
		}
	}
	printf("\n");
	return (128 + WTERMSIG(status));
}

int	close_pipe(int *pipe)
{
	if (close(pipe[0]) < 0)
		return (-1);
	if (close(pipe[1]) < 0)
		return (-1);
	return (2);
}

void	sig_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_hnd(void)
{
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, signals_handler);
}
