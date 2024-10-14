/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:54:16 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 10:54:17 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*res;

	res = NULL;
	while (*s)
	{
		if (*s == (char)c)
		{
			res = s;
		}
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return ((char *)res);
}
