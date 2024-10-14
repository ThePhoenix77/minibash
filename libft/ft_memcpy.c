/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:52:47 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 10:52:48 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dstp;
	unsigned char	*srcp;

	dstp = (unsigned char *)dst;
	srcp = (unsigned char *)src;
	if ((dst == NULL) && (src == NULL))
		return (NULL);
	while (n > 0)
	{
		*dstp = *srcp;
		dstp++;
		srcp++;
		n--;
	}
	return (dst);
}
