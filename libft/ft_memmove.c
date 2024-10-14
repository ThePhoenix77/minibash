/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:52:51 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 10:52:52 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if ((dst == NULL) && (src == NULL))
		return (NULL);
	if (d > s && d < s + len)
	{
		s += len;
		d += len;
		while (len-- > 0)
			*--d = *--s;
	}
	else
	{
		while (len-- > 0)
			*d++ = *s++;
	}
	return (dst);
}
