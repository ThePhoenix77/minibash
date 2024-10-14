/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:53:54 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 10:53:55 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	i = 0;
	if ((s == NULL) || (f == NULL))
		return ;
	if ((!s) || (!f))
		return ;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
