/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:01:31 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 13:46:39 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	join_nodes(t_global *global, t_lst **node)
{
	char	*save;

	if (((*node)->type == ENV || (*node)->type == WORD)
		&& ((*node)->next && ((*node)->next->type == ENV
				|| (*node)->next->type == WORD)))
	{
		while (*node && ((*node)->type == ENV || (*node)->type == WORD))
		{
			save = ft_strjoin2(global->content, (*node)->content);
			if (!save)
				malloc_failed(global);
			if (global->content)
				free(global->content);
			global->content = save;
			*node = (*node)->next;
		}
		global->type = WORD;
		add_pre_list(global);
		return (SUCCESS);
	}
	return (FAILURE);
}

void	prepere_list(t_global *global)
{
	global->tmp = global->head;
	while (global->tmp)
	{
		if (global->tmp->type == ENV_SPL)
		{
			split_env(global, global->tmp);
			if (join_cont(global, global->tmp) == 3)
				global->tmp = global->tmp->next;
		}
		else if (global->tmp->type != WHITE_SPACE && global->tmp->type != SKIP)
		{
			if (join_nodes(global, &global->tmp) == SUCCESS)
				continue ;
			global->content = ft_strdup(global->tmp->content);
			if (global->type == ENV)
				global->type = WORD;
			global->type = global->tmp->type;
			global->state = global->tmp->state;
			add_pre_list(global);
		}
		global->tmp = global->tmp->next;
	}
}

void	cmd_msg(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(ERR_CMD_NF, 2);
}

bool	main_exc_p2(t_global *global)
{
	global->exc_size = exc_list_size(global->root);
	if (global->exc_size == 1)
	{
		execute_one_cmd(global);
		return (FAILURE);
	}
	if (global->exc_size == 0)
		return (FAILURE);
	global->root_tree = build_tree(global, &global->root);
	execute_tree(global, global->root_tree);
	return (SUCCESS);
}

void	main_exc(t_global *global)
{
	t_exc_list	*exc_tmp;

	prepere_list(global);
	bulid_list_exc(global);
	check_builtins_cmds(global->root);
	env_list_2d_array(global);
	exc_tmp = global->root;
	while (exc_tmp)
	{
		if (exc_tmp->redir)
		{
			if (check_doubel_redir(global, &exc_tmp->redir) == FAILURE)
			{
				printf("FAILIER\n");
				global->exit_status = 1;
				exit(1);
			}
		}
		exc_tmp = exc_tmp->next;
	}
	main_exc_p2(global);
}
