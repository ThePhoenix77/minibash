/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscall_fun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 21:31:02 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 14:32:20 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) < 0)
		return (perror("minishell: dup2:"), FAILURE);
	close(fd1);
	return (SUCCESS);
}

int	ft_dup(int fd1, int fd2)
{
	fd1 = dup(fd2);
	if (fd1 < 0)
		return (perror("minishell: dup:"), -1);
	return (fd1);
}

bool	ft_close(int fd)
{
	if (close(fd) < 0)
		return (perror("minishell: close:"), FAILURE);
	return (SUCCESS);
}

bool	reset_sett(t_fd *fds)
{
	if (fds->in != -1)
		if (ft_dup2(fds->in, 0) == FAILURE)
			return (FAILURE);
	if (fds->out != -1)
		if (ft_dup2(fds->out, 1) == FAILURE)
			return (FAILURE);
	fds->in = -1;
	fds->out = -1;
	return (SUCCESS);
}
