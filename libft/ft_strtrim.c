/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 10:54:19 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/04 10:54:20 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*trimmed;

	trimmed = (char *)s1;
	if (!s1 || !set)
		return (0);
	while (*s1 != '\0' && ft_strchr(set, *s1) != 0)
		s1++;
	len = ft_strlen(s1);
	if (len != 0)
		while (len >= 0 && ft_strchr(set, s1[len]) != 0)
			len--;
	trimmed = ft_substr((char *)s1, 0, len + 1);
	return (trimmed);
}
