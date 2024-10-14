/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:55:07 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 15:26:12 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_out(t_redir *redir, t_fd *fds)
{
	int	fd;

	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("minishell: open");
	if (fds->out >= 0)
		close(fds->out);
	fds->out = fd;
}

void	handle_redir_in(t_redir *redir, t_fd *fds)
{
	int	fd;

	fd = open(redir->file_name, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(redir->file_name);
	}
	if (fds->in >= 0)
		close(fds->in);
	fds->in = fd;
	if (redir->file_type == HERE_DOC_FILE)
		unlink(redir->file_name);
}

void	handle_dredir_out(t_redir *redir, t_fd *fds)
{
	int	fd;

	fd = open(redir->file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror("minishell: open");
	if (fds->out >= 0)
		close(fds->out);
	fds->out = fd;
}

bool	handle_redirection(t_redir *redir_list, t_fd *fds)
{
	t_redir	*redir;

	redir = redir_list;
	while (redir)
	{
		if (redir->file_type == ERROR_DIS)
		{
			ft_putstr_fd(redir->file_name, 2);
			ft_putchar_fd('\n', 2);
			exit (1);
		}
		else if (redir->type == REDIR_OUT)
			handle_redir_out(redir, fds);
		else if (redir->type == REDIR_IN)
			handle_redir_in(redir, fds);
		else if (redir->type == DREDIR_OUT)
			handle_dredir_out(redir, fds);
		redir = redir->next;
	}
	if (fds->in > 0 || fds->out > 0)
		return (SUCCESS);
	return (FAILURE);
}
