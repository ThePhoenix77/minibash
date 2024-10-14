/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:53:59 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 10:54:00 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	i;
	size_t	j;

	if ((dst == NULL) && dstsize == 0)
		return (0);
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	i = dstlen;
	j = 0;
	if (dstsize <= dstlen)
		return (dstsize + srclen);
	while (i < dstsize - 1 && src[j])
	{
		dst[i] = src[j];
		j++;
		i++;
	}
	dst[i] = '\0';
	return (dstlen + srclen);
}
