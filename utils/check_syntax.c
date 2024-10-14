/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:13:29 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 15:43:10 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_num_heredoc(t_global *global)
{
	int		i;
	t_lst	*tmp;

	i = 0;
	tmp = global->head;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
			i++;
		tmp = tmp->next;
	}
	if (i > 16)
		return (FAILURE);
	return (SUCCESS);
}

void	ft_print_error(t_global *global, t_lst **node)
{
	if ((((*node)) && ((*node)->prev && (*node)->prev->type == HERE_DOC))
		|| (((*node)->prev) && (*node)->prev->prev
			&& (*node)->prev->prev->type == HERE_DOC))
	{
		ft_putstr_fd(ERROR, 2);
		ft_putchar_fd((*node)->content[0], 2);
		ft_putstr_fd("'\n", 2);
		check_here_doc(global);
		return ;
	}
	check_here_doc(global);
	ft_putstr_fd(ERROR, 2);
	ft_putchar_fd((*node)->content[0], 2);
	ft_putstr_fd("'\n", 2);
}

bool	check_syntax(t_global *global)
{
	t_lst		*tmp;
	int			v;
	static int	tr[6][7] = {{2, 3, 3, 3, 3, 0, 0},
	{2, 3, 3, 3, 3, 4, 5}, {2, 0, 0, 0, 0, 0, 6},
	{2, 3, 3, 3, 3, 0, 6}, {2, 3, 3, 3, 3, 4, 0},
	{2, 3, 3, 3, 3, 0, 0}};

	tmp = global->head;
	v = 1;
	while (tmp)
	{
		v = tr[v - 1][tmp->type - 1];
		if (!v)
		{
			ft_print_error(global, &tmp);
			return (FAILURE);
		}
		tmp = tmp->next;
	}
	if (v == 2)
		return (SUCCESS);
	tmp = last_node(global->head);
	ft_print_error(global, &tmp);
	return (FAILURE);
}

void	open_heredoc_sy(char *eof)
{
	char	*read;
	int		len;

	len = ft_strlen(eof);
	while (1)
	{
		read = readline("> ");
		if (!read || ft_strcmp(read, eof) == SUCCESS)
			break ;
		free(read);
	}
	if (read)
		free(read);
}

void	check_here_doc(t_global *global)
{
	t_lst	*tmp;

	tmp = global->head;
	while (tmp)
	{
		if (tmp->type == HERE_DOC)
		{
			if (tmp->next)
			{
				if (tmp->next->next && tmp->next->next->type == WORD)
					open_heredoc_sy(tmp->next->next->content);
			}
		}
		tmp = tmp->next;
	}
}
