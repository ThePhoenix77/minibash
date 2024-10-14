/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 07:10:58 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/09 09:35:46 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

void	get_line(t_global *global)
{
	read_history(HISTORY_FILE);
	while (1)
	{
		global->line_input = readline("minishell-1.0$ ");
		if (check_valid_in(global) == SUCCESS)
			continue ;
		if (check_valid_in(global) == FAILURE)
		{
			free_memory(global);
			if (global->env_list)
				free_env_list(&global->env_list);
			write(1, "\x1B[Fminishell-1.0$ exit\n", 24);
			g_exit_status = 0;
			break ;
		}
		exit_status_update(global);
		(add_history(global->line_input), skip_ec_t(global, 0));
		if (check_valid_in(global) == SUCCESS)
			continue ;
		if (start(global) == FAILURE)
			continue ;
		free_memory(global);
	}
	write_history(HISTORY_FILE);
}

bool	start(t_global *global)
{
	global->type = WORD;
	global->state = GENERAL;
	ft_tokeniz(global);
	if (check_syntax(global) == FAILURE)
	{
		free_memory(global);
		return (FAILURE);
	}
	if (check_num_heredoc(global) == FAILURE)
	{
		ft_putstr_fd(ERR_MANY_HERDOCS, 2);
		free_memory(global);
		if (global->env_list)
			free_env_list(&global->env_list);
		global->exit_status = 2;
		exit(global->exit_status);
	}
	if (check_heredoc(global) == FAILURE)
		return (free_memory(global), FAILURE);
	if (check_expand(global) == FAILURE)
		return (free_memory(global), FAILURE);
	(main_exp_fun(global), check_redir(global));
	(open_heredoc_file(global), main_exc(global));
	return (SUCCESS);
}

int	main(int arc, char **arv, char **env)
{
	t_global	global;

	arc = 0;
	arv = NULL;
	if (isatty(0) == 0)
		return (-1);
	init_sigaction();
	init_global(&global, env);
	if (check_env(&global) == FAILURE)
		malloc_failed(&global);
	get_line(&global);
	clear_history();
}
