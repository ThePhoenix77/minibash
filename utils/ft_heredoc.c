/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:17:32 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 11:57:53 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	buff_heredoc(t_global *global, char *line)
{
	char	*tmp;
	char	*save;

	tmp = ft_strjoin2(line, "\n");
	if (!tmp)
	{
		free(line);
		malloc_failed(global);
	}
	free(line);
	save = ft_strjoin2(global->content, tmp);
	if (global->content)
		free(global->content);
	free(tmp);
	global->content = save;
}

bool	open_heredoc(t_global *global, t_lst *lim_node)
{
	char	*line;

	global->content = NULL;
	signal(SIGINT, handler);
	while (1)
	{
		line = readline("> ");
		if (!ttyname(0))
		{
			open(ttyname(2), O_RDWR);
			return (free(line), FAILURE);
		}
		if (!line || ft_strcmp(line, lim_node->content) == SUCCESS)
		{
			free(lim_node->content);
			lim_node->content = global->content;
			if (!line)
				empty_here_doc(global, lim_node);
			free(line);
			break ;
		}
		buff_heredoc(global, line);
	}
	sig_hnd();
	return (SUCCESS);
}

void	get_limit_hrdc(t_global *global, t_lst **node)
{
	char	*save;
	t_lst	*hd_node;

	hd_node = *node;
	global->content = NULL;
	save = NULL;
	while (hd_node && hd_node->type == WORD)
	{
		save = ft_strjoin2(global->content, hd_node->content);
		if (!save)
		{
			if (global->content)
				free(global->content);
			malloc_failed(global);
		}
		if (global->content)
			free(global->content);
		global->content = save;
		hd_node->type = SKIP;
		hd_node = hd_node->next;
	}
}

bool	here_doc_failed(t_global *global, t_lst *node)
{
	if (open_heredoc(global, node) == FAILURE)
	{
		if (global->content)
			free(global->content);
		return (FAILURE);
	}
	return (SUCCESS);
}

bool	check_heredoc(t_global *global)
{
	t_lst	*tmp;

	tmp = global->head;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			if (tmp->next->type == WORD)
				tmp = tmp->next;
			else
				tmp = tmp->next->next;
			get_limit_hrdc(global, &tmp);
			if (tmp->content)
			{
				free(tmp->content);
				tmp->content = global->content;
				global->content = NULL;
			}
			if (here_doc_failed(global, tmp) == FAILURE)
				return (FAILURE);
			tmp->type = EXP_HERE_DOC;
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
