/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:02:28 by eaboudi           #+#    #+#             */
/*   Updated: 2024/08/19 18:02:29 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count(int n)
{
	int		c;
	long	num;

	num = n;
	c = 0;
	if (num <= 0)
	{
		c = 1;
		num *= -1;
	}
	while (num > 0)
	{
		num /= 10;
		c++;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	int		c;
	long	num;
	char	*res;

	c = count(n);
	num = n;
	res = (char *)malloc(sizeof(char) * (c + 1));
	if (res == NULL)
		return (NULL);
	res[c--] = '\0';
	if (num < 0)
	{
		num *= -1;
		res[0] = '-';
	}
	if (num == 0)
		res[0] = '0';
	while (num > 0)
	{
		res[c--] = (num % 10) + '0';
		num /= 10;
	}
	return (res);
}
