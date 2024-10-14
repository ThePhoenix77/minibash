/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokeniz.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:15:35 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 20:07:30 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_opr(t_global *global)
{
	if ((global->line_input[0] == ' ' || global->line_input[0] == '\t'
			|| global->line_input[0] == '\n')
		&& global->state == GENERAL)
		skip_ec_t(global, 1);
	if (check_operator(global) == SUCCESS)
		return ;
	global->content = (char *)malloc(sizeof(char) * 2);
	if (global->content == NULL)
		malloc_failed(global);
	ft_strlcpy(global->content, global->line_input, 2);
	global->type = global->content[0];
	check_type(global);
	update_line(&global->line_input, 1, global);
	add_list(global);
}

bool	check_operator(t_global *global)
{
	if (!ft_strchr(META_CHARS, global->line_input[0]))
		return (SUCCESS);
	if (global->line_input[0] == '\"' || global->line_input[0] == '\'')
	{
		get_str_inside_quote(global);
		global->state = GENERAL;
		global->type = WORD;
		return (SUCCESS);
	}
	if (global->line_input[0] == '>' || global->line_input[0] == '<')
	{
		if (check_heredoc_dred(global) == SUCCESS)
			return (SUCCESS);
	}
	if (global->line_input[0] == '\0' || !global->line_input)
		return (SUCCESS);
	return (FAILURE);
}

void	del_sp(t_global *global)
{
	t_lst	*last;

	last = last_node(global->head);
	if (last->type == WHITE_SPACE)
	{
		free(last->content);
		last->prev->next = NULL;
		free(last);
	}
}

void	ft_tokeniz(t_global *global)
{
	int		len_un_sep;

	while (global->line_input && global->line_input[0] != '\0')
	{
		len_un_sep = ft_strlen_un_del(META_CHARS, global->line_input);
		if (len_un_sep)
		{
			if (!ft_strchr(META_CHARS, global->line_input[0]))
			{
				global->content = get_word(&global->line_input,
						len_un_sep, global);
				add_list(global);
			}
			else
				get_opr(global);
		}
		if (len_un_sep == 0)
		{
			global->content = global->line_input;
			global->line_input = NULL;
			add_list(global);
		}
	}
	del_sp(global);
	return ;
}
