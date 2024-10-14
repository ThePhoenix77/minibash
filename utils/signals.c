/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 07:52:43 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 20:15:30 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_exit_status = 1;
	}
	else if (sig == SIGQUIT)
		signal(SIGQUIT, SIG_IGN);
}

void	exit_status_update(t_global *global)
{
	if (g_exit_status == 1)
	{
		global->exit_status = g_exit_status;
		g_exit_status = 0;
	}
}

void	mask_and_catch_signals(t_sigaction *sig)
{
	sig->sa_handler = signals_handler;
	sigemptyset(&sig->sa_mask);
	sigaddset(&sig->sa_mask, SIGINT);
	sigaddset(&sig->sa_mask, SIGQUIT);
	sigaction(SIGINT, sig, NULL);
	sigaction(SIGQUIT, sig, NULL);
}

void	init_sigaction(void)
{
	t_sigaction	sig;

	ft_memset(&sig, 0, sizeof(sig));
	mask_and_catch_signals(&sig);
	rl_catch_signals = 0;
}
