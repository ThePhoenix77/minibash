/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils_Tokeniz1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 08:21:44 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 20:17:59 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_word(char **line, int len, t_global *global)
{
	char	*word;

	word = malloc(sizeof(char) * len + 1);
	if (!word)
		malloc_failed(global);
	ft_strlcpy(word, *line, len + 1);
	update_line(line, len, global);
	return (word);
}

void	update_line(char **line, int len_skip, t_global *global)
{
	char	*save;

	save = ft_strdup (*line + len_skip);
	if (!save)
		malloc_failed(global);
	free(*line);
	*line = save;
	save = NULL;
}

void	skip_ec_t(t_global *global, int flag)
{
	int	i;

	i = 0;
	if (!global->line_input)
		return ;
	while (global->line_input[i]
		&& (global->line_input[i] == ' '
			|| global->line_input[i] == '\t'))
		i++;
	update_line(&global->line_input, i, global);
	if (flag == 1)
	{
		global->content = ft_strdup(" ");
		if (!global->content)
			malloc_failed(global);
		global->state = GENERAL;
		global->type = WHITE_SPACE;
		add_list(global);
	}
}

void	check_state(t_global *global)
{
	if (global->line_input[0] == '\"')
	{
		if (global->state == GENERAL)
			global->state = IN_DQUOTE;
		else if (global->state == IN_DQUOTE)
		{
			global->state = GENERAL;
			global->type = WORD;
		}
	}
	if (global->line_input[0] == '\'')
	{
		if (global->state == GENERAL)
			global->state = IN_SQUOTE;
		else if (global->state == IN_SQUOTE)
		{
			global->state = GENERAL;
			global->type = WORD;
		}
	}
}

void	check_type(t_global *global)
{
	if (global->content[0] == '>')
		global->type = REDIR_OUT;
	if (global->content[0] == '<')
		global->type = REDIR_IN;
	if (global->content[0] == '|')
		global->type = PIPE;
	if (global->content[0] == ' ')
		global->type = WHITE_SPACE;
}
