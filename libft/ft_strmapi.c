/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:29:45 by eaboudi           #+#    #+#             */
/*   Updated: 2024/07/26 12:29:46 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*res;

	i = 0;
	if ((s == NULL) || (f == NULL))
		return (NULL);
	len = ft_strlen(s);
	res = (char *)malloc((sizeof(char)) * (len + 1));
	if (res == NULL)
		return (NULL);
	else
	{
		while (i < len)
		{
			res[i] = f(i, s[i]);
			i++;
		}
		res[i] = '\0';
	}
	return (res);
}
