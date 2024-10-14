/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:54:13 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 10:54:14 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*tmp1;
	char	*tmp2;
	size_t	i;

	if (*needle == '\0')
		return ((char *)haystack);
	while (len > 0 && *haystack)
	{
		i = 0;
		tmp1 = (char *)haystack;
		tmp2 = (char *)needle;
		while (*tmp2 && *tmp1 == *tmp2 && i < len)
		{
			tmp1++;
			tmp2++;
			i++;
		}
		if (*tmp2 == '\0')
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
