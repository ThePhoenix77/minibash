/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_Tokeniz2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 11:15:30 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 15:53:38 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_heredoc_dred(t_global *global)
{
	if (global->line_input[0] == '>' && global->line_input[1] == '>')
	{
		global->content = ft_strdup(">>");
		global->type = DREDIR_OUT;
	}
	else if (global->line_input[0] == '<' && global->line_input[1] == '<')
	{
		global->content = ft_strdup("<<");
		global->type = HERE_DOC;
	}
	if (global->type == HERE_DOC || global->type == DREDIR_OUT)
	{
		update_line(&global->line_input, 2, global);
		add_list(global);
		return (SUCCESS);
	}
	return (FAILURE);
}

void	get_str_inside_quote(t_global *global)
{
	int	len_unt_qoute;

	len_unt_qoute = 0;
	if (global->line_input[0] == '\"' || global->line_input[0] == '\'')
	{
		check_state(global);
		update_line(&global->line_input, 1, global);
		if (global->state == IN_DQUOTE)
			len_unt_qoute = ft_strlen_un_char(global->line_input, '\"');
		if (global->state == IN_SQUOTE)
			len_unt_qoute = ft_strlen_un_char(global->line_input, '\'');
		if (len_unt_qoute < 0)
		{
			free_memory(global);
			ft_putstr_fd(UNCLOSED_QUOTE, 2);
			global->exit_status = 258;
			get_line(global);
		}
		global->content = malloc(sizeof(char) * len_unt_qoute + 1);
		if (global->content == NULL)
			return ((void) NULL);
		ft_strlcpy(global->content, global->line_input, len_unt_qoute + 1);
		update_line(&global->line_input, len_unt_qoute + 1, global);
		add_list(global);
	}
}
